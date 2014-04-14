#! /usr/bin/python
# coding=utf-8

from function import *

PNG_DIR = ''

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
            '<html><link rel="stylesheet" href="result.css">'
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
        setImage(f, 'Population.png')
# HasVirus
    outputLine(f, '<h2 id=hasvirus>hasVirus</h2>')
    setImage(f, 'HasVirus.png',
            'HasVirus_begin.png',
            'HasVirus_end.png')
# HasImmunity
    outputLine(f, '<h2 id=hasimmunity>hasImmunity</h2>')
    setImage(f,
            'HasImmunity.png',
            'HasImmunity_begin.png',
            'HasImmunity_end.png')
# SIR
    outputLine(f, '<h2 id=sir>SIR about all</h2>')
    setImage(f,
            'SIR.png',
            'SIR_begin.png',
            'SIR_end.png')
# EACH_SIR
    for i in range(int(d['V_NUM'])):
        outputLine(f, '<h2 id=eachsir>SIR about virus_'+str(i)+'</h2>')
        setImage(f, 'SIR_'+str(i)+'.png',
                'SIR_'+str(i)+'_begin.png',
                'SIR_'+str(i)+'_end.png')
# Contact
    outputLine(f, '<h2 id=contact>Contact</h2>')
    setImage(f,
            'Contact.png',
            'InfectionContact.png',
            'InfectionContact_begin.png',
            'InfectionContact_end.png')

    outputLine(f, '</code></body></html>' )