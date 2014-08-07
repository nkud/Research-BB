#! /usr/bin/python
# coding=utf-8

# 確率はすべてパーセンテージで表示(0~100)

### Config ###################
WIDTH = 50
V_INFECTION_RATE = 5
##############################

# TODO
# マップを１次元配列にする

from package.function import *
from package.landscape import *
from package.gene import *
from package.cell import *
from package.virus import *
from package.leukocyte import *
from package.view import *
from package.terminal import *

## メインルーチン
def main():
  w = 50                            # 幅
  land = Landscape(w)               # 土地を初期化
  tm = TcellManager()               # T細胞の集合
  v = Virus(5,50)                   # ウイルスを一つ用意する
  land.getCell(0,0).pushNewVirus(v) # 土地の０，０番目の細胞に、ウイルスを感染させる
  cell_num = 10                     # T細胞の数
  for i in range(cell_num):         # だけ
    tcell = Tcell(length=5)         # T細胞を用意する
    tcell.setX(random_int(0,w-1))   # x座標と
    tcell.setY(random_int(0,w-1))   # y座標をランダムに設定して
    tm.pushTcell(tcell)             # 集合に加える
    land.resistTcell(tcell)         # 土地にT細胞の位置を登録する

  term = 100                           # 実行する期間
  clear_screen()
  for i in range(term):                # 計算開始
    put_cursor_at(0,0)
    print 'TERM: %d' % i               # 現在の期間
    print 'Tcell: %d' % len(tm.getTcellArray())               # 現在の期間

# ウイルスの増殖
    for i in range(land.getWidth()):   # 土地の上の
      for j in range(land.getWidth()): # 全ての細胞に対して
        c = land.getCell(i,j)          # その場所の細胞を
        c.contact(land.neighbors(i,j)) # その近隣に対して接触させる
    for i in range(land.getWidth()):   # 土地の上の
      for j in range(land.getWidth()): # 全ての細胞に対して
        c = land.getCell(i,j)          # その細胞を
        c.infection()                  # 感染させる

# T細胞の移動
    for tc in tm.getTcellArray(): # 全てのT細胞を
      tc.move(land)               # 移動させて
      land.resistTcell(tc)        # 土地に位置を登録する

# T細胞のウイルス殺傷
    new_tcell = []                # 新しいT細胞の配列を用意する
    for tc in tm.getTcellArray(): # 全てのT細胞に対して
      c = land.getCell(tc.getX(),tc.getY()) # 同じ位置にある細胞に
      for v in c.getInfectedVirus(): # 感染しているウイルス全てに対して
        if tc.hasReceptorMatch(v):   # 受容体を持っていれば
          #c.eraseVirus(v)
          c.clearInfectedVirus() # その細胞からウイルスを除去する
          if probability(100):   # ある確率で
            new_tcell.append(tc.clone()) # そのT細胞のクローンを作成する
    for tc in new_tcell:                 # 新しく作成されたT細胞を
      tm.pushTcell(tc)                   # 集合に加える

# ウイルスの突然変異
    for i in range(land.getWidth()):   # 全ての土地の
      for j in range(land.getWidth()): # 上にある
        c = land.getCell(i,j)          # 細胞に対して
        for v in c.getInfectedVirus(): # その細胞に感染している全てのウイルスに対して
          v.mutationDrift()            # 連続変異をさせる

# T細胞の寿命
    lifespan = 10
    for tc in tm.getTcellArray():
      tc.aging()
      if tc.getAge() > lifespan:
        tm.removeTcell(tc)

    land.printNumOfVirus()      # ウイルス数マップを表示する
    land.resetTcellMap()        # T細胞のマップをリセットする

### プログラム実行
if __name__ == '__main__':
  print 'Host-Pathogen Model'
  print 'author: Naoki Ueda'
  print 'version: 0.1'
  main()

