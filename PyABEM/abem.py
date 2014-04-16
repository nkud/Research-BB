#! /usr/bin/python
# coding=utf-8

import random

from function import *
from landscape import *

A_NUM = 1000
V_NUM = 1
WIDTH = 20
MOVE_DIST = 3
TERM = 200


### Tag
class Tag(object):
  gene = '1111'

### Agent
class Agent( Tag ):
  def __init__(self, land):
    self.x = random.randint(0, WIDTH-1)
    self.y = random.randint(0, WIDTH-1)

    self.stand_by_virus = []
    self.infected_virus = []
    if probability(10):
      self.infected_virus.append(1)

    self.land = land

  def move(self):
    """ 移動して土地に登録する """
    self.x += random.randint(-MOVE_DIST, MOVE_DIST)
    self.y += random.randint(-MOVE_DIST, MOVE_DIST)
    self.x = random.randint(0, WIDTH-1)
    self.y = random.randint(0, WIDTH-1)
    self.x %= WIDTH
    self.y %= WIDTH
    self.land.resist_agent_to_map(self, self.x, self.y)

  def response(self):
    """ 免疫獲得する """
    if probability(20):
      self.infected_virus = []

  def contact(self, agent):
    """ 接触する
    Attributes:
      agent: 接触した相手エージェント
    """
    if len(agent.infected_virus) > 0:
      self.stand_by_virus.append( random.choice(agent.infected_virus) )

  def infection(self):
    """ 感染する """
    if len(self.stand_by_virus) > 0 :
      if probability(100):
       self.infected_virus.append( random.choice( self.stand_by_virus) )
    self.stand_by_virus = []

  def is_infected(self):
    """ has virus or not """
    if len(self.infected_virus) > 0 :
      return True
    else:
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

def agentIsInfected(agents):
  n = 0
  for a in agents:
    if a.is_infected():
      n += 1
  return n

def showAgentInformation(agents, n):
  """ エージェントの情報を表示する """
  print '[ Agents 0 ~ %d ]' % (n-1)
  for i in range(n):
    print '\t%d:\t( %d, %d )' % (i, agents[i].x, agents[i].y)

### Virus
class Virus( Tag ):
  def __init__(self):
    pass

### Main
def main():
  """
  Yields:
    Running BTABM
  """
  agent = []
  virus = []
  landscape = Landscape()

  f = open('output.txt', 'w')

  for i in range(A_NUM):
    agent.append( Agent(landscape) )
  for i in range(V_NUM):
    virus.append(Virus())

  for t in range(TERM):
    print "[ %5d ]  agent( %5d )  infected(%5d)" % ( t, len(agent), agentIsInfected(agent) )

    landscape.reset_agent_map() # 土地を初期化する

    agentMove( agent, landscape )
    agentContact( agent, virus, landscape )
    agentInfection( agent )
    agentResponse( agent )

    outputline = '%d %d\n' % (t, agentIsInfected(agent))
    f.write(outputline)

  showAgentInformation(agent, 3)

  f.close()

if __name__ == "__main__":
  print '>>> start ABEM program'
  main()
