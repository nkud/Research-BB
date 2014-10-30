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
  def __init__(self, length, irate, mrate):
    """ 初期化 """
    super(Virus, self).__init__(length)
    self.infection_rate_ = irate
    self.mutation_rate_ = mrate

  def getInfectionRate(self):
    """ 感染率 """
    return self.infection_rate_

  def getMutationRate(self):
    return self.mutation_rate_

  def mutationDrift(self):
    """ 抗原連続変異 """
    self.mutation(prob=self.getMutationRate())

  def mutationShift(self):
    """ 抗原不連続変異 """
    pass

  def clone(self):
    """ クローン """
    v = Virus(self.getLen(), self.getInfectionRate(), self.getMutationRate())
    v.setTag( self.getTag() )
    return v

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
