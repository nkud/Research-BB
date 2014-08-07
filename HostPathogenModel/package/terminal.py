#! /usr/bin/python
# coding:utf-8

def clear_screen():
  """ 画面をクリアする """
  print '\033[2J'

def put_cursor_at(x,y):
  """カーソルを移動する"""
  print '\033[%d;%dH' % ( x, y )

def test():
  tm = TcellManager()
  tm.pushTcell(Tcell(10))
  tm.printTcellArray()

  tc = Tcell(6)
  v = Virus(7,100)
  print tc.getTag(), v.getTag()
  print tc.hasReceptorMatch(v)

  a = Tcell(5)
  b = a.clone()
  for i in range(10):
    a.move(Landscape(10))
    print a,a.getX(),a.getY(), b,b.getX(),b.getY()

if __name__ == '__main__':
  print '( test program )'
  test()
