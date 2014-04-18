#! /usr/bin/python
# coding=utf-8

from agent import *
from virus import *
from landscape import *

class FileFactory(object):
    def __init__(self, f, a, v, l):
        self.f = f
        self.agents = a
        self.viruses = v
        self.landscape = l
    def output(self, t):
        """ time infectedv1 infectedv2 ... """
        line = ''
        line += str(t)
        for v in self.viruses:
            line += ' %d' % agentIsInfected(self.agents, v)
        line += '\n'
        self.f.write(line)
