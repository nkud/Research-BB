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


class TcellManager(object):
  """ T細胞マネージャー
  T細胞の集合体を扱う。
  """
  def __init__(self):
    """ 初期化 """
    self.t_cell_array = []

  def pushTcell(self, tcell):
    """ T細胞を追加 """
    self.t_cell_array.append(tcell)

  def getTcellArray(self):
    """ T細胞の配列を取得 """
    return self.t_cell_array

  def printTcellArray(self):
    n = 0
    for tc in self.getTcellArray():
      print '%d:' % n, tc
      n += 1

  def removeTcell(self, tcell):
    """ 指定したT細胞を配列から削除 """
    self.t_cell_array.remove(tcell)

  def getTcellListSize(self):
    """ T細胞集合のサイズを返す """
    return len(self.getTcellArray())

  def complementTcell(self, land, min_tcell):
    """ T細胞を保管する """
    tlen = self.getTcellArray()[0].getLen()
    while self.getTcellListSize() < min_tcell:
      tc = Tcell(length=tlen)
      tc.setX( random_int( 0, land.getWidth()-1 ) )
      tc.setY( random_int( 0, land.getWidth()-1 ) )
      self.pushTcell( tc )
      land.resistTcell( tc )

## T細胞テスト
class TestTcellManager(unittest.TestCase):
  def setUp(self):
    self.tclist = TcellManager()

  def test_push(self):
    num = 1000
    for i in range(num):
      self.tclist.pushTcell(Tcell(100))
    self.assertTrue( self.tclist.getTcellListSize() == num )

  def test_clone(self):
    for i in range(1000):
      a = Tcell(10)
      b = a.clone()
      self.assertTrue( a.hasEqualTagTo(b) )
      self.assertTrue( a.getX() == b.getX() )
      self.assertTrue( a.getY() == b.getY() )
      self.assertTrue( b.getAge() == 0 )

if __name__ == '__main__':
  unittest.main()
