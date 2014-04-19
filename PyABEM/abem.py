#! /usr/bin/python
# coding=utf-8

import random
import os

from package import *

FNAME = 'output.txt'

### Main
def main():
    agents = []
    viruses = []
    landscape = Landscape()
    f = open(FNAME, 'w')

    # 初期設定
    for i in range(A_NUM):
        agents.append(Agent(landscape))

    for i in range(V_NUM):
        viruses.append(Virus())
    viruses[0].tag = '0000000000'
    viruses[1].tag = '1111111111'

    ff = FileFactory(f, agents, viruses, landscape)

    # 初期感染
    for a in agents:
        if probability(30):
            a.immune.infected_virus.append(random.choice(viruses))

    # 計算開始
    for t in range(TERM):
        print "[ %5d ]  agents( %5d )  infected(%5d)" % ( t, len(agents), 
            agentIsInfected(agents, viruses[0]) )

        landscape.reset_agent_map() # 土地を初期化する

        agentMove( agents, landscape )
        agentContact( agents, viruses, landscape )
        agentInfection( agents )
        agentResponse( agents )

        ff.output(t)

    # 最終状態表示
    showAgentInformation(agents, 5)
    show_virus_info(viruses)

    f.close()

if __name__ == "__main__":
    print '>>> start ABEM program'
    main()
