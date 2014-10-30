#! /usr/bin/python
# coding:utf-8

from gene import *
from function import *
from virus import *
from landscape import *

import unittest

## T細胞
class Tcell(Gene):
  """ T細胞
  """
  def __init__(self, length, tag=''):
    """ 初期化 """
    super(Tcell, self).__init__(length, tag)
    self.x_ = 0
    self.y_ = 0
    self.age_ = 0

  def move(self, land):
    """ 移動 """
    X = self.getX()
    Y = self.getY()
    if probability(50):
      if probability(50): X += 1
      else: X -= 1
    if probability(50):
      if probability(50): Y += 1
      else: Y -= 1
    if land.isOnMap(X,Y):
      self.setX(X)
      self.setY(Y)

  def setX(self, x):
    """ x座標を設定する """
    self.x_ = x

  def setY(self, y):
    """ y座標を設定する """
    self.y_ = y

  def getX(self):
    """ x座標を返す """
    return self.x_

  def getY(self):
    """ y座標を返す """
    return self.y_

  def getAge(self):
    """ 年齢を返す """
    return self.age_

  def aging(self):
    """ 年をとる """
    self.age_ += 1

  def hasReceptorMatching(self, v):
    """ 受容体を持っているかどうか """
    if self.getLen() < v.getLen(): return False
    if v.getTag() in self.getTag(): return True
    return False

  def clone(self):
    """ クローンを作成する """
    tcell = Tcell(self.getLen(), self.getTag())
    tcell.setX(self.getX())
    tcell.setY(self.getY())
    return tcell

  def willDie(self, maxage):
    if self.getAge() > maxage:
      return True
    else:
      return False

## T細胞テスト
class TestTcellManager(unittest.TestCase):
  def test_clone(self):
    for i in range(1000):
      a = Tcell(10)
      b = a.clone()
      self.assertTrue( a.hasEqualTagTo(b) )
      self.assertTrue( a.getX() == b.getX() )
      self.assertTrue( a.getY() == b.getY() )
      self.assertTrue( b.getAge() == 0 )

  def test_age(self):
    term = 1000
    for i in range(term):
      a = Tcell(10)
      a.age_ = random_int(0,100)
      while True:
        a.aging()
        if a.willDie(maxage=200):
          self.assertTrue( a.getAge() == 201 )
          break

if __name__ == '__main__':
  unittest.main()
