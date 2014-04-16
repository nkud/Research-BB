#! /usr/bin/python
# coding=utf-8

import random

def probability(p):
  if random.randint(0, 100) < p:
    return True
  else:
    return False