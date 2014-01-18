#! /usr/bin/python

from function import *

def setImage(f, *imgname):
    outputLine(f, '<!-- ###### IMAGE ###### -->')
    outputLine(f, '<table class="graph">')
    for name in imgname:
        outputLine(f, '\t<tr><td><img src="img/'+name+'"/></td></tr>')
    outputLine(f, '<tr></table>')

### generate HTMl
def generateResultHTML(f):
    outputLine(f, '<html><link rel="stylesheet" href="result.css"><body><font color=gray><code>')
    outputLine(f, '<h1><font color=black># RESULT </font></h1>')

# Population
    outputLine(f, '<h2 id=population>population</h2>')
    setImage(f, 'Population.png', 'Population_begin.png', 'Population_end.png')
# HasVirus
    outputLine(f, '<h2 id=hasvirus>hasVirus</h2>')
    setImage(f, 'HasVirus.png', 'HasVirus_begin.png', 'HasVirus_end.png')
# HasImmunity
    outputLine(f, '<h2 id=hasvirus>hasImmunity</h2>')
    setImage(f, 'HasImmunity.png', 'HasImmunity_begin.png', 'HasImmunity_end.png')
# SIR
    outputLine(f, '<h2 id=hasvirus>SIR</h2>')
    setImage(f, 'SIR.png', 'SIR_begin.png', 'SIR_end.png')
# Contact
    outputLine(f, '<h2 id=hasvirus>SIR</h2>')
    setImage(f, 'Contact.png', 'Contact_begin.png', 'Contact_end.png')
