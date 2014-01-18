#! /usr/bin/python

from function import *

PNG_DIR = ''

def setImage(f, *imgname):
    outputLine(f, '<!-- IMAGE -->')
    outputLine(f, '<table class="graph">')
    for name in imgname:
        outputLine(f, '\t<tr><td><img src="'+PNG_DIR+name+'"/></td></tr>')
    outputLine(f, '<tr></table>')

### generate HTMl
def generateResultHTML(f, d):
    outputLine(f, '<html><link rel="stylesheet" href="result.css"><body><font color=gray><code>')
    outputLine(f, '<h1><font color=black># RESULT </font></h1>')

# Population
    if d['AGING_AGENT'] == 1:
        outputLine(f, '<h2 id=population>population</h2>')
        setImage(f, 'Population.png')
# HasVirus
    outputLine(f, '<h2 id=hasvirus>hasVirus</h2>')
    setImage(f, 'HasVirus.png', 'HasVirus_begin.png', 'HasVirus_end.png')
# HasImmunity
    outputLine(f, '<h2 id=hasvirus>hasImmunity</h2>')
    setImage(f, 'HasImmunity.png', 'HasImmunity_begin.png', 'HasImmunity_end.png')
# SIR
    outputLine(f, '<h2 id=hasvirus>SIR</h2>')
    setImage(f, 'SIR.png', 'SIR_begin.png', 'SIR_end.png')
# SIR
    outputLine(f, '<h2 id=hasvirus>SIR_0</h2>')
    setImage(f, 'SIR_0.png', 'SIR_0_begin.png', 'SIR_0_end.png')
# SIR
    outputLine(f, '<h2 id=hasvirus>SIR_1</h2>')
    setImage(f, 'SIR_1.png', 'SIR_1_begin.png', 'SIR_1_end.png')
# Contact
    outputLine(f, '<h2 id=hasvirus>SIR</h2>')
    setImage(f, 'Contact.png')
