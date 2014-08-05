#! /usr/bin/python
# coding=utf-8

### Config ###################
BASE_TAG = 0
##############################

### 遺伝子
class Gene(object):
  def __init__(self, length, base=BASE_TAG):
    """ 初期化 """
    self.tag_ = []
    for i in range(length): self.tag_.append(base)
  def getLen(self):
    """ タグの長さ """
    return len(self.tag_)
  def getTag(self):
    """ タグ """
    return self.tag_

