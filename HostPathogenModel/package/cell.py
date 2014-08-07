#! /usr/bin/python
# coding=utf-8

from function import *
from virus import *

class Cell(object):
  """ 細胞
  """
  def __init__(self):
    """ 初期化 """
    self.infected_virus_ = []   # 保持ウイルスの配列
    self.stand_by_virus_ = []   # 待機ウイルスの配列
    
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
    return self.infected_virus_
    
  def clearInfectedVirus(self):
    self.infected_virus_ = []   # 保持ウイルスに空のリストを設定
    """ 感染ウイルスをクリアする """
    
  def getStandByVirus(self):
    """ 待機ウイルス """
    return self.stand_by_virus_
    
  def clearStandByVirus(self):
    """ 待機ウイルスをクリアする """
    self.stand_by_virus_ = []   # 待機ウイルスに空のリストを設定
    
  def pushNewVirus(self,v):
    """ ウイルスを追加する """
    if self.enablePushVirus():  # 新しいウイルスを追加できる状態で
      for iv in self.getInfectedVirus(): # 自分の各保持ウイルスに対して
        if iv.isEqualTagTo(v): return False # タグが同じでなければ
      newv = v.clone()                      # そのウイルスのクローンを作成し
      self.getInfectedVirus().append(newv)  # 保持ウイルスに加えて
      return True                           # 真を返す
    else:                                   # そうでなければ
      return False                          # 偽を返す
      
  def enablePushVirus(self):
    """ ウイルスを追加できるかどうか """
    max_virus = 2
    if len(self.getInfectedVirus()) < max_virus: return True # 最大保持ウイルス未満なら真
    else: return False                                       # そうでなければ偽
    
  def pushStandByVirus(self,v):
    """ 待機ウイルスを追加 """
    self.getStandByVirus().append(v)
    
  def contact(self,neighbors):
    """ 接触する """
    for c in neighbors:         # 各近隣の細胞に対して
      for v in c.getInfectedVirus(): # その細胞の各保持ウイルスのに対して
        if probability(v.getRate()): # そのウイルス固有の感染確率で
          self.pushStandByVirus(v)   # 自分の待機ウイルスに加える
          
  def infection(self):
    """ 待機ウイルスを感染させる """
    for v in self.getStandByVirus(): # 自分の各待機ウイルスに対して
      self.pushNewVirus(v)           # 保持ウイルスに加える処理をして
    self.clearStandByVirus()         # 待機ウイルスの配列をクリアする
    
  def eraseVirus(self,v):
    """ ウイルスを削除 """
    self.getInfectedVirus().remove(v) # 保持ウイルスの配列から指定されたウイルスを削除

def test():
  c = Cell()
  va = Virus(5,5)
  vb = Virus(5,5,100)
  vb.mutationDrift()
  c.pushNewVirus(va)
  print c.getInfectedVirus()
  c.pushNewVirus(vb)
  print c.getInfectedVirus()
  vb.mutationDrift()
  c.pushNewVirus(vb)
  va = Virus(5,5)
  c.pushNewVirus(va)
  print c.getInfectedVirus()

if __name__ == '__main__':
  print '( test program )'
  test()
