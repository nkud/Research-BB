#! /usr/bin/python
# coding:utf-8

# 
# Configure
# 
BASE_TAG = 0

class Gene(object):
  """ 遺伝子
  遺伝子タグを持つ。
  """
  def __init__(self, length, base=BASE_TAG):
    """ 初期化 """
    self.tag_ = []
    for i in range(length): self.tag_.append(base)
  def getLen(self):
    """ タグの長さを返す """
    return len(self.tag_)
  def getTag(self):
    """ タグを返す """
    return self.tag_
  def getTagString(self):
    """ タグを文字列化して返す """
    tagstr = ''
    for i in self.getTag():
      tagstr += str(i)
    return tagstr
  def getTagAt(self,i):
    """ 指定された位置のタグを返す """
    return self.tag_[i]
  def isEqualTagTo(self,other):
    """ タグが等しい """
    if self.getLen() != other.getLen(): return False
    for i in range(self.getLen()):
      if self.getTagAt(i) != other.getTagAt(i): return False
    return True

# テスト
def check():
  g = Gene(10)
  print g.getTag()
  print g.getTagString()

if __name__ == '__main__':
  print '( test program )'
  check()
