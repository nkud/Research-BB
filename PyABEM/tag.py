#! /usr/bin/python
# coding=utf-8

from function import *
from config import *

### Tag
class Tag(object):
  tag = ''
  def __init__(self, len):
    for i in range(len):
      self.tag += str(rand_binary())
