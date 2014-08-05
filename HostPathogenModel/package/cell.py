#! /usr/bin/python
# coding=utf-8

#### 細胞
class Cell(object):
  def __init__(self):
    """ 初期化 """
    self.infected_virus_ = []
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
  def pushVirus(self,v):
    """ ウイルスを追加する """
    self.getInfectedVirus().append(v)

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
    self.getCell(x,y).pushVirus(v)
  def printState(self):
    for h in range(self.getWidth()):
      for w in range(self.getWidth()):
        print self.getCell(h,w).isInfected(),
      print '\n'
