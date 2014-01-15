#! /usr/bin/python
import sys

info_data = {}

# Read Parameter Data
for line in open('bin/assets/INFO.txt', 'r'):
    item = line[:-1].split(' ')
    info_data[item[0]] = float(item[1])

for i in info_data:
    print i, info_data[i]

def outputLine(fname, line):
    """ write line to file """
    fname.write(line+'\n')

# Scripts For Png
def scriptForInitSetting(f):
    """ create script for initialization """
    outputLine(f, 'set style line 1 lw 2')
    outputLine(f, 'set terminal png size 800,200')
    outputLine(f, 'set key box below left')

def scriptForHasVirusPng(f, data):
    """ create script for img about 'hasVirus' """
    initPng("HasVirus", "Term", "Agent", "HasVirus.png")
    outputLine(f, 'plot "A_hasVirus.txt" title "has_virus_0"')
    for i in range(int(data['NUM_V'])-1):
        outputLine(f, 'set output "HasVirus.png";')
        outputLine(f, 'replot "A_hasVirus.txt" using 1:'+str(i+3)
                +' title "has_virus_'+str(i+1));
    initPng("HasVirus", "Term", "Agent", "HasVirus_mini.png")
    outputLine(f, 'plot [0:200] "A_hasVirus.txt" title "has_virus_0"')
    for i in range(int(data['NUM_V'])-1):
        outputLine(f, 'set output "HasVirus_mini.png";')
        outputLine(f, 'replot "A_hasVirus.txt" using 1:'+str(i+3)
                +' title "has_virus_'+str(i+1));

def initPng(title, xl, yl, img_name):
    outputLine(f, 'set title "'+title+'"')
    outputLine(f, 'set xl "'+xl+'"')
    outputLine(f, 'set yl "'+yl+'"')
    outputLine(f, 'set output "'+img_name+'"')

class PngFactory(object):
    def __init__(self, fn, t, x, y):
        self.fname = fn
        self.title = t
        self.xl = x
        self.yl = y
    def normal(self):
        initPng(self.title, self.xl, self.yl, self.title)
        outputLine(f, 'plot "'+self.fname+'"');
        for i in range(int(info_data['NUM_V'])-1):
            outputLine(f, 'set output "'+self.title+'.png"')
            outputLine(f, 'replot "'+self.fname+'" using 1:'+str(i+3))
    def begin(self):
        initPng(self.title, self.xl, self.yl, self.title)
        outputLine(f, 'plot [0:200]"'+self.fname+'"');
        for i in range(int(info_data['NUM_V'])-1):
            outputLine(f, 'set output "'+self.title+'_mini.png"')
            outputLine(f, 'replot "'+self.fname+'" using 1:'+str(i+3))
    def end(self):
        initPng(self.title, self.xl, self.yl, self.title)
        outputLine(f, 'plot "'+self.fname+'"');
        for i in range(int(info_data['NUM_V'])-1):
            outputLine(f, 'set output "'+self.title+'_last.png"')
            outputLine(f, 'replot "'+self.fname+'" using 1:'+str(i+3))

f = open('auto.plt', 'w')

scriptForInitSetting(f)

hasVirusPng = PngFactory('A_hasVirus.txt', 'HasVirus', 'Term', 'Agent')
hasImmunityPng = PngFactory('A_hasImmunity.txt', 'HasImmunity', 'Term', 'Agent')

hasVirusPng.normal()
hasVirusPng.begin()
hasVirusPng.end()
hasImmunityPng.normal()
hasImmunityPng.begin()
hasImmunityPng.end()
