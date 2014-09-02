#! /usr/bin/python
# -*- encoding:utf-8 -*-

import Tkinter
import sys
import os
import webbrowser
import subprocess

## Configure
FONT = ('monospace', '12')
##

def output_define(fo, name, value):
  """ 定義をファイルに出力する """
  fo.write('#define %s %d\n' % (name, value))

def output_line(fo, line):
  """ １行出力する """
  fo.write('%s\n' % line)

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
  def __init__(self, master, title, name, f, t, bg='white'):
    Tkinter.Frame.__init__(self, master)
    self.label = create_label(self, title, bg=bg)
    self.spinbox = create_spinbox(self, f, t)
    self.name = name
    put_widget(self.label, 0, 0)
    put_widget(self.spinbox, 0, 1)

  def getValue(self):
    """ スピンボックスの値を取得 """
    return int(self.spinbox.get())
  def getName(self):
    return self.name

class Configure(Tkinter.Frame):
  def __init__(self, master=None):
    Tkinter.Frame.__init__(self, master, width=500, height=500)
    self.master.title('VEM Configure')
    # self.master.minsize(width=300, height=600)
    # self.master.maxsize(width=300, height=600)

    self.info_ = {}
    self.readConfig()

    self.parameter_ = {}
# 期間
    term_panel = Tkinter.Frame(self, relief=Tkinter.GROOVE, bd=2)
    self.setParameter(term_panel, '最大実行期間', 'TERM')
    self.setParameter(term_panel, 'ヒト実行間隔', 'HUMAN_INTERVAL')
    self.setParameter(term_panel, '免疫実行間隔', 'IMMUNE_INTERVAL')
# ヒト
    human_panel = Tkinter.Frame(self, relief=Tkinter.GROOVE, bd=2)
    self.setParameter(human_panel, '初期ヒト数', 'HUMAN_SIZE')
    self.setParameter(human_panel, 'ヒト土地ヨコ', 'HUMAN_LAND_WIDTH')
    self.setParameter(human_panel, 'ヒト土地タテ', 'HUMAN_LAND_HEIGHT')

# 細胞
    cell_panel = Tkinter.Frame(self, relief=Tkinter.GROOVE, bd=2)
    self.setParameter(cell_panel, '細胞土地ヨコ', 'CELL_LAND_WIDTH')
    self.setParameter(cell_panel, '細胞土地タテ', 'CELL_LAND_HEIGHT')
    self.setParameter(cell_panel, '最大保持ウイルス数', 'CELL_MAX_VIRUS_CAN_HAVE')

# T細胞
    tcell_panel = Tkinter.Frame(self, relief=Tkinter.GROOVE, bd=2)
    self.setParameter(tcell_panel, '最小T細胞数', 'TCELL_MINIMUM_SIZE', 'yellow')
    self.setParameter(tcell_panel, 'T細胞寿命', 'TCELL_LIFESPAN', 'yellow')
    self.setParameter(tcell_panel, 'T細胞遺伝子長', 'TCELL_LEN', 'yellow')

# ウイルス
    virus_panel = Tkinter.Frame(self, relief=Tkinter.GROOVE, bd=2)
    self.setParameter(virus_panel, 'ウイルス遺伝子長', 'V_TAG', 'skyblue')
    self.setParameter(virus_panel, '感染率', 'V_INF_RATE', 'skyblue')

# パック
    term_panel.pack( padx=5, pady=5 )
    human_panel.pack( padx=5, pady=5 )
    cell_panel.pack( padx=5, pady=5 )  
    tcell_panel.pack( padx=5, pady=5 )
    virus_panel.pack( padx=5, pady=5 )

# ボタン
    button_panel = Tkinter.Frame(self)
    # execute_button = create_button(button_panel, FONT, '実行', self.execute, 0, 0)
    save_button = create_button(button_panel, FONT, '保存', self.saveConfig, 0, 0)
    read_button = create_button(button_panel, FONT, '読込', self.readConfig, 0, 0)
    exit_button = create_button(button_panel, FONT, '終了', self.exitConfig, 0, 0)
    result_button = create_button(button_panel, FONT, '結果', self.showResult, 0, 0)
    # put_widget(execute_button, 0, 0)
    put_widget(save_button, 0, 1)
    put_widget(read_button, 0, 2)
    put_widget(result_button, 0, 3)
    put_widget(exit_button, 0, 4)
    button_panel.pack()

  def execute(self):
    print 'Run'
    # os.system('make')
    subprocess.call('ls', shell=True)

  def saveConfig(self):
    print 'Save'
    fo = open('include/Config.hpp', 'w')
    output_line(fo, '// created by Configure.py')
    output_line(fo, '#ifndef ___CONFIG_HPP')
    output_line(fo, '#define ___CONFIG_HPP\n')
    for paramname in self.parameter_.keys():
        output_define(fo, paramname, self.parameter_[paramname].getValue())
    output_line(fo, '\n#endif')

  def setParameter(self, master, title, name, color='white'):
    self.parameter_[name] = ParameterField(master, title, name, self.info_[name], 10000, color)
    self.parameter_[name].pack()

  def readConfig(self):
    """ コンフィグを読み込む """
    print 'Read'
    fi = open('include/Config.hpp', 'r')
    for line in fi:
      ll = line.split()
      if len(ll) < 3:
        continue
      if ll[0] != '#define':
        continue
      else:
        self.info_[ll[1]] = ll[2]
    for key in self.info_.keys():
      print '- %s = %s' % (key, self.info_[key])

  def showResult(self):
    print 'Result'
    webbrowser.open('file://' + os.path.realpath('stat/index.html'))

  def exitConfig(self):
    sys.exit()

def main():
  c = Configure()
  c.pack()
  c.mainloop()

if __name__=='__main__':
  print 'Virus Evolutionary Model Configure'
  print 'version 1.0'
  main()
