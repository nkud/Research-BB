#! /usr/bin/python
# coding=utf-8

from gene import *
from function import *

### T細胞
class Tcell(Gene):
  def __init__(self,length):
    super(Tcell, self).__init__(length)
    self.x = 0
    self.y = 0

  def move(self, land):
    """ 移動 """
    X = self.getX()
    Y = self.getY()
    if probability(50):
      if probability(50): self.x += 1
      else: X -= 1
    if probability(50):
      if probability(50): self.y += 1
      else: Y -= 1
    if land.isOnMap(X,Y):
      self.setX(X)
      self.setY(Y)

  def setX(self,x):
    self.x = x
  def setY(self,y):
    self.y = y
  def getX(self):
    return self.x
  def getY(self):
    return self.y

class TcellManager(object):
  def __init__(self):
    self.t_cell_array = []
  def pushTcell(self, tcell):
    self.t_cell_array.append(tcell)
  def getTcellArray(self):
    return self.t_cell_array
  def printTcellArray(self):
    n = 0
    for tc in self.getTcellArray():
      print '%d:' % n, tc
      n += 1

### テスト
def check():
  tm = TcellManager()
  tm.printTcellArray()
  tm.pushTcell(Tcell(5))
  tm.pushTcell(Tcell(5))
  tm.pushTcell(Tcell(5))
  tm.pushTcell(Tcell(5))
  tm.pushTcell(Tcell(5))
  tm.printTcellArray()

if __name__ == '__main__':
  print '( test program )'
  check()
