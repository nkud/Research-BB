#! /usr/bin/python
# coding=utf-8

from function import *

PNG_DIR = ''
CSS_FILE = '../template/result.css'

def setImage(f, *imgnames):
    outputLine(f, '<!-- IMAGE -->')
    outputLine(f, '<table class="graph">')
    for name in imgnames:
        outputLine(f, '    <tr><td><img src="%s"/></td></tr>' % (PNG_DIR+name))
    outputLine(f, '<tr></table>')

### generate HTMl
def generateResultHTML(fname, d):
    """ generate a HTML file
    Args:
        file name, data
    Yields:
        結果表示用のHTMLファイルを出力する。
    """
    print '( generating HTML... )'
    f = open(fname, 'w')
    outputLine(f,
            '<html><link rel="stylesheet" href="'+CSS_FILE+'">'
            '<body><font color=gray><code>')
    outputLine(f, '<h1><font color=black># RESULT </font></h1>')

    outputLine(f, '<div id=left>')
    outputLine(f, '<table>')
    for i,v in sorted(d.items()):
        outputLine(f, '<tr><td>'+i+'</td><td>'+v+'</td></tr>')
    outputLine(f, '</table>')
    outputLine(f, '</div>')

    outputLine(f, '<div id=right>')
    if int(d['AGING_AGENT']) == 1:
        outputLine(f, '<li><a href=#population>Population</a></li>')
    outputLine(f, '<li><a href=#hasvirus>hasVirus</a></li>')
    outputLine(f, '<li><a href=#hasimmunity>hasImmunity</a></li>')
    outputLine(f, '<li><a href=#sir>SIR</a></li>')
    outputLine(f, '<li><a href=#eachsir>each_SIR</a></li>')
    outputLine(f, '<li><a href=#contact>Contact</a></li>')
    outputLine(f, '</div>')


# Population
    if int(d['AGING_AGENT']) == 1:
        outputLine(f, '<h2 id=population>Population</h2>')
        setImage(f, 'Population.svg')
# VirusVariaty
    outputLine(f, '<h2 id=>VirusVariaty</h2>')
    setImage(f, 'VirusVariaty.svg')
# HasVirus
    outputLine(f, '<h2 id=hasvirus>hasVirus</h2>')
    setImage(f, 'HasVirus.svg',
            'HasVirus_begin.svg',
            'HasVirus_end.svg')
# HasImmunity
    outputLine(f, '<h2 id=hasimmunity>hasImmunity</h2>')
    setImage(f,
            'HasImmunity.svg',
            'HasImmunity_begin.svg',
            'HasImmunity_end.svg')
# SIR
    outputLine(f, '<h2 id=sir>SIR about all</h2>')
    setImage(f,
            'SIR.svg',
            'SIR_begin.svg',
            'SIR_end.svg')
# EACH_SIR
    for i in range(int(d['V_NUM'])):
        outputLine(f, '<h2 id=eachsir>SIR about virus_'+str(i)+'</h2>')
        setImage(f, 'SIR_'+str(i)+'.svg',
                'SIR_'+str(i)+'_begin.svg',
                'SIR_'+str(i)+'_end.svg')
# Contact
    outputLine(f, '<h2 id=contact>Contact</h2>')
    setImage(f,
            'Contact.svg',
            'InfectionContact.svg',
            'InfectionContact_begin.svg',
            'InfectionContact_end.svg')

    outputLine(f, '</code></body></html>' )
