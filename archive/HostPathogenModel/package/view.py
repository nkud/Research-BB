#! /usr/bin/python
# coding=utf-8

import function
import Tkinter
import configure

class InfoPanel(Tkinter.Frame):
  def __init__(self, master=None, **options):
    Tkinter.Frame.__init__(self, master, **options)
    self.term_panel = Tkinter.Label(self, text='info')
    self.term_panel.pack()

## メインビュー
class MainViewController(Tkinter.Frame):
  def __init__(self, master=None):
    Tkinter.Frame.__init__(self, master)
    self.title = 'Host-Pathogen Model'

    self.vmv = VirusMapViewController(self, relief=Tkinter.RIDGE, bd=0)
    self.vmv.grid(row=1, column=0, padx=5, pady=5)

    # self.info_panel = InfoPanel(self, relief=Tkinter.GROOVE, bd=1)
    # self.info_panel.grid(row=0, column=0, columnspan=2, sticky=Tkinter.W+Tkinter.E)

    self.cv = configure.ConfigurePanel(self, relief=Tkinter.RAISED, bd=0)
    self.cv.grid(row=1, column=1, padx=5, pady=5)

  def setModel(self, model):
    self.vmv.virus_map_.setModel(model)

  def stop(self):
    self.vmv.virus_map_.after_cansel()

  def animation(self):
    self.initialize()
    self.vmv.virus_map_.cell_width_ = 400/self.vmv.virus_map_.model.land.getWidth()
    self.vmv.virus_map_.animation()

  def initialize(self):
    self.vmv.virus_map_.model.width = self.cv.width.getValue()
    self.vmv.virus_map_.model.vlen = self.cv.vlen.getValue()
    self.vmv.virus_map_.model.vrate = self.cv.vrate.getValue()
    self.vmv.virus_map_.model.vmrate = self.cv.vmrate.getValue()
    self.vmv.virus_map_.model.tlen = self.cv.tlen.getValue()
    self.vmv.virus_map_.model.lifespan = self.cv.lifespan.getValue()
    self.vmv.virus_map_.model.tcell_num = self.cv.tcell_num.getValue()
    self.vmv.virus_map_.model.maxterm = self.cv.maxterm.getValue()

    self.vmv.virus_map_.model.initialize()

class VirusMapViewController(Tkinter.Frame):
  def __init__(self, master=None, **options):
    Tkinter.Frame.__init__(self, master, width=400, height=500, **options)

    self.vip = VirusInfoPanel(self, relief=Tkinter.GROOVE, bd=0)
    self.vip.pack()

    title_label_ = Tkinter.Label(self, text='ウイルスに感染した細胞マップ（青色）')
    title_label_.pack(anchor=Tkinter.W)

    self.virus_map_ = VirusMap(self)
    self.virus_map_.pack()

class VirusInfoPanel(Tkinter.Frame):
  """docstring for VirusInfoPanel"""
  def __init__(self, master=None, **options):
    Tkinter.Frame.__init__(self, master, width=400, height=200, **options)

    self.term_ = Tkinter.StringVar()
    self.term_.set( '経過期間 : %6d' % 0 )
    self.term_label_ = Tkinter.Label(self, textvariable=self.term_)
    self.term_label_.pack()

## ウイルスマップビュー
class VirusMap(Tkinter.Canvas):
  model = None
  def __init__(self, master=None, **options):
    """ 初期化する """
    Tkinter.Canvas.__init__(self, master, width=400, height=400, bg='white', **options)

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
    self.master.vip.term_.set( '経過期間 : %6d' % self.model.term.getTerm() )

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
  v = VirusMapViewController()
  v.pack()
  v.mainloop()

if __name__ == '__main__':
  test_virusmapview()
