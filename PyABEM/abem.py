#! /usr/bin/python
# coding=utf-8

import random
import os

from package import *

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
    agent.append(PolyAgent(landscape))
  for i in range(V_NUM):
    virus.append(Virus())
  virus[0].tag = '0000000000'
  virus[1].tag = '1111111111'

  for a in agent:
    if probability(30):
      a.immunes[0].infected_virus.append(random.choice(virus))

  for t in range(TERM):
    print "[ %5d ]  agent( %5d )  infected(%5d)" % ( t, len(agent), agentIsInfected(agent, virus[0]) )

    landscape.reset_agent_map() # 土地を初期化する

    agentMove( agent, landscape )
    agentContact( agent, virus, landscape )
    agentInfection( agent )
    agentResponse( agent )

    agent[0].numHasVirus()

    # print len(agent[0].immunes[0].infected_virus)
    outputline = '%d %d %d\n' % (t, agentIsInfected(agent, virus[0]), agentIsInfected(agent, virus[1]))
    f.write(outputline)

  showAgentInformation(agent, 5)
  print agent[0].immunes == agent[1].immunes
  show_virus_info(virus)

  f.close()

if __name__ == "__main__":
  print '>>> start ABEM program'
  main()