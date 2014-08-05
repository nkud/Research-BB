#! /usr/bin/python
# coding=utf-8

import numpy as np
import matplotlib.pyplot as plt
from pylab import *

def output(width, cell_map):
  x = arange(width+1)
  y = arange(width+1)
  X, Y = meshgrid(x, y)

  Z = array(cell_map)

  pcolor(X, Y, Z)
  colorbar

  show()
Z = array([[24, 32, 12, 16, 21],
  [23, 24, 25, 26, 27],
  [43, 36, 32, 26, 25],
  [30, 32, 25, 21, 20],
  [20, 32, 23, 20, 14]])

print Z

t = [[24, 32, 12, 16, 21],
  [23, 24, 25, 26, 27],
  [43, 36, 32, 26, 25],
  [30, 32, 25, 21, 20],
  [20, 32, 23, 20, 14]]
print t
