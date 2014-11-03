#! /usr/bin/python
# -*- encoding:utf-8 -*-

import Tkinter
import sys
import os
import webbrowser
import subprocess
import collections

## Configure
FONT = ('monospace', '12')
##

def output_define(fo, name, value, title='none', color='white'):
  """ 定義をファイルに出力する """
  fo.write('#define %-30s %-10d///< %s %s\n' % (name, value, title, color))

def output_line(fo, line):
  """ １行出力する """
  fo.write('%s\n' % line)

def create_spinbox(master, f, t):
  """ スピンボックスを作成する """
  spinbox = Tkinter.Spinbox(master, from_=f, to=t, width=10)
  return spinbox

def create_label(master, text, **options):
  """ ラベルを作成する """
  border = 1
  label = Tkinter.Label(master, text=text, relief=Tkinter.GROOVE, bd=border, width=20, **options)
  return label

def put_widget(widget, row, column, padx=5, pady=0):
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
  """ パラメータフィールド
  """
  def __init__(self, master, title, name, f, t, bg='white'):
    Tkinter.Frame.__init__(self, master)
    # 作成
    self.label = create_label(self, title, bg=bg)
    self.spinbox = create_spinbox(self, f, t)
    self.name = name
    self.title = title
    self.color_ = bg
    # 配置
    put_widget(self.label, 0, 0)
    put_widget(self.spinbox, 0, 1)
    self.pack()

  def getValue(self):
    """ スピンボックスの値を取得 """
    return int(self.spinbox.get())

  def getName(self):
    """ 変数名を取得 """
    return self.name

  def getTitle(self):
    """ 説明を取得 """
    return self.title

  def getColor(self):
    return self.color_

class Configure(Tkinter.Frame):
  """ コンフィグ画面
  """
  def __init__(self, master=None):
    Tkinter.Frame.__init__(self, master, width=500, height=500)
    self.master.title('VEM Configure')
    self.config_path_ = 'include/Config.hpp'
    # self.master.minsize(width=300, height=600)
    # self.master.maxsize(width=300, height=600)

# メニューバー
    menubar = Tkinter.Menu(self)
    menu_file = Tkinter.Menu(menubar)
    menu_file.add_command(label=u'保存する', command=self.saveConfig)
    menu_file.add_command(label=u'読込する', command=self.readConfig)
    menu_file.add_command(label=u'結果を表示する', command=self.showResult)
    menu_file.add_command(label=u'終了する', command=self.exitConfig)
    menubar.add_cascade(label=u'メニュー', menu=menu_file)
    try:
      self.master.config(menu=menubar)
    except AttributeError:
      self.master.Tkinter.call(master, 'config', '-menu', menubar)

    self.info_ = collections.OrderedDict()
    self.readConfig()

    self.parameter_ = collections.OrderedDict()
# 期間
    term_panel = Tkinter.Frame(self, relief=Tkinter.GROOVE, bd=0)
    self.setParameter(term_panel, '最大実行期間', 'TERM')
    self.setParameter(term_panel, 'ヒト実行間隔', 'HUMAN_INTERVAL')
    self.setParameter(term_panel, '免疫実行間隔', 'IMMUNE_INTERVAL')
# ヒト
    human_panel = Tkinter.Frame(self, relief=Tkinter.GROOVE, bd=0)
    self.setParameter(human_panel, '初期ヒト数', 'HUMAN_SIZE')
    self.setParameter(human_panel, 'ヒト土地ヨコ', 'HUMAN_LAND_WIDTH')
    self.setParameter(human_panel, 'ヒト土地タテ', 'HUMAN_LAND_HEIGHT')
    self.setParameter(human_panel, '発症閾値', 'H_SYMPTOMATIC_THRESHOLD')
# 細胞
    cell_panel = Tkinter.Frame(self, relief=Tkinter.GROOVE, bd=0)
    self.setParameter(cell_panel, '最大保持ウイルス数', 'CELL_MAX_VIRUS_CAN_HAVE', 'gray')
    self.setParameter(cell_panel, '細胞土地ヨコ', 'CELL_LAND_WIDTH', 'gray')
    self.setParameter(cell_panel, '細胞土地タテ', 'CELL_LAND_HEIGHT', 'gray')
    self.setParameter(cell_panel, '細胞の再生産期間', 'CELL_REPRODUCTIVE_SPAN', 'gray')

