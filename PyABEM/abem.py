#! /usr/bin/python
# coding=utf-8

import random
import os

from package import *

def main():
    """ Entry point of Agent Based Model program """
    # 変数宣言
    agents = []
    viruses = []
    landscape = Landscape()
    f = open(FNAME, 'w')
    f_ave_tag_len = open('ave.txt', 'w')

    # 初期設定
    for i in range(A_NUM):
        agents.append(Agent(30, 50))

    for i in range(V_NUM):
        viruses.append(Virus(20))

    ff = FileFactory(f, agents, viruses, landscape)

    # 初期感染
    initial_infection(agents, viruses)

    # 計算開始
    for t in range( TERM ):
        print "[ %5d ]  agents( %5d )  infected(%5d)" % (
            t, len(agents), agentIsInfected(agents, viruses[0])
            )

        landscape.reset_agent_map() # 土地を初期化する

        agentMove( agents, landscape )
        agentContact( agents, viruses, landscape )
        agentInfection( agents )
        agentResponse( agents )

        if t % GENERATION_INTERVAL == 0:
            f_ave_tag_len.write(
                str(t/GENERATION_INTERVAL)+' '+str(ave_tag_len(agents))+' '+str(len(agents))+'\n'
                )
            new_agents = []
            while(len(agents) >= 2):
                a = agents.pop(random.randint(0, len(agents)-1))
                b = agents.pop(random.randint(0, len(agents)-1))
                n, m = mating( a, b ), mating(a, b)
                new_agents.append( n )
                new_agents.append( m )
            agents = new_agents
            while( len(agents) < A_NUM ):
                agents.append( Agent(30, 50) )
            initial_infection(agents, viruses)

        ff.output(t, agents) # なぜagentsの必要か
        #if agentIsInfected(agents, viruses[0]) <= 0:
        #    break;

    # 最終状態表示
    show_agent_information(agents, 5)
    show_virus_info(viruses)

    f.close()

if __name__ == "__main__":
    print '>>> start ABEM program'
    main()
    plot()
