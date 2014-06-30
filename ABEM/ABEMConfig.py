import Tkinter as Tk

class Frame(Tk.Frame):
    """ Frame with three label """

    def __init__(self, master=None):
        Tk.Frame.__init__(self, master)
        self.master.title('ABEM Configure')

        # First Label
        term = Tk.Label(self, text='TERM',  bg='yellow', relief=Tk.RIDGE, bd=2)
        term.pack()
        term_sp = Tk.Spinbox(self, width=10, from_=0, to=1000000)
        term_sp.pack()

        # Second Label
        lb = Tk.Label(self, text='Oh My God!', bg='red', relief=Tk.RIDGE, bd=2)
        lb.pack()

        # Third Label
        lc = Tk.Label(self, text='See you tomorrow.', bg='LightSkyBlue', relief=Tk.RIDGE, bd=2)
        lc.pack()

        sp = Tk.Spinbox(self, width=10, from_=0, to=29)
        sp.pack()

if __name__ == '__main__':
    f = Frame()
    f.pack()
    f.mainloop()
