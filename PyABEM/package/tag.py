#! /usr/bin/python
# coding=utf-8

from function import *
from config import *

### Tag
class Tag(object):
  tag = ''
  def __init__(self, length):
    for i in range(length):
      self.tag += str(rand_binary())
    self.length = length

class MultiTag(object):
  tags = []
  length = 0
  def __init__(self, length, num):
    for i in range(num):
      t = ''
      for l in range(length):
        t += str(rand_binary())
      self.tags.append(t)
    self.length = length
    self.num = num