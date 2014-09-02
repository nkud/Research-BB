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

    self.info_ = {}
    self.readConfig()

# 期間
    term_panel = Tkinter.Frame(self, relief=Tkinter.GROOVE, bd=2)
    self.max_term = ParameterField(term_panel, '最大実効期間', self.info_['TERM'], 10000, 'white')
    self.human_interval = ParameterField(term_panel, 'ヒト実行間隔', self.info_['HUMAN_INTERVAL'], 100, 'white')
    self.immune_interval = ParameterField(term_panel, '免疫実行間隔', self.info_['IMMUNE_INTERVAL'], 100, 'white')
    self.max_term.pack()
    self.human_interval.pack()
    self.immune_interval.pack()
# ヒト
    human_panel = Tkinter.Frame(self, relief=Tkinter.GROOVE, bd=2)
    self.human_size = ParameterField(human_panel, '初期ヒト数', self.info_['HUMAN_SIZE'], 1000, 'white')
    self.hland_width = ParameterField(human_panel, 'ヒト土地ヨコ', self.info_['HUMAN_LAND_WIDTH'], 1000, 'white')
    self.hland_height = ParameterField(human_panel, 'ヒト土地タテ', self.info_['HUMAN_LAND_HEIGHT'], 1000, 'white')
    self.human_size.pack()
    self.hland_width.pack()
    self.hland_height.pack()
# T細胞
    tcell_panel = Tkinter.Frame(self, relief=Tkinter.GROOVE, bd=2)
    self.tcell_minimum_size = ParameterField(tcell_panel, '最小T細胞数', self.info_['TCELL_MINIMUM_SIZE'], 1000, 'white')
    self.tcell_lifespan = ParameterField(tcell_panel, 'T細胞寿命', self.info_['TCELL_LIFESPAN'], 1000, 'white')
    self.tcell_minimum_size.pack()
    self.tcell_lifespan.pack()
# 細胞
    cell_panel = Tkinter.Frame(self, relief=Tkinter.GROOVE, bd=2)
    self.cland_width = ParameterField(cell_panel, '細胞土地タテ', self.info_['CELL_LAND_WIDTH'], 1000, 'white')
    self.cland_height = ParameterField(cell_panel, '細胞土地タテ', self.info_['CELL_LAND_HEIGHT'], 1000, 'white')
    self.cland_width.pack()
    self.cland_height.pack()

# ウイルス
    virus_panel = Tkinter.Frame(self, relief=Tkinter.GROOVE, bd=2)
    self.virus_len = ParameterField(virus_panel, 'ウイルス遺伝子長', self.info_['V_TAG'], 100, 'white')
    self.virus_irate = ParameterField(virus_panel, '感染率', self.info_['V_INF_RATE'], 100, 'white')
    self.virus_len.pack()
    self.virus_irate.pack()

# パック
    term_panel.pack( padx=5, pady=5 )
    human_panel.pack( padx=5, pady=5 )
    tcell_panel.pack( padx=5, pady=5 )
    cell_panel.pack( padx=5, pady=5 )
    virus_panel.pack( padx=5, pady=5 )

# Button
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
  def exitConfig(self):
    sys.exit()
  def saveConfig(self):
    print 'Save'
    fo = open('include/Config.hpp', 'w')
    output_line(fo, '// created by Configure.py')
    output_line(fo, '#ifndef ___CONFIG_HPP')
    output_line(fo, '#define ___CONFIG_HPP\n')
    output_define(fo, 'HUMAN_SIZE', self.human_size.getValue())
    output_define(fo, 'TERM', self.max_term.getValue())
    output_define(fo, 'HUMAN_INTERVAL', self.human_interval.getValue())
    output_define(fo, 'IMMUNE_INTERVAL', self.immune_interval.getValue())
    output_define(fo, 'HUMAN_LAND_WIDTH', self.hland_width.getValue())
    output_define(fo, 'HUMAN_LAND_HEIGHT', self.hland_height.getValue())
    output_define(fo, 'TCELL_MINIMUM_SIZE', self.tcell_minimum_size.getValue())
    output_define(fo, 'TCELL_LIFESPAN', self.tcell_lifespan.getValue())
    output_define(fo, 'CELL_LAND_WIDTH', self.cland_width.getValue())
    output_define(fo, 'CELL_LAND_HEIGHT', self.cland_height.getValue())
    output_define(fo, 'V_TAG', self.virus_len.getValue())
    output_define(fo, 'V_INF_RATE', self.virus_irate.getValue())
    output_line(fo, '\n#endif')

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

def main():
  c = Configure()
  c.pack()
  c.mainloop()

if __name__=='__main__':
  print 'Virus Evolutionary Model Configure'
  print 'version 1.0'
  main()
