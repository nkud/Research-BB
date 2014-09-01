#! /usr/bin/python
# -*- encoding:utf-8 -*-

import Tkinter
import sys
import os

FONT = ('monospace', '12')

def create_spinbox(master, f, t):
  """ スピンボックスを作成する """
  spinbox = Tkinter.Spinbox(master, from_=f, to=t, width=10)
  return spinbox

def create_label(master, text, **options):
  """ ラベルを作成する """
  border = 0
  label = Tkinter.Label(master, text=text, relief=Tkinter.GROOVE, bd=border, width=20, **options)
  return label

def put_widget(widget, row, column, padx=5, pady=5):
  """ ウィジェットを配置する """
  widget.grid(row=row, column=column, padx=padx, pady=pady)

def create_field(master, text, values, pos):
  """ 入力フィールドを作成する """
  label = create_label(master, text)
  spinbox = create_spinbox(master, values)
  put_widget(label, pos, 0)
  put_widget(spinbox, pos, 1)
  return label, spinbox

def create_button(master, font, text, command, row, column, padx=5, pady=5):
  """ ボタンを作成する """
  button = Tkinter.Button(master, font=font, text=text, command=command)
  button.grid(row=row, column=column, padx=padx, pady=pady)
  return button

class ParameterField(Tkinter.Frame):
  """パラメータフィールド 
  """
  def __init__(self, master, text, f, t, bg='white'):
    Tkinter.Frame.__init__(self, master)
    self.label = create_label(self, text, bg=bg)
    self.spinbox = create_spinbox(self, f, t)
    put_widget(self.label, 0, 0)
    put_widget(self.spinbox, 0, 1)

  def getValue(self):
    """ スピンボックスの値を取得 """
    return int(self.spinbox.get())

class Configure(Tkinter.Frame):
  def __init__(self, master=None):
    Tkinter.Frame.__init__(self, master, width=200, height=100)
    self.master.title('VEM Configure')

# 期間
    term_panel = Tkinter.Frame(self, relief=Tkinter.GROOVE, bd=2)
    max_term = ParameterField(term_panel, '最大実効期間', 100, 10000, 'white')
    max_term.pack()
# ヒト
    human_panel = Tkinter.Frame(self, relief=Tkinter.GROOVE, bd=2)
    human_size = ParameterField(human_panel, '初期ヒト数', 1, 1000, 'white')
    hland_width = ParameterField(human_panel, 'ヒト土地ヨコ', 10, 1000, 'white')
    hland_height = ParameterField(human_panel, 'ヒト土地タテ', 10, 1000, 'white')
    human_size.pack()
    hland_width.pack()
    hland_height.pack()
# T細胞
    tcell_panel = Tkinter.Frame(self, relief=Tkinter.GROOVE, bd=2)
    tcell_minimum_size = ParameterField(tcell_panel, '最小T細胞数', 10, 1000, 'white')
    tcell_lifespan = ParameterField(tcell_panel, 'T細胞寿命', 10, 1000, 'white')
    tcell_minimum_size.pack()
    tcell_lifespan.pack()
# 細胞
    cell_panel = Tkinter.Frame(self, relief=Tkinter.GROOVE, bd=2)
    cland_width = ParameterField(cell_panel, '細胞土地タテ', 10, 1000, 'white')
    cland_height = ParameterField(cell_panel, '細胞土地タテ', 10, 1000, 'white')
    cland_width.pack()
    cland_height.pack()

    term_panel.pack( padx=5, pady=5 )
    human_panel.pack( padx=5, pady=5 )
    tcell_panel.pack( padx=5, pady=5 )
    cell_panel.pack( padx=5, pady=5 )

# Button
    button_panel = Tkinter.Frame(self)
    #execute_button = create_button(button_panel, FONT, '実行', self.execute, 0, 0)
    save_button = create_button(button_panel, FONT, '保存', self.saveConfig, 0, 0)
    exit_button = create_button(button_panel, FONT, '終了', self.exitConfig, 0, 0)
    put_widget(button_panel, 0, 0)
    put_widget(save_button, 0, 1)
    put_widget(exit_button, 0, 2)
    button_panel.pack()

  def execute(self):
    print 'Run'
    os.system('make run')
  def exitConfig(self):
    sys.exit()
  def saveConfig(self):
    print 'Save'

def main():
  c = Configure()
  c.pack()
  c.mainloop()

if __name__=='__main__':
  print 'Virus Evolutionary Model Configure'
  print 'version 1.0'
  main()
