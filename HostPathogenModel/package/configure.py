#! /usr/bin/python
# coding=utf-8

import Tkinter

def create_spinbox(master, f, t):
  """ スピンボックスを作成する """
  spinbox = Tkinter.Spinbox(master, from_=f, to=t, width=10)
  return spinbox

def create_label(master, text):
  """ ラベルを作成する """
  border = 0
  label = Tkinter.Label(master, text=text, bg='white', relief=Tkinter.RIDGE, bd=border, width=20)
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
  def __init__(self, master, text, f, t):
    font = ('helvetica', '12')
    Tkinter.Frame.__init__(self, master)
    self.label = create_label(self, text)
    self.spinbox = create_spinbox(self, f, t)
    put_widget(self.label, 0, 0)
    put_widget(self.spinbox, 0, 1)

  def getValue(self):
    """ スピンボックスの値を取得 """
    return int(self.spinbox.get())

## コンフィグ画面
class Configure(Tkinter.Frame):
  """ コンフィグ画面
  """
  def __init__(self, master=None):
    font = ('verdana', '12')
    Tkinter.Frame.__init__(self, master)
    # self.master.title('Host-Pathogen Model Confiture')

    # landscape
    self.width = ParameterField(self, '幅', 20, 100)
    put_widget(self.width, 0, 0)
    self.tlen = ParameterField(self, 'Ｔ細胞の遺伝子長', 12, 100) 
    put_widget(self.tlen, 1, 0)
    self.vlen = ParameterField(self, 'ウイルスの遺伝子長', 3, 100)
    put_widget(self.vlen, 2, 0)
    self.vrate = ParameterField(self, '感染率', 50, 100)
    put_widget(self.vrate, 3, 0)
    self.vmrate = ParameterField(self, '突然変異率', 30, 100)
    put_widget(self.vmrate, 4, 0)
    self.lifespan = ParameterField(self, '寿命', 5, 100)
    put_widget(self.lifespan, 5, 0)
    self.tcell_num = ParameterField(self, '初期Ｔ細胞数', 10, 100)
    put_widget(self.tcell_num, 6, 0)
    self.maxterm = ParameterField(self, '最大実行期間', 500, 100000)
    put_widget(self.maxterm, 7, 0)

    execute_button = create_button(self, font, '実行', self.execute, 8, 0)
    stop_button = create_button(self, font, '停止', self.stop, 8, 1)
    end_button = create_button(self, font, '終了', self.end, 8, 2)

  def end(self):
    print 'end'
    print self.p.getValue()

  def stop(self):
    print 'stop'

  def execute(self):
    """ 計算を実行する """
    print 'execute'
    self.master.animation()

## テスト
def test_configure():
  c = Configure()
  c.pack()
  c.mainloop()

if __name__ == '__main__':
  test_configure()
