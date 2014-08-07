#! /usr/bin/python
# coding=utf-8

from gene import *
from function import *
from virus import *
from landscape import *

### T細胞
class Tcell(Gene):
  """ T細胞
  """
  def __init__(self, length):
    """ 初期化 """
    super(Tcell, self).__init__(length)
    self.x = 0
    self.y = 0

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
    self.x = x
  def setY(self, y):
    self.y = y
  def getX(self):
    return self.x
  def getY(self):
    return self.y
    
  def hasReceptorMatch(self, v):
    """ 受容体を持っているかどうか """
    if self.getLen() < v.getLen(): return False
    if v.getTagString() in self.getTagString(): return True
    return False
  def clone(self):
    """ クローンを作成する """
    tcell = Tcell(self.getLen())
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

### テスト
def check():
  tm = TcellManager()
  tm.pushTcell(Tcell(10))
  tm.printTcellArray()

  tc = Tcell(6)
  v = Virus(7,100)
  print tc.getTag(), v.getTag()
  print tc.hasReceptorMatch(v)

  a = Tcell(5)
  b = a.clone()
  for i in range(10):
    a.move(Landscape(10))
    print a,a.getX(),a.getY(), b,b.getX(),b.getY()

if __name__ == '__main__':
  print '( test program )'
  check()
