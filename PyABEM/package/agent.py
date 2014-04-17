#! /usr/bin/python
# coding=utf-8

from landscape import *
from tag import *
from virus import *
from config import *
from function import *

### Agent
class Agent( Tag ):
  x = 0
  y = 0
  stand_by_virus = []
  infected_virus = []
  land = object
  def __init__(self, land):
    super(Agent, self).__init__(A_TAG_LEN)
    self.x = random.randint(0, WIDTH-1)
    self.y = random.randint(0, WIDTH-1)

    self.stand_by_virus = []
    self.infected_virus = []

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
    """ 接触する
    Attributes:
      agent: 接触した相手エージェント
    """
    if len(agent.infected_virus) > 0:
      if probability(INFECTION_RATE):
        self.stand_by_virus.append( random.choice(agent.infected_virus) )
      else: pass
    else: pass

  def infection(self):
    """ 感染する """
    if len(self.stand_by_virus) > 0 :
      v = random.choice( self.stand_by_virus ) # ランダムに選んで
      if not self.hasImmunity(v) and not self.hasVirus(v) :
        v.cling_point = min_ham_distance(self.tag, v.tag)
        if v.cling_point >=0 :
          self.infected_virus.append( v )
      self.stand_by_virus = []

  def response(self):
    """ 免疫獲得する
    フリップ : return 1
    免疫獲得済み : return 0
    """
    if len(self.infected_virus) > 0:
      cp = self.infected_virus[0].cling_point # 先頭のウイルスの取りつく位置
      v = self.infected_virus[0]
      for i in range(v.len):
        if self.tag[cp+i] == v.tag[i]:
          continue
        else:
          self.tag = self.tag[:cp+i]+v.tag[i]+self.tag[cp+i+1:]
          return 1
      del self.infected_virus[0] # フリップする必要がなければ免疫獲得
      return 0
    else: pass

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
    for myv in self.infected_virus :
      if myv == v : return True
    return False

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
    if a.hasVirus(v) :
      n += 1
  return n

def showAgentInformation(agents, n):
  """ エージェントの情報を表示する """
  print '[ Agents 0 ~ %d ]' % (n-1)
  for i in range(n):
    print '\t%d:\t( %d, %d ) %s %s' % (i, agents[i].x, agents[i].y, agents[i].tag, agents[i].infected_virus)
