#! /usr/bin/python
" Functions module "

def outputLine(fname, line):
    """ write line to file """
    fname.write(line+'\n')

class OutputFactory(object):
    " class for output factory "
    def __init__(self, f, fname, title, xl, yl, imgname, info):
        self.fname = fname
        self.title = title
        self.xl = xl
        self.yl = yl
        self.imgname = imgname
        self.f = f
        self.info = info
        self.mini_term = info['MINI_SIZE_TERM']
        self.last_term = info['LAST_TERM']

    def init(self):
        outputLine(self.f, '\nset title "'+self.title+'";set xl "'+self.xl+'";set yl "'+self.yl+'"')
    def init_begin(self):
        outputLine(self.f, '\nset title "'+self.title+'_begin";set xl "'+self.xl+'";set yl "'+self.yl+'"')
    def init_end(self):
        outputLine(self.f, '\nset title "'+self.title+'_end";set xl "'+self.xl+'";set yl "'+self.yl+'"')

    def output(self):
        outputLine(self.f, 'set output "'+self.imgname+'.png"')
    def output_begin(self):
        outputLine(self.f, 'set output "'+self.imgname+'_begin.png"')
    def output_end(self):
        outputLine(self.f, 'set output "'+self.imgname+'_end.png"')

    def plot(self, title):
        outputLine(self.f, 'set output "'+self.imgname+'.png";plot "'+self.fname+'" title "'+title+'"')
    def plot_begin(self, title):
        outputLine(self.f, 'set output "'+self.imgname+'_begin.png";plot [0:'+str(int(self.mini_term))+'] "'+self.fname+'" title "'+title+'"')
    def plot_end(self, title):
        outputLine(self.f, 'set output "'+self.imgname+'_end.png";plot ['+str(int(self.last_term-self.mini_term))+':'+str(int(self.last_term))+'] "'+self.fname+'" title "'+title+'"')

    def replot(self, title, using):
        outputLine(self.f, 'set output "'+self.imgname+'.png";replot "'+self.fname+'" using 1:'+str(using)+' title "'+title+'"')
    def replot_begin(self, title, using):
        outputLine(self.f, 'set output "'+self.imgname+'_begin.png";replot "'+self.fname+'" using 1:'+str(using)+' title "'+title+'"')
    def replot_end(self, title, using):
        outputLine(self.f, 'set output "'+self.imgname+'_end.png";replot "'+self.fname+'" using 1:'+str(using)+' title "'+title+'"')

def initPng(title, xl, yl):
    outputLine(f, 'set title "'+title+'"')
    outputLine(f, 'set xl "'+xl+'"')
    outputLine(f, 'set yl "'+yl+'"')

def scriptForInitSetting(f):
    """ create script for initialization """
    outputLine(f, 'set style line 1 lw 2')
    outputLine(f, 'set terminal png size 800,200')
    outputLine(f, 'set key box below left')


def scriptForHasVirusPng(f, data):
    """ create script for img about 'hasVirus' """
    of = OutputFactory(f, "A_hasVirus.txt", "HasVirus", "Term", "Agent", "HasVirus", data)
    of.init()
    of.plot("has_virus_0")
    for i in range(int(data['NUM_V'])-1):
        of.replot('has_virus_'+str(i+1),i+3)
    of.init_begin()
    of.plot_begin('has_virus_0')
    for i in range(int(data['NUM_V'])-1):
        of.replot_begin('has_virus_'+str(i+1), i+3)
    of.init_end()
    of.plot_end('has_virus_0')
    for i in range(int(data['NUM_V'])-1):
        of.replot_end('has_virus_'+str(i+1), i+3)

def scriptForHasImmunityPng(f, data):
    """ create script for img about 'hasImmunity' """
    of = OutputFactory(f, "A_hasImmunity.txt", "HasImmunity", "Term", "Agent", "HasImmunity", data)
    of.init()
    of.plot("has_immunity_0")
    for i in range(int(data['NUM_V'])-1):
        of.replot('has_immunity_'+str(i+1),i+3)
    of.init_begin()
    of.plot_begin('has_immunity_0')
    for i in range(int(data['NUM_V'])-1):
        of.replot_begin('has_immunity_'+str(i+1), i+3)
    of.init_end()
    of.plot_end('has_immunity_0')
    for i in range(int(data['NUM_V'])-1):
        of.replot_end('has_immunity_'+str(i+1), i+3)

def scriptForSIR(f,data):
    ofi = OutputFactory(f, "A_hasVirus.txt", "SIR", "Term", "Agent", "SIR", data)
    ofr = OutputFactory(f, "A_hasImmunity.txt", "SIR", "Term", "Agent", "SIR", data)
    ofi.init()
    ofi.plot('I')
    ofr.replot('R', int(data['NUM_V']+2))
