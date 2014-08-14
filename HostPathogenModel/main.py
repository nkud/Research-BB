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
from package.terminal import *
from package.term import *
from package.view import *

class HostPathogenModel(object):
  """宿主内動態モデル
  """
  def __init__(self):
    """ 初期化 """
    self.width     = 20 # 幅
    self.vlen      = 3
    self.vrate     = 50
    self.vmrate    = 30
    self.tlen      = 10
    self.lifespan  = 5
    self.tcell_num = 5 # T細胞の数
    self.maxterm   = 500                           # 実行する期間

    self.term = Term(self.maxterm)

    self.fo = open('out.dat','w')

    self.land = Landscape(self.width)               # 土地を初期化
    self.tcell_list = TcellManager()               # T細胞の集合
    v = Virus(self.vlen,self.vrate,self.vmrate)                # ウイルスを一つ用意する
    self.land.getCellAt(0,0).pushNewVirus(v) # 土地の０，０番目の細胞に、ウイルスを感染させる

    for i in range(self.tcell_num):
      tcell = Tcell(length=self.tlen)         # T細胞を用意する
      tcell.setX(random_int(0,self.width-1))   # x座標と
      tcell.setY(random_int(0,self.width-1))   # y座標をランダムに設定して
      self.tcell_list.pushTcell(tcell)             # 集合に加える
      self.land.resistTcell(tcell)         # 土地にT細胞の位置を登録する
    clear_screen()

  def execute(self):
    """ 計算実行 """
    while self.term.progress():
      self.loop()

  def loop(self):
    """ メインループ """
    put_cursor_at(0,0)
    print 'TERM: %d' % self.term.getTerm()               # 現在の期間
    print 'Tcell: %d' % len(self.tcell_list.getTcellArray())               # 現在の期間

# ウイルスの増殖
    for i in range(self.land.getWidth()):   # 土地の上の
      for j in range(self.land.getWidth()): # 全ての細胞に対して
        c = self.land.getCellAt(i,j)          # その場所の細胞を
        c.contact(self.land.neighbors(i,j)) # その近隣に対して接触させる
    for i in range(self.land.getWidth()):   # 土地の上の
      for j in range(self.land.getWidth()): # 全ての細胞に対して
        c = self.land.getCellAt(i,j)          # その細胞を
        c.infection()                  # 感染させる

# T細胞の移動
    for tc in self.tcell_list.getTcellArray(): # 全てのT細胞を
      self.land.clearTcellMap()
      tc.move(self.land)               # 移動させて
      self.land.resistTcell(tc)        # 土地に位置を登録する

# T細胞のウイルス殺傷
    new_tcell = []                # 新しいT細胞の配列を用意する
    for tc in self.tcell_list.getTcellArray(): # 全てのT細胞に対して
      c = self.land.getCellAt(tc.getX(),tc.getY()) # 同じ位置にある細胞に
      for v in c.getInfectedVirus(): # 感染しているウイルス全てに対して
        if tc.hasReceptorMatching(v):   # 受容体を持っていれば
          #c.eraseVirus(v)
          c.clearInfectedVirus() # その細胞からウイルスを除去する
          if probability(100):   # ある確率で
            new_tcell.append(tc.clone()) # そのT細胞のクローンを作成する
    for tc in new_tcell:                 # 新しく作成されたT細胞を
      self.tcell_list.pushTcell(tc)                   # 集合に加える
      self.land.resistTcell(tc)

# T細胞の寿命
    for tc in self.tcell_list.getTcellArray():
      tc.aging()
      tc.mutation(rate=10)
      if tc.getAge() > self.lifespan:
        self.tcell_list.removeTcell(tc)
        self.land.removeTcell(tc)

    self.tcell_list.complementTcell(self.land, 10)

    self.land.printNumOfVirus()      # ウイルス数マップを表示する
#    land.printNumOfTcell()

    self.land.clearTcellMap()        # T細胞のマップをリセットする

    print '\033[0K',
    for v in self.land.getCellAt(0,0).getInfectedVirus():
      print v.getTag(),

    self.fo.write('%d %d\n' % (self.term.getTerm(), self.tcell_list.getTcellListSize()))
    self.fo.flush()

## プログラム実行
if __name__ == '__main__':
  print 'Host-Pathogen Model'
  print 'author: Naoki Ueda'
  print 'version: 0.1'
  #main()
  h = HostPathogenModel()
  h.execute()

