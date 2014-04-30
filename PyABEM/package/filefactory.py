#! /usr/bin/python
# coding=utf-8

import os
import shutil

from agent import *
from AgentManager import *
from virus import *
from landscape import *

CONFIG_PATH = 'package/config.py'

class FileFactory(object):
    def __init__(self, a, v, l):
        # os.makedirs(BIN)
        self.f_has_virus = open(FNAME_HASVIRUS, 'w')
        self.f_ave_tag_len = open(FNAME_TAGLEN, 'w')
        self.f_info = open(FNAME_INFO, 'w')
        self.f_config = open(FNAME_CONFIG, 'w')
        self.f_population = open(FNAME_POPULATION, 'w')

    def outputHasVirus(self, t, agents, viruses):
        """ time infectedv1 infectedv2 ... """
        # if a is None: a = self.agents
        line = ''
        line += str(t)
        for v in viruses:
            line += ' %d' % agentIsInfected(agents, v)
        line += '\n'
        self.f_has_virus.write(line)
    def outputTagLen(self, t, agents):
        self.f_ave_tag_len.write(
            str(t/GENERATION_INTERVAL)+' '+str(ave_tag_len(agents))+' '+str(len(agents))+'\n'
            )
    def outputInfo(self, agents):
        for a in agents:
            self.f_info.write('%d %s %d %d\n' % (len(a.tag), a.tag, a.x, a.y))
        fconfig = open(CONFIG_PATH, 'r')
        for line in fconfig:
            if line[0] == '#' or line == '\n': continue
            self.f_config.write(line)

    def outputPopulation(self, t, agents):
        self.f_population.write(
            str(t)+' '+str( len(agents) )+'\n'
            )

    def close(self):        
        self.f_has_virus.close()
        self.f_ave_tag_len.close()
        self.f_info.close()
        self.f_config.close()
        self.f_population.close()