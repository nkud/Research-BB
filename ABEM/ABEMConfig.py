import Tkinter as Tk

class Frame(Tk.Frame):
    """ Frame with three label """

    def __init__(self, master=None):
        Tk.Frame.__init__(self, master)
        self.master.title('Pack Three Labels')

        # First Label
        la = Tk.Label(self, text='Hello everybody. How are you?',  bg='yellow', relief=Tk.RIDGE, bd=2)
        la.pack()

        # Second Label
        lb = Tk.Label(self, text='Oh My God!', bg='red', relief=Tk.RIDGE, bd=2)
        lb.pack()

        # Third Label
        lc = Tk.Label(self, text='See you tomorrow.', bg='LightSkyBlue', relief=Tk.RIDGE, bd=2)
        lc.pack()

        sp = Tk.Spinbox(self, width=10, from_=0, to=29)
        sp.pack()

##----------------
if __name__ == '__main__':
    f = Frame()
    f.pack()
    f.mainloop()