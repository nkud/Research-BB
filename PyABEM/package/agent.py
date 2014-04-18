#! /usr/bin/python
# coding=utf-8

from landscape import *
from tag import *
from virus import *
from config import *
from function import *

import landscape

### ImmuneSystem
class ImmuneSystem( object ):
  def __init__(self, tag):
    self.tag = tag
    self.stand_by_virus = []
    self.infected_virus = []

  def contact(self, agent):
    """ 接触する """
    if len(agent.immune.infected_virus) > 0:
      if probability(INFECTION_RATE):
        self.stand_by_virus.append( random.choice(agent.immune.infected_virus) )

  def infection(self):
    """ 感染する """
    if len(self.stand_by_virus) > 0 :
      v = random.choice( self.stand_by_virus ) # ランダムに選んで
      if not self.hasImmunity(v) and not self.hasVirus(v) :
        v.cling_point = min_ham_distance(self.tag, v.tag)
        if v.cling_point >=0 :
          self.infected_virus.append( v )
          self.stand_by_virus = []
        return True
    self.stand_by_virus = []
    return False

  def infection(self, v):
    """ 感染する """
    if not self.hasImmunity(v) and not self.hasVirus(v) :
      v.cling_point = min_ham_distance(self.tag, v.tag)
      if v.cling_point >=0 :
        self.infected_virus.append( v )
        self.stand_by_virus = []
        return True
    self.stand_by_virus = []
    return False

  def response(self):
    """ 免疫獲得する
    フリップ : return 1
    免疫獲得済み : return 0
    """
    if len(self.infected_virus) > 0:
      cp = self.infected_virus[0].cling_point # 先頭のウイルスの取りつく位置
      v = self.infected_virus[0]
      for i in range(v.length):
        if self.tag[cp+i] == v.tag[i]:
          continue
        else:
          self.tag = self.tag[:cp+i]+v.tag[i]+self.tag[cp+i+1:]
          return True
      del self.infected_virus[0] # フリップする必要がなければ免疫獲得
    return False

  def hasImmunity(self, v):
    if self.tag.find(v.tag) >= 0:
      return True
    else:
      return False

  def isInfected(self):
    """ has virus or not """
    if len(self.infected_virus) > 0 :
      return True
    else:
      return False

  def hasVirus(self, v):
    for iv in self.infected_virus :
      if iv == v:
        return True
    return False


### Agent
class Agent( Tag ):
  def __init__(self, land):
    self.x = random.randint(0, WIDTH-1)
    self.y = random.randint(0, WIDTH-1)

    self.stand_by_virus = []
    self.infected_virus = []

    self.immune = ImmuneSystem(self.tag)

    self.land = land

  def move(self):
    """ 移動して土地に登録する """
    #self.x += random.randint(-MOVE_DIST, MOVE_DIST)
    #self.y += random.randint(-MOVE_DIST, MOVE_DIST)
    self.x = random.randint(0, WIDTH-1)
    self.y = random.randint(0, WIDTH-1)
    self.x %= WIDTH
    self.y %= WIDTH
    self.land.resist_agent_to_map(self, self.x, self.y)

  def contact(self, agent):
    self.immune.contact(agent)

  def infection(self):
    self.immune.infection()

  def response(self):
    self.immune.response()

  def hasImmunity(self, v):
    return self.immune.hasImmunity(v)

  def isInfected(self):
    return self.immune.isInfected()

  def hasVirus(self, v):
    return self.immune.hasVirus(v)

  def info(self):
    """ 個人情報を表示 """
    print "%d %d" % ( self.x, self. y )

### PolyAgent
class PolyAgent( MultiTag ):
  def __init__(self, land):
    super(PolyAgent, self).__init__(A_TAG_LEN, A_TAG_NUM)
    self.immunes = []
    self.num = A_TAG_NUM
    #for i in range(self.num):
    for t in self.tags:
      self.immunes.append(ImmuneSystem(t))
    self.x = random.randint(0, WIDTH-1)
    self.y = random.randint(0, WIDTH-1)

    self.stand_by_virus = []
    self.land = land

  def move(self):
    """ 移動して土地に登録する """
    #self.x += random.randint(-MOVE_DIST, MOVE_DIST)
    #self.y += random.randint(-MOVE_DIST, MOVE_DIST)
    self.x = random.randint(0, WIDTH-1)
    self.y = random.randint(0, WIDTH-1)
    self.x %= WIDTH
    self.y %= WIDTH
    self.land.resist_agent_to_map(self, self.x, self.y)

  def contact(self, agent):
    stv = []
    for im in agent.immunes:
      stv += im.infected_virus

    if len(stv) > 0:
      if probability(INFECTION_RATE):
        self.stand_by_virus.append( random.choice(stv) )

  def infection(self):
    if len(self.stand_by_virus) > 0:
      for v in self.stand_by_virus:
        for im in self.immunes:
          if im.infection(v) :
            self.stand_by_virus = []
            return True
    self.stand_by_virus = []
    return False

  def response(self):
    for im in self.immunes:
      im.response()

  def hasImmunity(self, v):
    for im in self.immunes:
      if im.hasImmunity(v):
        return True
    return False

  def isInfected(self):
    for im in self.immunes:
      if im.isInfected():
        return True
    return False

  def hasVirus(self, v):
    for im in self.immunes:
      if im.hasVirus(v):
        return True
    return False

  def numHasVirus(self):
    n = 0
    for im in self.immunes:
      n += len(im.infected_virus)
    return n

  def info(self):
    """ 個人情報を表示 """
    print "%d %d" % ( self.x, self. y )

# Agent Management
def agentContact(agents, viruses, land):
  for myself in agents:
    ax = myself.x
    ay = myself.y
    a_list = land.agent_map[ax][ay]
    for i in [-1, 1]:
      for j in [-1, 1]:
        if land.isOnMap(ax+i, ay+j):
          a_list += land.agent_map[ax+i][ay+j]
    a_list.remove( myself )
    if( len(a_list) > 0 ):
      myself.contact( random.choice(a_list) )

def agentMove(agents, land):
  for a in agents:
    a.move()

def agentInfection(agents):
  for a in agents:
    a.infection()

def agentResponse(agents):
  for a in agents:
    a.response()

def agentIsInfected(agents, v):
  n = 0
  for a in agents:
    if a.hasVirus(v):
      n += 1
  return n

def showAgentInformation(agents, n):
  """ エージェントの情報を表示する """
  print '[ Agents 0 ~ %d ]' % (n-1)
  for i in range(n):
    print '\t%d:\t( %d, %d ) %s %s' % (i, agents[i].x, agents[i].y, agents[i].immunes[0].tag, agents[i].immunes[0].infected_virus)
