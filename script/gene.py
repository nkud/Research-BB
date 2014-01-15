#! /usr/bin/python
import sys

info_data = {}

# Read Parameter Data
for line in open('bin/assets/INFO.txt', 'r'):
    item = line[:-1].split(' ')
    info_data[item[0]] = float(item[1])

def outputLine(fname, line):
    """ write line to file """
    fname.write(line+'\n')

# Scripts For Png
def scriptForInitSetting(f):
    """ create script for initialization """
    outputLine(f, 'set style line 1 lw 2')
    outputLine(f, 'set terminal png size 800,200')
    outputLine(f, 'set key box below left')

def initPng(title, xl, yl):
    outputLine(f, 'set title "'+title+'"')
    outputLine(f, 'set xl "'+xl+'"')
    outputLine(f, 'set yl "'+yl+'"')

class OutputFactory(object):
    def __init__(self, fname, title, xl, yl, imgname):
        self.fname = fname
        self.title = title
        self.xl = xl
        self.yl = yl
        self.imgname = imgname

    def init(self):
        outputLine(f, '\nset title "'+self.title+'";set xl "'+self.xl+'";set yl "'+self.yl+'"')
    def init_begin(self):
        outputLine(f, '\nset title "'+self.title+'_begin";set xl "'+self.xl+'";set yl "'+self.yl+'"')

    def output(self):
        outputLine(f, 'set output "'+self.imgname+'.png"')
    def output_mini(self):
        outputLine(f, 'set output "'+self.imgname+'_begin.png"')

    def plot(self, title):
        outputLine(f, 'set output "'+self.imgname+'.png";plot "'+self.fname+'" title "'+title+'"')
    def plot_begin(self, title, term):
        outputLine(f, 'set output "'+self.imgname+'_begin.png";plot [0:'+str(term)+'] "'+self.fname+'" title "'+title+'"')

    def replot(self, title, n):
        outputLine(f, 'set output "'+self.imgname+'.png";replot "'+self.fname+'" using 1:'+str(n)+' title "'+title+'"')
    def replot_begin(self, title, n):
        outputLine(f, 'set output "'+self.imgname+'_begin.png";replot "'+self.fname+'" using 1:'+str(n)+' title "'+title+'"')


def scriptForHasVirusPng(f, data):
    """ create script for img about 'hasVirus' """
    of = OutputFactory("A_hasVirus.txt", "HasVirus", "Term", "Agent", "HasVirus")
    of.init()
    of.plot("has_virus_0")
    for i in range(int(data['NUM_V'])-1):
        of.replot('has_virus_'+str(i+1),i+3)
    of.init_begin()
    of.plot_begin('has_virus_0', 200)
    for i in range(int(data['NUM_V'])-1):
        of.replot_begin('has_virus_'+str(i+1), i+3)

def scriptForHasImmunityPng(f, data):
    of = OutputFactory("A_hasImmunity.txt", "HasImmunity", "Term", "Agent", "HasImmunity")
    of.init()
    of.plot("has_immunity_0")
    for i in range(int(data['NUM_V'])-1):
        of.replot('has_immunity_'+str(i+1),i+3)
    of.init_begin()
    of.plot_begin('has_immunity_0', 200)
    for i in range(int(data['NUM_V'])-1):
        of.replot_begin('has_immunity_'+str(i+1), i+3)

def scriptForSIR(f,data):
    ofi = OutputFactory("A_hasVirus.txt", "SIR", "Term", "Agent", "SIR")
    ofr = OutputFactory("A_hasImmunity.txt", "SIR", "Term", "Agent", "SIR")
    ofi.init()
    ofi.plot('I')
    ofr.replot('R', int(data['NUM_V']+2))

f = open('auto.plt', 'w')

scriptForInitSetting(f)

scriptForHasVirusPng(f, info_data)
scriptForHasImmunityPng(f, info_data)
scriptForSIR(f, info_data)
