#! /usr/bin/python
# coding=utf-8

import os
import shutil

from agent import *
from virus import *
from landscape import *

class FileFactory(object):
    def __init__(self, a, v, l):
        os.makedirs(BIN)
        self.f_has_virus = open(FNAME_HASVIRUS, 'w')
        self.f_ave_tag_len = open(FNAME_TAGLEN, 'w')
        self.f_info = open(FNAME_INFO, 'w')

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

    def close(self):        
        self.f_has_virus.close()
        self.f_ave_tag_len.close()
        self.f_info.close()