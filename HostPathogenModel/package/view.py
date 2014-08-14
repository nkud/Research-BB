#! /usr/bin/python
# coding=utf-8

import function
import Tkinter

## ウイルスマップビュー
class VirusMapView(Tkinter.Frame):
  canvas = None
  model = None
  def __init__(self, master=None):
    """ 初期化する """
    Tkinter.Frame.__init__(self, master)
    self.master.title('Virus Map View')

    self.cell_list_ = []
    self.cell_width_ = 10

    self.canvas = Tkinter.Canvas(self, width=600, height=600)
    self.width_ = None

  def appendNewCell(self, x, y, clist):
    """ セルを作成して追加 """
    x += 10
    y += 10
    c = self.canvas.create_rectangle(x, y, x+self.cell_width_, y+self.cell_width_
        , fill='blue', width=0)
    clist.append(c)

  def clearView(self):
    """ 画面をクリア """
    for cell in self.cell_list_:
      self.canvas.delete(cell)
    self.cell_list_ = []

  def updateView(self, model):
    self.clearView()

    model.loop()
    cell_map = model.land.getCellMap()

    for cell in cell_map:
      if cell.isInfected():
        self.appendNewCell(cell.getX()*10, cell.getY()*10, self.cell_list_)

    self.canvas.pack()

  def animation(self):
    """ アニメーションを開始 """
    self.updateView(self.model)
    self.after(1, self.animation)

  def setModel(self, model):
    """ データを設定する """
    self.model = model

if __name__ == '__main__':
  pass