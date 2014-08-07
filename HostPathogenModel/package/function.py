#! /usr/bin/python
# coding:utf-8

import random

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

### テスト
def test():
  """ テストプログラム """
  m = [0,0,0,0,0,0,0,0]
  for i in range(500):
    m[random_int(0,7)] += 1
  for i in m:
    print i,
    for j in range(i):
      print '*',
    print 

if __name__ == '__main__':
  print '( test program )'
  test()
