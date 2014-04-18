#! /usr/bin/python
# coding=utf-8

from function import *
from config import *
from agent import *
from virus import *
from landscape import *

### ImmuneSystem
class ImmuneSystem( object ):
  def __init__(self, tag):
    self.tag = tag
    self.stand_by_virus = []
    self.infected_virus = []

  def contact(self, agent):
    """ 接触する """
    if len(agent.immune.infected_virus) > 0:
      if probability(INFECTION_RATE):
        self.stand_by_virus.append( random.choice(agent.immune.infected_virus) )

  def infection(self, v=None):
    """ 感染する """
    if v is None:
        if len(self.stand_by_virus) > 0 :
            v = random.choice( self.stand_by_virus ) # ランダムに選んで
            if not self.hasImmunity(v) and not self.hasVirus(v) :
                v.cling_point = min_ham_distance(self.tag, v.tag)
                if v.cling_point >=0 :
                    self.infected_virus.append( v )
                    self.stand_by_virus = []
                    return True
        self.stand_by_virus = []
        return False
    else:
        if not self.hasImmunity(v) and not self.hasVirus(v) :
            v.cling_point = min_ham_distance(self.tag, v.tag)
            if v.cling_point >=0 :
                self.infected_virus.append( v )
                self.stand_by_virus = []
                return True
        self.stand_by_virus = []
        return False

  def response(self):
    """ 免疫獲得する
    フリップ : return 1
    免疫獲得済み : return 0
    """
    if len(self.infected_virus) > 0:
      cp = self.infected_virus[0].cling_point # 先頭のウイルスの取りつく位置
      v = self.infected_virus[0]
      for i in range(v.length):
        if self.tag[cp+i] == v.tag[i]:
          continue
        else:
          self.tag = self.tag[:cp+i]+v.tag[i]+self.tag[cp+i+1:]
          return True
      del self.infected_virus[0] # フリップする必要がなければ免疫獲得
    return False

  def hasImmunity(self, v):
    if self.tag.find(v.tag) >= 0:
      return True
    else:
      return False

  def isInfected(self):
    """ has virus or not """
    if len(self.infected_virus) > 0 :
      return True
    else:
      return False

  def hasVirus(self, v):
    for iv in self.infected_virus :
      if iv == v:
        return True
    return False

