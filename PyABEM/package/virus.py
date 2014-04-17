#! /usr/bin/python
# coding=utf-8

from tag import *
from agent import *
from config import *

### Virus
class Virus( Tag ):
  cling_point = 0
  cling_tag = 0
  def __init__(self):
    super(Virus, self).__init__(V_TAG_LEN)

  def infection(self, agent):
    """ エージェントに感染させる """
    if probability(10):
      agent.infected_virus.append(self)
    else: pass

  def info(self):
    """ ウイルス情報を表示 """
    print '[ %s ] %s' % ( self, self.tag )

def show_virus_info(viruses):
  for v in viruses:
    v.info()