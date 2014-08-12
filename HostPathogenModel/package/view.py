#! /usr/bin/python
# coding=utf-8

from matplotlib import pyplot as plt
from matplotlib import animation
import numpy as np
from pylab import *

import Tkinter

class View(object):
  def __init__(self):
    pass

## コンフィグ画面
class Configure(Tkinter.Frame):
  """ コンフィグ画面
  """
  pass

def output(width, cell_map):
  x = arange(width+1)
  y = arange(width+1)
  X, Y = meshgrid(x, y)

  Z = array(cell_map)

  pcolor(X, Y, Z)
  colorbar

  show()

def animate(width, ar):
  fig = plt.figure()
  x = arange(width+1)
  y = arange(width+1)
  X, Y = meshgrid(x, y)
  Z = array(ar)

  ims = []
  for add in np.arange(15):
    ims.append((plt.pcolor(X, Y, Z),))

  im_ani = animation.ArtistAnimation(fig, ims, interval=50,
      repeat_delay=100, blit=False)
#ani.save("cycloid.mp4")
  plt.show()

### テスト #############################
def test():
  t = [[24, 32, 12, 16, 21],
    [23, 24, 25, 26, 27],
    [43, 36, 32, 26, 25],
    [30, 32, 25, 21, 20],
    [20, 32, 23, 20, 14]]

  print t

  Z = array([[0, 32, 12, 16, 21],
    [23, 0, 0, 26, 27],
    [43, 0, 32, 26, 25],
    [30, 0, 25, 21, 20],
    [20, 0, 23, 20, 14]])

  print Z

  fig = plt.figure()

  width = 5

  x = arange(width+1)
  y = arange(width+1)
  X, Y = meshgrid(x, y)

  ims = []
  for i in range(20):
    t[0][0] += 1
    Z = array(t)
    ims.append((plt.pcolor(X, Y, Z),))

  im_ani = animation.ArtistAnimation(fig, ims, interval=50, repeat_delay=100, blit=False)
#ani.save("cycloid.mp4")
  plt.show()

if __name__ == '__main__':
  print '( test program )'

  c = Configure()
  c.mainloop()
