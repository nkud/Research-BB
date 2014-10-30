#! /usr/bin/python
# coding:utf-8

import random
import unittest

def probability(prob):
  """ 確率
  Args:
    prob: 指定する確率
  Returns:
    真偽値
  """
  if prob > random.uniform(0,100): return True
  else: return False

def random_int(minimum, maximum):
  """ 確率関数
  Args:
    minimum: 最小値
    maximum: 最大値
  Returns:
    最小値 <= 返り値 <= 最大値
  """
  return random.randint(minimum, maximum)

def random_choose(alist):
  """ 確率選択
  Args:
    alist: 選択されるリスト
  Returns:
    リストの中のどれか１つ
  """
  n = len(alist)
  return alist[ random_int(0,n-1) ]

## 関数テスト
class TestRandom(unittest.TestCase):
  def test_probability(self):
    for i in range(1000):
      self.assertTrue(probability(100))
      self.assertFalse(probability(0))

  def test_random_int(self):
    for i in range(1000):
      self.assertTrue(random_int(0,1) in [0,1])
      self.assertTrue(random_int(0,99) in range(100))

  def test_choose(self):
    l = []
    for i in range(1000):
      l.append(i)
    for i in range(2000):
      n = random_choose(l)
      self.assertTrue( n>=0 and n<=999 )

if __name__ == '__main__':
  unittest.main()
