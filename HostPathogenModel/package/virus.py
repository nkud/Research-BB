#! /usr/bin/python
# coding=utf-8

from gene import *
from function import *

import unittest

### ウイルス
class Virus(Gene):
  """ ウイルス
  """
  def __init__(self, length, rate=100, mutation_rate=100):
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
    self.mutation(self.getMutationRate())

  def mutationShift(self):
    """ 抗原不連続変異 """
    pass

  def clone(self):
    """ クローン """
    v = Virus(self.getLen(), self.getRate(), self.getMutationRate())
    for i in range(self.getLen()):
      v.tag_[i] = self.getTagAt(i)
    return v

class VirusManager(object):
  """ ウイルスの集合を管理する
  """
  def __init__(self):
    self.virus_list_ = []
  
  def pushVirus(self, v):
    self.virus_list_.append(v)
  
  def getVirusList(self):
    return self.virus_list_

  def getVirusListSize(self):
    return len( slef.getVirusList() )

## ウイルステスト
class TestVirus(unittest.TestCase):
  def test_clone(self):
    for i in range(1000):
      a = Virus(100,100,100)
      b = a.clone()
      self.assertTrue(a.isEqualTagTo(b))
  def test_mutation_drift(self):
    for i in range(1000):
      a = Virus(100,100,100)
      b = a.clone()
      a.mutationDrift()
      self.assertFalse(a.isEqualTagTo(b))

def test():
  a = Virus(5,10)
  b = Virus(5,10)
  print a.getTag()
  print b.getTag()
  a.mutationDrift()
  print a.getTag()
  print b.getTag()

if __name__ == '__main__':
  unittest.main()
