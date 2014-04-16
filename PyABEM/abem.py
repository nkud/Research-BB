#! /usr/bin/python
# coding=utf-8

import random

print 'This is an Agent Based Model using Binary Tags. '

A_NUM = 100
V_NUM = 1
WIDTH = 20
MOVE_DIST = 3
TERM = 30

### Tag
class Tag(object):
  gene = []

### Agent
class Agent( Tag ):
  def __init__(self, land):
    self.x = random.randint(0, WIDTH-1)
    self.y = random.randint(0, WIDTH-1)
    self.stand_by_virus = []
    self.infected_virus = []
    self.land = land

  def move(self):
    """ 移動して土地に登録する """
    self.x += random.randint(-MOVE_DIST, MOVE_DIST) 
    self.y += random.randint(-MOVE_DIST, MOVE_DIST) 
    self.x %= WIDTH
    self.y %= WIDTH
    self.land.resist_agent_to_map(self, self.x, self.y)

  def response(self):
    """ 免疫獲得する """
    pass
  def contact(self):
    """ 接触する """
    pass

  def infection(self):
    """ 感染する """
    pass

def agent_contact(agents, viruses, land):
  for a in agents:
    ax = a.x
    ay = a.y
    for na in land.agent_map[ax][ay]:
      if na == a: continue
      print ax, ay

def show_agent_info(agents, n):
  """ エージェントの情報を表示する """
  print '[ Agents 0 - %d ]' % (n-1)
  for i in range(n):
    print '\t%d:\t( %d, %d )' % (i, agents[i].x, agents[i].y)

### Virus
class Virus( Tag ):
  def __init__(self):
    pass

### Landscape
class Landscape(object):
  agent_map = []
  def __init__(self):
    self.reset_agent_map()

  def reset_agent_map(self):
    """ エージェントのマップを初期化する """
    self.agent_map = []
    for h in range(WIDTH):
      t = []
      for w in range(WIDTH):
        t.append([])
      self.agent_map.append(t)
  def resist_agent_to_map(self, a, x, y):
    """ エージェントをマップに登録する """
    self.agent_map[x][y].append(a)

### Main
def main():
  """
  Yields:
    Running BTABM
  """
  agent = []
  virus = []
  landscape = Landscape()

  for i in range(A_NUM):
    agent.append( Agent(landscape) )
  for i in range(V_NUM):
    virus.append(Virus())

  for t in range(TERM):
    print "[ %5d ]  agent( %5d ) %d" % ( t, len(agent), len(landscape.agent_map[0][0]) )

    landscape.reset_agent_map() # 土地を初期化する

    for a in agent:
      a.move()

    agent_contact( agent, virus, landscape )

  show_agent_info(agent, 10)

if __name__ == "__main__":
  print 'start main()'
  main()
