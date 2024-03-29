#! /usr/bin/python
# coding=utf-8

from function import *
from cell import *
from leukocyte import *

import unittest

## ランドスケープ
class Landscape(object):
  """ ランドスケープ
  """
  def __init__(self, width):
    """ 初期化 """
    self.width_ = width         # 細胞マップの幅
    self.cell_map_ = []         # 細胞マップ
    self.clearCellMap()         # 細胞マップを初期化する
    self.initCellMap()

  def clearCellMap(self):
    """ 細胞マップをクリアする """
    for i in range( self.getWidth() * self.getWidth() ):
      self.cell_map_.append(None)

  def initCellMap(self):
    for i in range( self.getWidth() * self.getWidth() ):
      newc = Cell()
      newc.setX( i%self.getWidth() )
      newc.setY( i/self.getWidth() )
      self.cell_map_[i] = newc

  def getWidth(self):
    """ 幅 """
    return self.width_

  def getCellMap(self):
    """ 細胞マップ """
    return self.cell_map_

  def getCellAt(self, i, j):
    """ 細胞 """
    n = self.getWidth()*i + j
    return self.cell_map_[n]

  def isInfected(self, i, j):
    """ 感染細胞 """
    return self.getCellAt(i,j).isInfected()

  def isNotInfected(self, i, j):
    """ 未感染細胞 """
    return self.getCell(i,j).isNotInfected()

  def infectionVirusAt(self, v, i, j):
    """ 感染する """
    self.getCellAt(i,j).pushNewVirus(v)

  def neighbors(self, i, j):
    """ 近隣を返す。壁あり """
    cells = []
    for k in [-1,0,1]:
      for l in [-1,0,1]:
        I = i + k
        J = j + l
        if self.isOnMap(I,J) and (k,l) != (0,0):
          cells.append(self.getCellAt(I,J))
    return cells

  def isOnMap(self, i, j):
    """ 細胞マップの上にあるか。壁あり """
    if i < 0: return False
    if j < 0: return False
    if i >= self.getWidth(): return False
    if j >= self.getWidth(): return False
    return True

  def printNumOfVirus(self):
    """ 状態を表示 """
    print ' ',
    for i in range(self.getWidth()):
      print '-',
    print
    for i in range(self.getWidth()):
      print '|',
      for j in range(self.getWidth()):
        n = len(self.getCellAt(i,j).getInfectedVirus())
        print n if n>0 else ' ',
      print '|'
    print ' ',
    for i in range(self.getWidth()):
      print '-',
    print

## ランドスケープテスト
class TestLandscape(unittest.TestCase):
  def test_cell(self):
    land = Landscape(10)
    c = land.getCellAt(0,0)
    c.infected_virus_list_.append(1)
    c = land.getCellAt(0,1)
    c.infected_virus_list_.append(1)
    n = 0
    for c in land.getCellMap():
      if c.isInfected(): n+=1
    self.assertTrue( n == 2 )

  def test_initcellmap(self):
    land = Landscape(100)
    for i in range(land.getWidth()):
      for j in range(land.getWidth()):
        c = land.getCellAt(i, j)
        self.assertTrue( c.getX() == j )
        self.assertTrue( c.getY() == i )

if __name__ == '__main__':
  unittest.main()
