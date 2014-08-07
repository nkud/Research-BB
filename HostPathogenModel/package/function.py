#! /usr/bin/python
# coding=utf-8

import random

def probability(prob):
  """ 確率 """
  if prob > random.uniform(0,100): return True
  else: return False

def random_int(minimum, maximum):
  return random.randint(minimum, maximum)

### テスト
def check():
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
  check()
