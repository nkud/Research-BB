#! /usr/bin/python
# coding=utf-8

import random
import os

from package import *

### Main
def main():
    agent = []
    virus = []
    landscape = Landscape()
    f = open('output.txt', 'w')

    # 初期設定
    for i in range(A_NUM):
        agent.append(PolyAgent(landscape))

    for i in range(V_NUM):
        virus.append(Virus())
    virus[0].tag = '0000000000'
    virus[1].tag = '1111111111'

    ff = FileFactory(f, agent, virus, landscape)

    # 初期感染
    for a in agent:
        if probability(30):
            a.immunes[0].infected_virus.append(random.choice(virus))

    # 計算開始
    for t in range(TERM):
        print "[ %5d ]  agent( %5d )  infected(%5d)" % ( t, len(agent), agentIsInfected(agent, virus[0]) )

        landscape.reset_agent_map() # 土地を初期化する

        agentMove( agent, landscape )
        agentContact( agent, virus, landscape )
        agentInfection( agent )
        agentResponse( agent )

        ff.output(t)
        # print len(agent[0].immunes[0].infected_virus)

    # 最終状態表示
    showAgentInformation(agent, 5)
    print agent[0].immunes == agent[1].immunes
    show_virus_info(virus)

    f.close()

if __name__ == "__main__":
    print '>>> start ABEM program'
    main()
