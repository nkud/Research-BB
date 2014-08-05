#! /usr/bin/python
# coding=utf-8

# 確率はすべてパーセンテージで表示(0~100)

### Config ###################
WIDTH = 50
V_INFECTION_RATE = 5
##############################

import random

from package.gene import *
from package.function import *
from package.cell import *


### T細胞
class Tcell(Gene):
  def __init__(self, length):
    """ 初期化 """
    super(Tcell, self).__init__(length)

### ウイルス
class Virus(Gene):
  def __init__(self, length, rate):
    """ 初期化 """
    super(Virus, self).__init__(length)
    self.infection_rate_ = rate
  def getRate(self):
    """ 感染率 """
    return self.infection_rate_
### メインルーチン
def main():
  print '--- Host-Pathogen Model'
  cell = Cell()
  cm = CellMap(10)
  v = Virus(rate=5,length=2)
  print v.getTag()
  print cell.isInfected(), cell.isNotInfected()
  cell.infected_virus_.append(v)
  print cell.isInfected(), cell.isNotInfected()
  print '---------'
  cm.printState()
  cm.infection(v,1,5)
  print '---------'
  cm.printState()

### プログラム実行
if __name__ == '__main__':
  main()

