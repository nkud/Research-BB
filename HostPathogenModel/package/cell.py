#! /usr/bin/python
# coding=utf-8

from function import *
from virus import *

#### 細胞
class Cell(object):
  def __init__(self):
    """ 初期化 """
    self.infected_virus_ = []
    self.stand_by_virus_ = []
  def isInfected(self):
    """ 感染細胞 """
    if len(self.getInfectedVirus()) > 0: return True
    else: return False
  def isNotInfected(self):
    """ 未感染細胞 """
    if self.isInfected(): return False
    else: return True
  def getInfectedVirus(self):
    """ 感染ウイルス """
    return self.infected_virus_
  def clearInfectedVirus(self):
    self.infected_virus_ = []
  def getStandByVirus(self):
    """ 待機ウイルス """
    return self.stand_by_virus_
  def clearStandByVirus(self):
    self.stand_by_virus_ = []
  def pushNewVirus(self,v):
    """ ウイルスを追加する """
    for iv in self.getInfectedVirus():
      if iv.isEqualTagTo(v): return False
    self.getInfectedVirus().append(v)
    return True
  def pushStandByVirus(self,v):
    """ 待機ウイルスを追加 """
    self.getStandByVirus().append(v)

  def contact(self,neighbors):
    """ 接触する """
    for c in neighbors:
      for v in c.getInfectedVirus():
        if probability(v.getRate()):
          self.pushStandByVirus(v)
  def infection(self):
    """ 待機ウイルスを感染させる """
    for v in self.getStandByVirus():
      self.pushNewVirus(v)
    self.clearStandByVirus()
