#! /usr/bin/python
# coding:utf-8

from function import *

import unittest

# 
# Configure
# 
BASE_TAG = 0
MAX_TAG = 1

## 遺伝子
class Gene(object):
  """ 遺伝子
  遺伝子タグを持つ。
  """
  def __init__(self, length, base=BASE_TAG):
    """ 初期化 """
    self.tag_ = []
    self.length_ = length
    self.initTag()

  def initTag(self):
    for i in range(self.length_):
      self.tag_.append(random_int(0,MAX_TAG))

  def getLen(self):
    """ タグの長さを返す """
    return len(self.tag_)

  def getTag(self):
    """ タグを返す """
    return self.tag_

  def getTagString(self):
    """ タグを文字列化して返す """
    tagstr = ''
    for i in self.getTag():
      tagstr += str(i)
    return tagstr

  def getTagAt(self,i):
    """ 指定された位置のタグを返す """
    return self.tag_[i]

  def isEqualTagTo(self, other):
    """ タグが等しい """
    if self.getLen() != other.getLen(): return False
    for i in range(self.getLen()):
      if self.getTagAt(i) != other.getTagAt(i): return False
    return True

  def mutation(self,rate=100):
    """ 突然変異させる """
    if probability(rate):
      n = random_int(0, self.getLen()-1)
      t = self.getTagAt(n)
      t += 1 if probability(50) else -1
      while(t>MAX_TAG): t -= MAX_TAG+1
      while(t<0): t += MAX_TAG+1
      self.tag_[n] = t

## 遺伝子テスト
class TestGene(unittest.TestCase):
  def test_mutation(self):
    for i in range(1000):
      a = Gene(100,0)
      sa = a.getTagString()
      a.mutation()
      sb = a.getTagString()
      self.assertTrue( sa != sb )

# テスト
def test():
  g = Gene(10)
  print g.getTag()
  print g.getTagString()
  g.mutation()
  print g.getTagString()

if __name__ == '__main__':
  unittest.main()
