#! /usr/bin/python
# coding=utf-8

from gene import *
from function import *

import unittest

## ウイルス
#
# 遺伝子、感染率、突然変異率
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
    v.setTag( self.getTag() )
    return v

## ウイルスマネージャー
class VirusManager(object):
  """ ウイルスの集合を管理する
  """
  def __init__(self):
    """ 初期化 """
    self.virus_list_ = []
  
  def pushVirus(self, v):
    """ ウイルスを追加する """
    self.virus_list_.append(v)
  
  def getVirusList(self):
    """ ウイルスリストを取得する """
    return self.virus_list_

  def getVirusListSize(self):
    """ ウイルス数を取得する """
    return len( slef.getVirusList() )

## ウイルステスト
class TestVirus(unittest.TestCase):
  def test_clone(self):
    for i in range(1000):
      a = Virus(100,100,100)
      b = a.clone()
      self.assertTrue(a.hasEqualTagTo(b))

  def test_mutation_drift(self):
    for i in range(1000):
      a = Virus(100,100,100)
      b = a.clone()
      a.mutationDrift()
      self.assertFalse(a.hasEqualTagTo(b))

if __name__ == '__main__':
  unittest.main()
