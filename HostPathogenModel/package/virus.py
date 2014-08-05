#! /usr/bin/python
# coding=utf-8

from gene import *

### ウイルス
class Virus(Gene):
  def __init__(self, length, rate):
    """ 初期化 """
    super(Virus, self).__init__(length)
    self.infection_rate_ = rate
  def getRate(self):
    """ 感染率 """
    return self.infection_rate_

