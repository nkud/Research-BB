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
    # f = open(FNAME_HASVIRUS, 'w')
    # f_ave_tag_len = open(FNAME_TAGLEN, 'w')
    # f_info = open(FNAME_INFO, 'w')

    # 初期設定
    for i in range(A_NUM):
        agents.append(Agent(A_TAG_LEN_FROM, A_TAG_LEN_TO))

    for i in range(V_NUM):
        viruses.append(Virus())

    file_factory = FileFactory(agents, viruses, landscape)

    # 初期感染
    initial_infection(agents, viruses)

    # 計算開始
    for t in range( TERM ):
        print "[ %5d ]  agents( %5d )  infected(%5d) %s" % (
            t, len(agents), agentIsInfected(agents, viruses[0]), str(ave_tag_len(agents))
            )

        landscape.reset_agent_map() # 土地を初期化する

        # Agent の行動　（　移動　→　接触　→　感染　→　免疫応答　）
        agentMove( agents, landscape )
        agentContact( agents, viruses, landscape )
        agentInfection( agents )
        agentResponse( agents )

        # 世代交代            
        if t % GENERATION_INTERVAL == 0:
            if len(agents) <= 0:
                pass
            else:
                file_factory.outputTagLen(t, agents) # Agent　の平均タグ長を出力
                _new_child_agent = []
                while( len(_new_child_agent) < A_NUM ):
                    a = random.choice( agents )
                    b = random.choice( agents )
                    _child = mating( a, b )
                    _new_child_agent.append( _child )
                agents = _new_child_agent
                initial_infection(agents, viruses)
        if len(agents) <= 0:
            break;
        file_factory.outputHasVirus(t, agents, viruses) # なぜagentsの必要か
        # if agentIsInfected(agents, viruses[0]) <= 0:
        #    break;

    # 最終状態表示
    show_agent_information(agents, 5)
    show_virus_info(viruses)

    # Agent の最終状態を出力
    file_factory.outputInfo(agents)

    # close files pointer
    file_factory.close()

if __name__ == "__main__":
    print '>>> start ABEM program'
    main()
    pf = PlotFactory(BINDIR+'auto.plt')
    pf.generatePlotScript()
    hf = HtmlFactory(BINDIR+'index.html')
    hf.generate()
    plot()