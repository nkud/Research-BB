#! /usr/bin/python
# coding:utf-8

from function import *

import unittest

# 
# Configure
# 
MAX_TAG = 1

## 遺伝子
class Gene(object):
  """ 遺伝子
  遺伝子タグを持つ。
  """
  def __init__(self, length, tag='', base=0):
    """ 初期化 """
    self.tag_ = tag
    self.initTag(length)

  def initTag(self, length):
    if self.tag_ == '':
      for i in range(length):
        self.tag_ += str(random_int(0,MAX_TAG))

  def getLen(self):
    """ タグの長さを返す """
    return len(self.tag_)

  def getTag(self):
    """ タグを返す """
    return self.tag_

  def makeTagArray(self):
    """ タグをリスト化して返す """
    ret = []
    for i in range(getLen()):
      ret.append( getNumAt(i) )
    return ret

  def getNumAt(self, pos):
    """ 指定された位置のタグを返す """
    return int(self.tag_[pos])

  def getStrAt(self, pos):
    return self.tag_[pos]

  def setTagAt(self, num, pos):
    s = self.getTag()
    self.tag_ = '%s%d%s' % (s[0:pos], num, s[pos+1:])

  def isEqualTagTo(self, other):
    """ タグが等しい """
    if self.getTag() == other.getTag():
      return True
    else:
      return False

  def mutation(self,rate=100):
    """ 突然変異させる """
    if probability(rate):
      n = random_int(0, self.getLen()-1)
      t = self.getNumAt(n)
      t += 1 if probability(50) else -1
      while(t>MAX_TAG): t -= MAX_TAG+1
      while(t<0): t += MAX_TAG+1
      self.setTagAt(t,n)

## 遺伝子テスト
class TestGene(unittest.TestCase):
  def test_mutation(self):
    for i in range(1000):
      a = Gene(100)
      sa = a.getTag()
      a.mutation()
      sb = a.getTag()
      self.assertTrue( sa != sb )

  def test_tag(self):
    for i in range(1000):
      length = 5
      t = ''
      for j in range(length):
        t += str(random_int(0,9))
      a = Gene(length, t)
      self.assertTrue( a.getTag() == t )

# テスト
def test():
  g = Gene(10)
  print g.getTag()
  print g.getTagString()
  g.mutation()
  print g.getTagString()

if __name__ == '__main__':
  unittest.main()
