#! /usr/bin/python
" Functions module "

from function import *

LINE_STYLE = 'w l lw 2'

### generateHTML
def generatePngPlot(f, d):
    " generate plot script for gnuplot "
    v_num = int(d['NUM_V'])
    scriptForInitSetting(f)
    scriptForHasVirusPng(f, d)
    scriptForHasImmunityPng(f, d)
    scriptForSIR(f, d)
    for i in range(v_num):
        scriptForEachSIR(f, d, i)
    scriptForContact(f, d)

def initPng(f, title, xl, yl):
    outputLine(f, '\nset title "'+title+'";set xl "'+xl+'";set yl "'+yl+'"')
def outputPng(f, imgname):
    outputLine(f, 'set output "'+imgname+'.png"')

class OutputFactory(object):
    " class for output factory "
    def __init__(self, f, info, fname, title, xl, yl, imgname):
        self.f = f
        self.info = info
        self.fname = fname
        self.title = title
        self.xl = xl
        self.yl = yl
        self.imgname = imgname
        self.mini_term = info['MINI_SIZE_TERM']
        self.last_term = info['LAST_TERM']
        self.v_num = info['NUM_V']

    def init(self):
        initPng(self.f, self.title, self.xl, self.yl)
    def init_begin(self):
        initPng(self.f, self.title+'_begin', self.xl, self.yl)
    def init_end(self):
        initPng(self.f, self.title+'_end', self.xl, self.yl)

    def output(self):
        outputPng(self.f, self.imgname)
    def output_begin(self):
        outputPng(self.f, self.imgname+'_begin')
    def output_end(self):
        outputPng(self.f, self.imgname+'_end')

    def plot(self, title, using=2):
        outputLine(self.f, 'set output "'+self.imgname+'.png";plot "'+self.fname+'" using 1:'+str(using)+' '+LINE_STYLE+' title "'+title+'"')
    def plot_begin(self, title, using=2):
        outputLine(self.f, 'set output "'+self.imgname+'_begin.png";plot [0:'+str(int(self.mini_term))+'] "'+self.fname+'" using 1:'+str(using)+' '+LINE_STYLE+' title "'+title+'"')
    def plot_end(self, title, using=2):
        outputLine(self.f, 'set output "'+self.imgname+'_end.png";plot ['+str(int(self.last_term-self.mini_term))+':'+str(int(self.last_term))+'] "'+self.fname+'" using 1:'+str(using)+' '+LINE_STYLE+' title "'+title+'"')

    def replot(self, title, using):
        outputLine(self.f, 'set output "'+self.imgname+'.png";replot "'+self.fname+'" using 1:'+str(using)+' '+LINE_STYLE+' title "'+title+'"')
    def replot_begin(self, title, using):
        outputLine(self.f, 'set output "'+self.imgname+'_begin.png";replot "'+self.fname+'" using 1:'+str(using)+' '+LINE_STYLE+' title "'+title+'"')
    def replot_end(self, title, using):
        outputLine(self.f, 'set output "'+self.imgname+'_end.png";replot "'+self.fname+'" using 1:'+str(using)+' '+LINE_STYLE+' title "'+title+'"')

def scriptForInitSetting(f):
    """ create script for initialization """
    outputLine(f, 'set style line 1 lw 2')
    outputLine(f, 'set terminal png size 800,200')
    outputLine(f, 'set key box below left')

def scriptForHasVirusPng(f, data):
    """ create script for img about 'hasVirus' """
    of = OutputFactory(f, data, "A_hasVirus.txt", "HasVirus", "Term", "Agent", "HasVirus")
    v_num = int(data['NUM_V'])

    of.init()
    of.plot("has_virus_0")
    for i in range(v_num-1):
        of.replot('has_virus_'+str(i+1), i+3)

    of.init_begin()
    of.plot_begin('has_virus_0')
    for i in range(v_num-1):
        of.replot_begin('has_virus_'+str(i+1), i+3)

    of.init_end()
    of.plot_end('has_virus_0')
    for i in range(v_num-1):
        of.replot_end('has_virus_'+str(i+1), i+3)

def scriptForHasImmunityPng(f, data):
    """ create script for img about 'hasImmunity' """
    of = OutputFactory(f, data, "A_hasImmunity.txt", "HasImmunity", "Term", "Agent", "HasImmunity")
    v_num = int(data['NUM_V'])
    of.init()
    of.plot("has_immunity_0")
    for i in range(v_num-1):
        of.replot('has_immunity_'+str(i+1),i+3)
    of.init_begin()
    of.plot_begin('has_immunity_0')
    for i in range(v_num-1):
        of.replot_begin('has_immunity_'+str(i+1), i+3)
    of.init_end()
    of.plot_end('has_immunity_0')
    for i in range(v_num-1):
        of.replot_end('has_immunity_'+str(i+1), i+3)

def scriptForSIR(f,data):
    ofi = OutputFactory(f, data, "A_hasVirus.txt", "SIR", "Term", "Agent", "SIR")
    ofr = OutputFactory(f, data, "A_hasImmunity.txt", "SIR", "Term", "Agent", "SIR")
    v_num = int(data['NUM_V'])
    ofi.init()
    ofi.plot('I', v_num+2)
    ofr.replot('R', v_num+2)
    ofi.init_begin()
    ofi.plot_begin('I', v_num+2)
    ofr.replot_begin('R', v_num+2)
    ofi.init_end()
    ofi.plot_end('I', v_num+2)
    ofr.replot_end('R', v_num+2)

def scriptForEachSIR(f,data, vn):
    ofi = OutputFactory(f, data, "A_hasVirus.txt", "SIR_"+str(vn), "Term", "Agent", "SIR_"+str(vn))
    ofr = OutputFactory(f, data, "A_hasImmunity.txt", "SIR_"+str(vn), "Term", "Agent", "SIR_"+str(vn))
    v_num = int(data['NUM_V'])
    ofi.init()
    ofi.plot('I', vn+2)
    ofr.replot('R', vn+2)
    ofi.init_begin()
    ofi.plot_begin('I', vn+2)
    ofr.replot_begin('R', vn+2)
    ofi.init_end()
    ofi.plot_end('I', vn+2)
    ofr.replot_end('R', vn+2)

def scriptForContact(f,data):
    of = OutputFactory(f, data, "A_infectionContact.txt", "Contact", "Term", "", "Contact")
    v_num = int(data['NUM_V'])
    of.init()
    of.plot('contact')
    for i in range(v_num):
        of.replot('infection_contact_'+str(i+1),i+3)

def scriptForPopulation(f, data):
    of = OutputFactory(f, data, "A_population.txt", "Population", "Term", "Agent", "Population")
    of.init()
    of.plot('population')
