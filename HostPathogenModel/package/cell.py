#! /usr/bin/python
# coding=utf-8

from function import *
from virus import *

import unittest

## 細胞
class Cell(object):
  """ 細胞
  """
  def __init__(self):
    """ 初期化 """
    self.infected_virus_list_ = []   # 保持ウイルスの配列
    self.stand_by_virus_list_ = []   # 待機ウイルスの配列
    self.x_ = None
    self.y_ = None

  def getX(self):
    return self.x_
  def getY(self):
    return self.y_
  def setX(self, x):
    self.x_ = x
  def setY(self, y):
    self.y_ = y


  def isInfected(self):
    """ 感染しているかどうか """
    if len(self.getInfectedVirus()) > 0: return True # 保持ウイルスが０より大きければ真
    else: return False                               # そうでなければ偽

  def isNotInfected(self):
    """ 未感染かどうか """
    if self.isInfected(): return False # 感染していれば偽
    else: return True                  # そうでなければ真

  def getInfectedVirus(self):
    """ 感染ウイルスを返す """
    return self.infected_virus_list_

  def clearInfectedVirus(self):
    self.infected_virus_list_ = []   # 保持ウイルスに空のリストを設定
    """ 感染ウイルスをクリアする """

  def getStandByVirus(self):
    """ 待機ウイルス """
    return self.stand_by_virus_list_

  def clearStandByVirus(self):
    """ 待機ウイルスをクリアする """
    self.stand_by_virus_list_ = []   # 待機ウイルスに空のリストを設定

  def pushNewVirus(self,v):
    """ ウイルスを追加する """
    if self.capPushVirus():  # 新しいウイルスを追加できる状態で
      for iv in self.getInfectedVirus(): # 自分の各保持ウイルスに対して
        if iv.hasEqualTagTo(v): return False # タグが同じでなければ
      self.getInfectedVirus().append(v)  # 保持ウイルスに加えて
      return True                           # 真を返す
    else:                                   # そうでなければ
      return False                          # 偽を返す

  def capPushVirus(self):
    """ ウイルスを追加できるかどうか """
    max_virus = 3
    if len(self.getInfectedVirus()) < max_virus: return True # 最大保持ウイルス未満なら真
    else: return False                                       # そうでなければ偽

  def pushStandByVirusClone(self,v):
    """ 待機ウイルスを追加 """
    newv = v.clone()
    self.getStandByVirus().append(newv)

  def contact(self, neighbors):
    """ 接触する """
    for cell in neighbors:         # 各近隣の細胞に対して
      for virus in cell.getInfectedVirus(): # その細胞の各保持ウイルスのに対して
        if probability(virus.getRate()): # そのウイルス固有の感染確率で
          virus.mutationDrift() # 固有の確率で突然変異させて
          self.pushStandByVirusClone(virus)   # 自分の待機ウイルスに加える

  def infection(self):
    """ 待機ウイルスを感染させる """
    while len(self.getStandByVirus()) > 0:
      v = random_choose(self.getStandByVirus())
      if self.pushNewVirus(v):
        self.clearStandByVirus()
        return True
      else: self.eraseStandByVirus(v)
    self.clearStandByVirus()
    return False

   # for v in self.getStandByVirus(): # 自分の各待機ウイルスに対して
   #   self.pushNewVirus(v)           # 保持ウイルスに加える処理をして
   # self.clearStandByVirus()         # 待機ウイルスの配列をクリアする

  def eraseVirus(self,v):
    """ ウイルスを削除 """
    self.infected_virus_list_.remove(v) # 保持ウイルスの配列から指定されたウイルスを削除

  def eraseStandByVirus(self, v):
    """ 待機ウイルスを削除 """
    self.stand_by_virus_list_.remove(v)

## 細胞テスト
class TestCell(unittest.TestCase):
  pass

if __name__ == '__main__':
  unittest.main()

