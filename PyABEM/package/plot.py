#! /usr/bin/python
# coding=utf-8

import os

LINE_STYLE = 'set style line 1 lw 2'
PNG_SIZE = '1200, 400'

CSS_FILE = ''

# Functions
def initPng(f, title, xl, yl):
    outputLine(f, 'set title "%s";set xl "%s";set yl "%s";' % (title, xl, yl))
def outputPng(f, imgname):
    outputLine(f, 'set output "%s.png";' % imgname)
def outputTerminal(f):
        outputLine(f, 'set terminal png size '+PNG_SIZE)
def outputLine(f, line):
    """ write line to file """
    f.write(line+'\n')
def plot_script(f, text='notitle', title='notitle', using='1:2'):
    outputLine(f, 'plot "'+text+'" using '+using+' w l title "'+title+'"')
def scriptForInitSetting(f):
    """ 初期化設定
    Args:
        file
    Yields:
        initial setting for plot.
    """
    outputLine(f, 'set style line 1 lw 2')
    # outputLine(f, 'set terminal png size '+PNG_SIZE)
    outputLine(f, 'set key below right')
    #outputLine(f, 'set key box lt 0 lw 1 ')
    outputLine(f, 'set key textcolor lt 0')
    outputLine(f, 'set xl textcolor lt 0')
    outputLine(f, 'set yl textcolor lt 0')

def plot():
    os.system('cd bin;gnuplot auto.plt')

def setImage(f, *imgnames):
    outputLine(f, '<!-- IMAGE -->')
    outputLine(f, '<table class="graph">')
    for name in imgnames:
        outputLine(f, '    <tr><td><img src="%s"/></td></tr>' % (name))
    outputLine(f, '<tr></table>')

### PlotFacroty
class PlotFactory(object):
    def __init__(self, filename):
        self.file = open(filename, 'w')

    def generatePlotScript(self):
        scriptForInitSetting(self.file)
        initPng(self.file, 'AverageTagLen', 'Term', 'AveTagLen')
        plot_script(self.file, 'ave.txt', 'Len')
        outputPng(self.file, 'AverageTagLen')
        outputTerminal(self.file)
        outputLine(self.file, 'replot')
        outputLine(self.file, 'set output')

        initPng(self.file, 'Population', 'Term', 'Agent')
        plot_script(self.file, 'population.txt', 'Agent')
        outputPng(self.file, 'Population')
        outputTerminal(self.file)
        outputLine(self.file, 'replot')
        outputLine(self.file, 'set output')

    def info(self):
        print 'have started generating PLOT SCRIPT.'

class HtmlFactory(object):
    def __init__(self, filename):
        self.file = open(filename, 'w')

    def generate(self):
        outputLine(self.file,
                '<html><link rel="stylesheet" href="'+CSS_FILE+'">'
                '<body><font color=gray><code>')
        outputLine(self.file, '<h1><font color=black># RESULT </font></h1>')

        # AverageTagLen
        outputLine(self.file, '<h2>AverageTagLen</h2>')
        setImage(self.file, 'AverageTagLen.png')
        outputLine(self.file, '</code></body></html>')
