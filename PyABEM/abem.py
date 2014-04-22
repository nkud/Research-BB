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
    f_info = open('info.txt', 'w')

    # 初期設定
    for i in range(A_NUM):
        agents.append(Agent(A_TAG_LEN_FROM, A_TAG_LEN_TO))

    for i in range(V_NUM):
        viruses.append(Virus())

    ff = FileFactory(f, agents, viruses, landscape)

    # 初期感染
    initial_infection(agents, viruses)

    # 計算開始
    for t in range( TERM ):
        print "[ %5d ]  agents( %5d )  infected(%5d) %s" % (
            t, len(agents), agentIsInfected(agents, viruses[0]), str(ave_tag_len(agents))
            )

        landscape.reset_agent_map() # 土地を初期化する

        agentMove( agents, landscape )
        agentContact( agents, viruses, landscape )
        agentInfection( agents )
        agentResponse( agents )

        # 世代交代            
        if t % GENERATION_INTERVAL == 0:
            if len(agents) <= 0:
                pass
            else:
                f_ave_tag_len.write(
                    str(t/GENERATION_INTERVAL)+' '+str(ave_tag_len(agents))+' '+str(len(agents))+'\n'
                    )
                _new_child_agent = []
                while( len(_new_child_agent) < A_NUM ):
                    a = random.choice( agents )
                    b = random.choice( agents )
                    _child = mating( a, b )
                    _new_child_agent.append( _child )
                # while(len(agents) >= 2):
                #    a = die(agents)
                #    b = die(agents)
                #    n, m = mating(a, b), mating(a, b)
                #    _new_child_agent.append( n )
                #    _new_child_agent.append( m )
                agents = _new_child_agent
                # complement_agent(agents)
                initial_infection(agents, viruses)
        if len(agents) <= 0:
            break;
        ff.output(t, agents) # なぜagentsの必要か
        # if agentIsInfected(agents, viruses[0]) <= 0:
        #    break;

    # 最終状態表示
    show_agent_information(agents, 5)
    show_virus_info(viruses)

    for a in agents:
        f_info.write('%d %s %d %d\n' % (len(a.tag), a.tag, a.x, a.y))

    f.close()
    f_ave_tag_len.close()
    f_info.close()

if __name__ == "__main__":
    print '>>> start ABEM program'
    main()
    plot()