#! /usr/bin/python
# coding=utf-8

import Tkinter


def create_spinbox(master, values):
  """ スピンボックスを作成する """
  spinbox = Tkinter.Spinbox(master, values=values)
  return spinbox

def create_label(master, text):
  """ ラベルを作成する """
  border = 0
  label = Tkinter.Label(master, text=text, bg='white', relief=Tkinter.RIDGE, bd=border)
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

## コンフィグ画面
class Configure(Tkinter.Frame):
  """ コンフィグ画面
  """
  def __init__(self, master=None):
    font = ('verdana', '12')
    Tkinter.Frame.__init__(self, master)
    # self.master.title('Host-Pathogen Model Confiture')

    # landscape
    width_label, self.width_spin = create_field(self, '幅', range(100), 0)

    # virus
    rate_label, self.rate_spin = create_field(self, '感染率', range(100), 1)
    
    # Tcell
    age_label, self.age_spin = create_field(self, '寿命', range(100), 2)
    tlen_label, self.tlen_spin = create_field(self, 'Ｔ細胞の遺伝子長', range(100), 3)

    execute_button = create_button(self, font, '実行', self.execute, 4, 0)
    stop_button = create_button(self, font, '停止', self.stop, 4, 1)
    end_button = create_button(self, font, '終了', self.end, 4, 2)

  def end(self):
    print 'end'

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