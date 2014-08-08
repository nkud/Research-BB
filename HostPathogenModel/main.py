#! /usr/bin/python
# coding=utf-8

# 確率はすべてパーセンテージで表示(0~100)

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
from package.term import *

## メインルーチン
def main():
  width     = 20 # 幅
  vlen      = 3
  vrate     = 50
  vmrate    = 30
  tlen      = 10
  lifespan  = 5
  tcell_num = 10 # T細胞の数
  maxterm   = 500                           # 実行する期間

  term = Term(maxterm)

  fo = open('tcell.dat','w')

  land = Landscape(width)               # 土地を初期化
  tcell_list = TcellList()               # T細胞の集合
  v = Virus(vlen,vrate,vmrate)                # ウイルスを一つ用意する
  land.getCell(0,0).pushNewVirus(v) # 土地の０，０番目の細胞に、ウイルスを感染させる

  for i in range(tcell_num):
    tcell = Tcell(length=tlen)         # T細胞を用意する
    tcell.setX(random_int(0,width-1))   # x座標と
    tcell.setY(random_int(0,width-1))   # y座標をランダムに設定して
    tcell_list.pushTcell(tcell)             # 集合に加える
    land.resistTcell(tcell)         # 土地にT細胞の位置を登録する

  clear_screen()
  while term.progress():
    put_cursor_at(0,0)
    print 'TERM: %d' % term.getTerm()               # 現在の期間
    print 'Tcell: %d' % len(tcell_list.getTcellArray())               # 現在の期間

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
    for tc in tcell_list.getTcellArray(): # 全てのT細胞を
      land.resetTcellMap()
      tc.move(land)               # 移動させて
      land.resistTcell(tc)        # 土地に位置を登録する

# T細胞のウイルス殺傷
    new_tcell = []                # 新しいT細胞の配列を用意する
    for tc in tcell_list.getTcellArray(): # 全てのT細胞に対して
      c = land.getCell(tc.getX(),tc.getY()) # 同じ位置にある細胞に
      for v in c.getInfectedVirus(): # 感染しているウイルス全てに対して
        if tc.hasReceptorMatch(v):   # 受容体を持っていれば
          c.eraseVirus(v)
          #c.clearInfectedVirus() # その細胞からウイルスを除去する
          if probability(100):   # ある確率で
            new_tcell.append(tc.clone()) # そのT細胞のクローンを作成する
    for tc in new_tcell:                 # 新しく作成されたT細胞を
      tcell_list.pushTcell(tc)                   # 集合に加える
      land.resistTcell(tc)

# ウイルスの突然変異
    for i in range(land.getWidth()):   # 全ての土地の
      for j in range(land.getWidth()): # 上にある
        c = land.getCell(i,j)          # 細胞に対して
        for v in c.getInfectedVirus(): # その細胞に感染している全てのウイルスに対して
          v.mutationDrift()            # 連続変異をさせる

# T細胞の寿命
    for tc in tcell_list.getTcellArray():
      tc.aging()
      tc.mutation(rate=10)
      if tc.getAge() > lifespan:
        tcell_list.removeTcell(tc)

    tcell_list.complementTcell(land, 10)

    land.printNumOfVirus()      # ウイルス数マップを表示する
    land.printNumOfTcell()

    land.resetTcellMap()        # T細胞のマップをリセットする

    print '\033[0K',
    for v in land.getCell(0,0).getInfectedVirus():
      print v.getTag(),

    fo.write('%d %d\n' % (term.getTerm(), tcell_list.getTcellListSize()))
    fo.flush()


## プログラム実行
if __name__ == '__main__':
  print 'Host-Pathogen Model'
  print 'author: Naoki Ueda'
  print 'version: 0.1'
  main()

