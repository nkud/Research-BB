#! /usr/bin/python
# coding=utf-8

from gene import *
from function import *

### ウイルス
class Virus(Gene):
  def __init__(self, length, rate):
    """ 初期化 """
    super(Virus, self).__init__(length)
    self.infection_rate_ = rate
  def getRate(self):
    """ 感染率 """
    return self.infection_rate_

  def mutationDrift(self):
    """ 抗原連続変異 """
    if probability(20):
      self.tag_[0] = 1
    pass
  def mutationShift(self):
    """ 抗原不連続変異 """
    pass

### テスト
def check():
  pass
if __name__ == '__main__':
  print '( test program )'
  check()
