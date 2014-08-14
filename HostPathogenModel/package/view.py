#! /usr/bin/python
# coding=utf-8

import function
import Tkinter
import configure


## ウイルスマップビュー
class VirusMapView(Tkinter.Canvas):
  model = None
  def __init__(self, master=None):
    """ 初期化する """
    Tkinter.Canvas.__init__(self, master, width=600, height=600)

    self.cell_list_ = []
    self.cell_width_ = 10

    # self.canvas = Tkinter.Canvas(self, width=600, height=600)
    self.width_ = None

  def appendNewCell(self, x, y, clist):
    """ セルを作成して追加 """
    x += 10
    y += 10
    c = self.create_rectangle(x, y, x+self.cell_width_, y+self.cell_width_
        , fill='blue', width=0)
    clist.append(c)

  def clearView(self):
    """ 画面をクリア """
    for cell in self.cell_list_:
      self.delete(cell)
    self.cell_list_ = []

  def updateView(self, model):
    """ 更新 """
    self.clearView()

    model.loop()
    cell_map = model.land.getCellMap()

    for cell in cell_map:
      if cell.isInfected():
        self.appendNewCell(cell.getX()*10, cell.getY()*10, self.cell_list_)

    self.pack()

  def animation(self):
    """ アニメーションを開始 """
    self.updateView(self.model)
    self.after(1, self.animation)

  def setModel(self, model):
    """ データを設定する """
    self.model = model

class test(object):
  def getX(self):
    return function.rand_int(0, 10)
  def getY(self):
    return function.rand_int(0, 10)
  def loop(self):
    print 'loop'

class View(Tkinter.Frame):
  def __init__(self, master=None):
    Tkinter.Frame.__init__(self, master)
    self.v = VirusMapView()
    self.v.grid(row=0, column=0)
    c = configure.Configure(self)
    c.grid(row=0, column=1)
    self.v.pack()
    c.pack()

  def setModel(self, model):
    self.v.setModel(model)

  def animation(self):
    self.v.animation()
  

def test_virusmapview():
  v = View()
  v.pack()
  v.mainloop()


if __name__ == '__main__':
  test_virusmapview()