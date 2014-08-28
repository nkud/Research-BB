#! /usr/bin/python
# encoding=utf-8

import Tkinter
import sys
import os

FONT = ('monospace', '8')

def create_spinbox(master, f, t):
  """ スピンボックスを作成する """
  spinbox = Tkinter.Spinbox(master, from_=f, to=t, width=10)
  return spinbox

def create_label(master, text, **options):
  """ ラベルを作成する """
  border = 2
  label = Tkinter.Label(master, text=text, relief=Tkinter.GROOVE, bd=border, width=20, **options)
  return label

def put_widget(widget, row, column, padx=5, pady=5):
  """ ウィジェットを配置する """
  widget.grid(row=row, column=column, padx=padx, pady=pady)

def create_field(master, text, values, pos):
  label = create_label(master, text)
  spinbox = create_spinbox(master, values)
  put_widget(label, pos, 0)
  put_widget(spinbox, pos, 1)
  return label, spinbox

def create_button(master, font, text, command, row, column, padx=5, pady=5):
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

    max_term = ParameterField(self, '最大実効期間', 100, 10000, 'white')
    human_num = ParameterField(self, '初期ヒト数', 1, 1000, 'yellow')
    hland_width = ParameterField(self, 'ヒト土地ヨコ', 10, 1000, 'yellow')
    hland_height = ParameterField(self, 'ヒト土地タテ', 10, 1000, 'yellow')

    max_term.pack()
    human_num.pack()
    hland_width.pack()
    hland_height.pack()

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
