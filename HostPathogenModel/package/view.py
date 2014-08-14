#! /usr/bin/python
# coding=utf-8

import function
import Tkinter

## ウイルスマップビュー
class VirusMapView(Tkinter.Frame):
  canvas = None
  loop = None
  def __init__(self, master=None):
    """ 初期化する """
    Tkinter.Frame.__init__(self, master)
    self.master.title('Virus Map View')

    self.cell_list_ = []
    self.cell_width_ = 10

    self.canvas = Tkinter.Canvas(self, width=600, height=600)

  def createCell(self, x, y):
    """ セルを作成 """
    x += 10
    y += 10
    return self.canvas.create_rectangle(x, y, x+self.cell_width_, y+self.cell_width_
        , fill='blue', width=0)

  def clearView(self):
    """ 画面をクリア """
    for cell in self.cell_list_:
      self.canvas.delete(cell)
    self.cell_list_ = []

  def updateView(self, loop):
    self.clearView()

    loop()

    for i in range(6):
      c = self.createCell(function.random_int(0,10)*10, function.random_int(0,10)*10)
      self.cell_list_.append( c )
    self.canvas.pack()

  def animation(self):
    """ アニメーションを開始 """
    self.updateView(self.loop)
    self.after(1, self.animation)

  def setLoop(self, loop):
    """ データを設定する """
    self.loop = loop

## コンフィグ画面
class Configure(Tkinter.Frame):
  """ コンフィグ画面
  """
  def __init__(self, master=None):
    Tkinter.Frame.__init__(self, master)
    self.master.title('Host-Pathogen Model Confiture')

    # landscape
    width_label = self.createLabel('幅')
    self.width_spin = self.createSpinbox(range(100))
    self.align(width_label, 0, 0)
    self.align(self.width_spin, 0, 1)

    # virus
    rate_label= self.createLabel('感染確率')
    self.rate_spin = self.createSpinbox(range(100))
    self.align(rate_label, 1, 0)
    self.align(self.rate_spin, 1, 1)

    # Tcell
    age_label = self.createLabel('寿命')
    age_spin = self.createSpinbox(range(10))
    self.align(age_label, 2, 0)
    self.align(age_spin, 2, 1)

    b = Tkinter.Button(self, font=('verdana','12'), text='実行', command=self.execute)
    b.grid(row=3,column=0,padx=5,pady=5)


  def createSpinbox(self, values):
    """ スピンボックスを作成する """
    spinbox = Tkinter.Spinbox(self, values=values)
    return spinbox

  def createLabel(self, text):
    """ ラベルを作成する """
    border = 0
    label = Tkinter.Label(self, text=text, bg='white', relief=Tkinter.RIDGE, bd=border)
    return label 

  def align(self, widget, r, c):
    """ ウィジェットを配置する """
    padding_x = 5
    padding_y = 5
    widget.grid(row=r, column=c, padx=padding_x, pady=padding_y)

  def execute(self):
    print 'button'
    print self.width_spin.get()

def hello():
  print 'hello'

if __name__ == '__main__':
  v = VirusMapView()
  v.pack()
  v.setLoop(hello)
  v.animation()
  v.mainloop()
