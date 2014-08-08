#! /usr/bin/python
# coding=utf-8

import unittest

class Term(object):
  """ 期間管理
  """
  def __init__(self, maxterm):
    self.term_ = 0
    self.maxterm_ = maxterm

  def getTerm(self):
    """ 現在期間を取得 """
    return self.term_

  def getMaxTerm(self):
    return self.maxterm_

  def incrementTerm(self):
    """ 期間を進める """
    self.term_ += 1
  
  def progress(self):
    self.incrementTerm()
    if self.getTerm() < self.getMaxTerm(): return True
    else: return False

  def doAtInterval(self, interval):
    """ 指定された間隔で実行 """
    if self.getTerm() % interval == 0: return True
    else: return False

# 期間管理テスト
class TestTerm(unittest.TestCase):
  def test_progress(self):
    term = Term(10000)
    n = 1
    while(term.progress()):
      self.assertTrue( term.getTerm() == n )
      n += 1
  def test_interval(self):
    term = Term(10000)
    interval = 7
    n = 0
    while term.progress():
      if term.doAtInterval(interval):
        self.assertTrue(term.getTerm() % interval == 0)
        n += 1
    self.assertTrue( n == 10000/interval )


if __name__ == '__main__':
  unittest.main()