# T細胞
    tcell_panel = Tkinter.Frame(self, relief=Tkinter.GROOVE, bd=0)
    self.setParameter(tcell_panel, 'T細胞遺伝子長', 'TCELL_LEN', 'yellow')
    self.setParameter(tcell_panel, '最小T細胞数', 'TCELL_MINIMUM_SIZE', 'yellow')
    self.setParameter(tcell_panel, 'T細胞寿命', 'TCELL_LIFESPAN', 'yellow')
    self.setParameter(tcell_panel, '記憶率', 'TCELL_MEMORY_RATE', 'yellow')
    self.setParameter(tcell_panel, 'クローン数', 'TCELL_CLONE_SIZE', 'yellow')
# ウイルス
    virus_panel = Tkinter.Frame(self, relief=Tkinter.GROOVE, bd=0)
    self.setParameter(virus_panel, 'ウイルス遺伝子長', 'V_TAG', 'skyblue')
    self.setParameter(virus_panel, '増殖率', 'V_REPRODUCTIVE_RATE', 'skyblue')
    # self.setParameter(virus_panel, '感染率', 'V_INF_RATE', 'skyblue')
    self.setParameter(virus_panel, '突然変異率', 'V_MUTATION_RATE', 'skyblue')
    self.setParameter(virus_panel, '一段階増殖閾値', 'V_ONE_STEP_GROWTH_THRESHOLD', 'skyblue')
# パック
    term_panel.pack( padx=5, pady=5 )
    human_panel.pack( padx=5, pady=5 )
    cell_panel.pack( padx=5, pady=5 )
    tcell_panel.pack( padx=5, pady=5 )
    virus_panel.pack( padx=5, pady=5 )
# ボタン
    button_panel = Tkinter.Frame(self)
    execute_button = create_button(button_panel, FONT, '実行', self.execute, 0, 0)
    save_button = create_button(button_panel, FONT, u'保存', self.saveConfig, 0, 0)
    # read_button = create_button(button_panel, FONT, u'読込', self.readConfig, 0, 0)
    exit_button = create_button(button_panel, FONT, u'終了', self.exitConfig, 0, 0)
    result_button = create_button(button_panel, FONT, u'結果', self.showResult, 0, 0)
    update_button = create_button(button_panel, FONT, u'更新', self.updateResult, 0, 0)
    put_widget(execute_button, 0, 0)
    put_widget(save_button, 0, 1)
    # put_widget(read_button, 0, 2)
    put_widget(result_button, 0, 3)
    put_widget(update_button, 0, 4)
    put_widget(exit_button, 0, 5)
    button_panel.pack()

    self.pack()

  def saveConfig(self):
    """ コンフィグを保存する """
    print 'Save'
    fo = open(self.config_path_, 'w')
    output_line(fo, '// created by Configure.py')
    output_line(fo, '#ifndef ___CONFIG_HPP')
    output_line(fo, '#define ___CONFIG_HPP\n')
    for paramname in self.parameter_.keys():
        output_define(fo,
          paramname,
          self.parameter_[paramname].getValue(),
          self.parameter_[paramname].getTitle(),
          self.parameter_[paramname].getColor())
    output_line(fo, '\n#endif')
    self.displayConfig()

  def setParameter(self, master, title, name, color='white'):
    if name not in self.info_:
        self.info_[name] = 0
    self.parameter_[name] = ParameterField(master, title, name, self.info_[name], 1000000, color)

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
    self.displayConfig()

  def showResult(self):
    """ 結果を表示する """
    print 'Result'
    webbrowser.open('file://' + os.path.realpath('stat/index.html'))

  def updateResult(self):
    print 'Update'
    subprocess.call('make stat open &', shell=True)

  def execute(self):
    """ 実行する """
    print 'Run'
    subprocess.call('make all &', shell=True)

  def exitConfig(self):
    """ コンフィグを終了する """
    sys.exit()

  def displayConfig(self):
    for key in self.info_.keys():
      print '- %s = %s' % (key, self.info_[key])

  def setConfigFile(self, fpath):
    self.config_path_ = fpath;

def main():
  c = Configure()
  c.mainloop()

if __name__=='__main__':
  print 'Virus Evolutionary Model Configure'
  print 'version 1.0'
  main()
