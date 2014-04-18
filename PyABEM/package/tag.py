#! /usr/bin/python
# coding=utf-8

from function import *
from config import *

### Tag
class Tag(object):
  def __init__(self, length):
    self.tag = ''
    for i in range(length):
      self.tag += str(rand_binary())
    self.length = length

class MultiTag(object):
  def __init__(self, length, num):
    self.tags = []
    self.length = length
    for i in range(num):
      t = ''
      for l in range(length):
        t += str(rand_binary())
      self.tags.append(t)
    self.length = length
    self.num = num