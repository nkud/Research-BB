#! /usr/bin/python
# coding=utf-8

from gene import *
from function import *

### ウイルス
class Virus(Gene):
  """ ウイルス
  """
  def __init__(self, length, rate, mutation_rate=5):
    """ 初期化 """
    super(Virus, self).__init__(length)
    self.infection_rate_ = rate
    self.mutation_rate_ = mutation_rate
  def getRate(self):
    """ 感染率 """
    return self.infection_rate_
  def getMutationRate(self):
    return self.mutation_rate_

  def mutationDrift(self):
    """ 抗原連続変異 """
    if probability(self.getMutationRate()):
      self.tag_[0] = 1
    pass
  def mutationShift(self):
    """ 抗原不連続変異 """
    pass
  def clone(self):
    """ クローン """
    v = Virus(self.getLen(), self.getRate())
    v.tag_[0] = self.getTagAt(0)
    return v

### テスト
def test():
  a = Virus(5,10)
  b = Virus(5,10)
  print a.getTag()
  print b.getTag()
  a.mutationDrift()
  print a.getTag()
  print b.getTag()

if __name__ == '__main__':
  print '( test program )'
  test()
