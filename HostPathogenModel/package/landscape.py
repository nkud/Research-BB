#! /usr/bin/python
# coding=utf-8

from matplotlib import pyplot as plt
from matplotlib import animation
import numpy as np

from function import *
from virus import *
from cell import *
from leukocyte import *
from view import *

### 細胞マップ
class Landscape(object):
  """ ランドスケープ
  """
  def __init__(self, width):
    """ 初期化 """
    self.width_ = width         # 細胞マップの幅
    self.cell_map_ = []         # 細胞マップ
    self.resetCellMap()         # 細胞マップを初期化する

    self.t_cell_map_ = []
    self.resetTcellMap()

  def resetCellMap(self):
    """ 細胞マップを初期化 """
    for h in range(self.getWidth()):
      t = []
      for w in range(self.getWidth()):
        t.append(Cell())
      self.cell_map_.append(t)

  def resetTcellMap(self):
    """ T細胞マップを初期化 """
    self.t_cell_map_ = []
    for h in range(self.getWidth()):
      t = []
      for w in range(self.getWidth()):
          t.append([])
      self.t_cell_map_.append(t)

  def resistTcell(self,tcell):
    """ T細胞を登録する """
    self.t_cell_map_[tcell.getY()][tcell.getX()].append(tcell)

  def getTcellMap(self):
    """ T細胞マップ """
    return self.t_cell_map_

  def getWidth(self):
    """ 幅 """
    return self.width_

  def getCellMap(self):
    """ 細胞マップ """
    return self.cell_map_

  def getCell(self, x, y):
    """ 細胞 """
    return self.getCellMap()[x][y]

  def isInfected(self, x, y):
    """ 感染細胞 """
    return self.getCell(x,y).isInfected()

  def isNotInfected(self, x, y):
    """ 未感染細胞 """
    return self.getCell(x,y).isNotInfected()

  def infection(self,v,x,y):
    """ 感染する """
    self.getCell(x,y).pushNewVirus(v)

  def neighbors(self,x,y):
    """ 近隣を返す。壁あり """
    cells = []
    for i in [-1,0,1]:
      for j in [-1,0,1]:
        X = x + i
        Y = y + j
        if self.isOnMap(X,Y) and (i,j) != (0,0):
          cells.append(self.getCell(X,Y))
    return cells

  def isOnMap(self,x,y):
    """ 細胞マップの上にあるか。壁あり """
    if x < 0: return False
    if y < 0: return False
    if x >= self.getWidth(): return False
    if y >= self.getWidth(): return False
    return True

  def printNumOfVirus(self):
    """ 状態を表示 """
    for h in range(self.getWidth()):
      for w in range(self.getWidth()):
        print len(self.getCell(h,w).getInfectedVirus()),
      print
    for i in range(self.getWidth()):
      print '-',
    print
  def printNumOfTcell(self):
    """ 状態を表示 """
    for h in range(self.getWidth()):
      for w in range(self.getWidth()):
        print len(self.getTcellMap()[w][h]),
      print
    for i in range(self.getWidth()):
      print '-',
    print

### テスト
def test():
  pass

if __name__ == '__main__':
  print '( test program )'
  test()
