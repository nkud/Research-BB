#! /usr/bin/python
# coding=utf-8

from function import *
from config import *

### Tag
class Tag(object):
  gene = ''
  def __init__(self, len):
    for i in range(len):
      self.gene += str(rand_binary())
