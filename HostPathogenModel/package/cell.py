#! /usr/bin/python
# coding=utf-8

from function import *
from virus import *

#### 細胞
class Cell(object):
  def __init__(self):
    """ 初期化 """
    self.infected_virus_ = []
    self.stand_by_virus_ = []
  def isInfected(self):
    """ 感染細胞 """
    if len(self.getInfectedVirus()) > 0: return True
    else: return False
  def isNotInfected(self):
    """ 未感染細胞 """
    if self.isInfected(): return False
    else: return True
  def getInfectedVirus(self):
    """ 感染ウイルス """
    return self.infected_virus_
  def clearInfectedVirus(self):
    self.infected_virus_ = []
  def getStandByVirus(self):
    """ 待機ウイルス """
    return self.stand_by_virus_
  def clearStandByVirus(self):
    self.stand_by_virus_ = []
  def pushNewVirus(self,v):
    """ ウイルスを追加する """
    for iv in self.getInfectedVirus():
      if iv.isEqualTagTo(v): return False
    self.getInfectedVirus().append(v)
    return True
  def pushStandByVirus(self,v):
    """ 待機ウイルスを追加 """
    self.getStandByVirus().append(v)

  def contact(self,neighbors):
    """ 接触する """
    for c in neighbors:
      for v in c.getInfectedVirus():
        if probability(v.getRate()):
          self.pushStandByVirus(v)
  def infection(self):
    """ 待機ウイルスを感染させる """
    for v in self.getStandByVirus():
      self.pushNewVirus(v)
    self.clearStandByVirus()

### 細胞マップ
class CellMap(object):
  def __init__(self, width):
    """ 初期化 """
    self.width_ = width         # 細胞マップの幅
    self.cell_map_ = []         # 細胞マップ
    self.resetCellMap()         # 細胞マップを初期化する

  def resetCellMap(self):
    """ 細胞マップを初期化 """
    for h in range(self.getWidth()):
      t = []
      for w in range(self.getWidth()):
        t.append(Cell())
      self.cell_map_.append(t)

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
  def printState(self,func):
    """ 状態を表示 """
    for h in range(self.getWidth()):
      for w in range(self.getWidth()):
        print '%3d\t ' % len(self.getCell(h,w).func()),
      print
    for i in range(self.getWidth()):
      print '-',
    print


cm = CellMap(50)
v = Virus(5,100)
cm.infection(v,5,5)
cm.printNumOfVirus()
for k in range(50):
  for i in range(50):
    for j in range(50):
      cm.getCell(i,j).contact(cm.neighbors(i,j))
  for i in range(50):
    for j in range(50):
      cm.getCell(i,j).infection()
  cm.printNumOfVirus()
