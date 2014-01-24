#! /usr/bin/python
# coding=utf-8

from function import *

LINE_STYLE = 'w l lw 2'

def scriptForInitSetting(f):
    """ 初期化設定
    Args:
        file
    Yields:
        initial setting for plot.
    """
    outputLine(f, 'set style line 1 lw 2')
    outputLine(f, 'set terminal png size 1000,180')
    outputLine(f, 'set key below right')
    #outputLine(f, 'set key box lt 0 lw 1 ')
    outputLine(f, 'set key textcolor lt 0')
    outputLine(f, 'set xl textcolor lt 0')
    outputLine(f, 'set yl textcolor lt 0')

### generateHTML
def generatePngPlot(f, d):
    """ generate plot script for gnuplot
    """
    print '( generating Plot Script... )'
    v_num = int(d['V_NUM'])
    scriptForInitSetting(f)
    scriptForHasVirusPng(f, d)
    scriptForHasImmunityPng(f, d)
    scriptForSIR(f, d)
    for i in range(v_num):
        scriptForEachSIR(f, d, i)
    scriptForContact(f, d)
    if int(d['AGING_AGENT']) == 1:
        scriptForPopulation(f, d)

def initPng(f, title, xl, yl):
    outputLine(f, 'set title "%s";set xl "%s";set yl "%s";' % (title, xl, yl))
def outputPng(f, imgname):
    outputLine(f, 'set output "%s.png";' % imgname)

class OutputFactory(object):
    """ output factory

    Attributes:
        f: file object
        info: info dictionary
        fname: output file name
        title: png title
        xl: x axis title
        yl: y axis title
        imgname: png image file name
    """
    def __init__(self, f, info, fname, title, xl, yl, imgname):
        """ initial setting """
        self.f = f
        self.info = info
        self.fname = fname
        self.title = title
        self.xl = xl
        self.yl = yl
        self.imgname = imgname
        self.mini_term = int(info['MINI_SIZE_TERM'])
        self.last_term = int(info['LAST_TERM'])
        self.v_num = int(info['V_NUM'])

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
        outputLine(self.f,
            'set output "%s.png";plot "%s" using 1:%s %s title "%s";' %
            (self.imgname, self.fname, str(using), LINE_STYLE, title))
    def plot_begin(self, title, using=2):
        outputLine(self.f,
            'set output "%s_begin.png";plot [0:%s] "%s" using 1:%s %s title "%s";' %
            (self.imgname, str(self.mini_term), self.fname, str(using), LINE_STYLE, title))
    def plot_end(self, title, using=2):
        outputLine(self.f, 'set output "%s_end.png";plot [%s:%s] "%s" using 1:%s %s title "%s";'
                % (self.imgname, str(self.last_term-self.mini_term), str(self.last_term), self.fname, str(using), LINE_STYLE, title))
    def replot(self, title, using):
        outputLine(self.f, 'set output "%s.png";replot "%s" using 1:%s %s title "%s";'
                % (self.imgname, self.fname, str(using), LINE_STYLE, title))
    def replot_begin(self, title, using):
        outputLine(self.f, 'set output "%s_begin.png";replot "%s" using 1:%s %s title "%s";'
                % (self.imgname, self.fname, str(using), LINE_STYLE, title))
    def replot_end(self, title, using):
        outputLine(self.f, 'set output "%s_end.png";replot "%s" using 1:%s %s title "%s";'
                % (self.imgname, self.fname, str(using), LINE_STYLE, title))

def scriptForHasVirusPng(f, data):
    """ create script for img about 'hasVirus' """
    of = OutputFactory(f, data, "A_hasVirus.txt", "HasVirus", "Term", "Agent", "HasVirus")
    v_num = int(data['V_NUM'])

    of.init()
    of.plot("has_virus_0")
    for i in range(v_num-1):
        of.replot('has_virus_'+str(i+1), i+3)
    of.replot('has_virus_all', v_num+2)

    of.init_begin()
    of.plot_begin('has_virus_0')
    for i in range(v_num-1):
        of.replot_begin('has_virus_'+str(i+1), i+3)
    of.replot_begin('has_virus_all', v_num+2)

    of.init_end()
    of.plot_end('has_virus_0')
    for i in range(v_num-1):
        of.replot_end('has_virus_'+str(i+1), i+3)
    of.replot_end('has_virus_all', v_num+2)

def scriptForHasImmunityPng(f, data):
    """ create script for img about 'hasImmunity' """
    of = OutputFactory(f, data, "A_hasImmunity.txt", "HasImmunity", "Term", "Agent", "HasImmunity")
    v_num = int(data['V_NUM'])

    of.init()
    of.plot("has_immunity_0")
    for i in range(v_num-1):
        of.replot('has_immunity_'+str(i+1),i+3)
    of.replot('has_immunity_all', v_num+2)

    of.init_begin()
    of.plot_begin('has_immunity_0')
    for i in range(v_num-1):
        of.replot_begin('has_immunity_'+str(i+1), i+3)
    of.replot_begin('has_immunity_all', v_num+2)

    of.init_end()
    of.plot_end('has_immunity_0')
    for i in range(v_num-1):
        of.replot_end('has_immunity_'+str(i+1), i+3)
    of.replot_end('has_immunity_all', v_num+2)

def scriptForSIR(f,data):
    ofi = OutputFactory(f, data, "A_hasVirus.txt", "SIR", "Term", "Agent", "SIR")
    ofr = OutputFactory(f, data, "A_hasImmunity.txt", "SIR", "Term", "Agent", "SIR")
    v_num = int(data['V_NUM'])
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
    ofi = OutputFactory(f, data,
            "A_hasVirus.txt", "SIR_"+str(vn), "Term", "Agent", "SIR_"+str(vn))
    ofr = OutputFactory(f, data,
            "A_hasImmunity.txt", "SIR_"+str(vn), "Term", "Agent", "SIR_"+str(vn))
    v_num = int(data['V_NUM'])
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
    """ script for contact """
    v_num = int(data['V_NUM'])

    of = OutputFactory(f, data,
            "A_infectionContact.txt", "Contact", "Term", "Count", "Contact")
    of.init()
    of.plot('infection_contact_0', 3)
    for i in range(v_num-1):
        of.replot('infection_contact_'+str(i+1), i+4)
    of.replot('contact', 2)

    of = OutputFactory(f, data,
            "A_infectionContact.txt", "InfectionContact", "Term", "Count",
            "InfectionContact")
    of.init()
    of.plot('infection_contact_0', 3 )
    for i in range(v_num-1):
        of.replot('infection_contact_'+str(i+1), i+4)
    of.init_begin()
    of.plot_begin('infection_contact_0', 3 )
    for i in range(v_num-1):
        of.replot_begin('infection_contact_'+str(i+1), i+4)
    of.init_end()
    of.plot_end('infection_contact_0', 3 )
    for i in range(v_num-1):
        of.replot_end('infection_contact_'+str(i+1), i+4)

def scriptForPopulation(f, data):
    of = OutputFactory(f, data, "A_population.txt", "Population", "Term", "Agent", "Population")
    of.init()
    of.plot('population')
