#! /usr/bin/python
# coding=utf-8

# 確率はすべてパーセンテージで表示(0~100)

### Config ###################
WIDTH = 50
V_INFECTION_RATE = 5
##############################

from package.gene import *
from package.function import *
from package.cell import *
from package.virus import *
from package.view import *

### メインルーチン
def main():
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

  mp = []
  for h in range(cm.getWidth()):
    t = []
    for w in range(cm.getWidth()):
      t.append(cm.getCell(h,w).isInfected())
    mp.append(t)
  print mp
  output(cm.getWidth(),mp)

### プログラム実行
if __name__ == '__main__':
  print 'Host-Pathogen Model'
  print 'author: Naoki Ueda'
  print 'version: 0.1'
  main()

