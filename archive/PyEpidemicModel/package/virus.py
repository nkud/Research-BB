#! /usr/bin/python
# coding=utf-8

from tag import *
from agent import *
from config import *

### Virus
class Virus( Tag ):
    def __init__(self, tl = V_TAG_LEN):
        super(Virus, self).__init__(tl)

        # 潜伏期間の設定
        self.incubate_period = V_INCUBATE_PERIOD
        self.onset_period = V_ONSET_PERIOD

    def infection(self, agent):
        """ エージェントに感染させる """
        if probability(10):
            agent.virus_list.append(self)

    def info(self):
        """ ウイルス情報を表示 """
        print '[ %s ] %s' % ( self, self.tag )

### Virus List
class VirusList( object ):
    def __init__(self, v, cp = 0):
        self.virus = v
        self.cling_point = cp
        self.time = 0

    def info(self):
        print '%s at %d' % (self.virus, self.cling_point)

def show_virus_info(viruses):
    for v in viruses:
        v.info()