#! /usr/bin/python
# coding=utf-8

import random

from function import *
from landscape import *
from virus import *
from tag import *
from agent import *
from config import *

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

  for v in virus:
    for a in agent:
      v.infection(a)

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
  show_virus_info(virus)

  f.close()

if __name__ == "__main__":
  print '>>> start ABEM program'
  main()
