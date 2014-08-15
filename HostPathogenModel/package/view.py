#! /usr/bin/python
# coding=utf-8

import function
import Tkinter
import configure

## メインビュー
class MainView(Tkinter.Frame):
  def __init__(self, master=None):
    Tkinter.Frame.__init__(self, master)
    self.title = 'Host-Pathogen Model'

    self.vmv = VirusMapView(self, relief=Tkinter.RIDGE, bd=1)
    self.vmv.grid(row=0, column=0, padx=5, pady=5)

    self.cv = configure.Configure(self, relief=Tkinter.SUNKEN, bd=0)
    self.cv.grid(row=0, column=1, padx=5, pady=5)

  def setModel(self, model):
    self.vmv.setModel(model)

  def stop(self):
    self.vmv.after_cansel()

  def animation(self):
    self.initialize()
    self.vmv.cell_width_ = 400/self.vmv.model.land.getWidth()
    self.vmv.animation()

  def initialize(self):
    self.vmv.model.width = self.cv.width.getValue()
    self.vmv.model.vlen = self.cv.vlen.getValue()
    self.vmv.model.vrate = self.cv.vrate.getValue()
    self.vmv.model.vmrate = self.cv.vmrate.getValue()
    self.vmv.model.tlen = self.cv.tlen.getValue()
    self.vmv.model.lifespan = self.cv.lifespan.getValue()
    self.vmv.model.tcell_num = self.cv.tcell_num.getValue()
    self.vmv.model.maxterm = self.cv.maxterm.getValue()

    self.vmv.model.initialize()

## ウイルスマップビュー
class VirusMapView(Tkinter.Canvas):
  model = None
  def __init__(self, master=None, **options):
    """ 初期化する """
    Tkinter.Canvas.__init__(self, master, width=400, height=400, **options)

    self.cell_list_ = []
    self.cell_width_ = 6

    # self.canvas = Tkinter.Canvas(self, width=600, height=600)
    self.width_ = None

  def appendNewCell(self, x, y, clist):
    """ セルを作成して追加 """
    c = self.create_rectangle(x, y, x+self.cell_width_, y+self.cell_width_
        , fill='blue', width=0)
    clist.append(c)

  def clearView(self):
    """ 画面をクリア """
    for cell in self.cell_list_:
      self.delete(cell)
    self.cell_list_ = []

  def loopModel(self):
    """ 更新 """
    self.clearView()

    self.model.loop()
    cell_map = self.model.land.getCellMap()

    for cell in cell_map:
      if cell.isInfected():
        self.appendNewCell(cell.getX()*self.cell_width_, cell.getY()*self.cell_width_, self.cell_list_)

  def animation(self):
    """ アニメーションを開始 """
    self.loopModel()
    if self.model.term.progress():
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


def test_virusmapview():
  v = MainView()
  v.pack()
  v.mainloop()


if __name__ == '__main__':
  test_virusmapview()
