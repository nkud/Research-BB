#! /usr/bin/python
# -*- coding: utf-8 -*-

import plotfactory as pf
import htmlfactory as hf

def main():
    # plot
    # fplot = open('auto.plt', 'w')
    # pf.initialize_for_plot(fplot)
    # pf.set_terminal(fplot)
    pfactory = pf.PlotFactory('auto.plt')
    pfactory.setFont = 'arial,16'
    pfactory.setImage('Denity', 'Term', 'Rate', 'density', (pf.TXT('../bin/dense'), 'density'))
    pfactory.setImage('Denity', 'Term', 'Rate', 'v-density', (pf.TXT('../bin/v-dense'), 'density'))
    pfactory.setImage('Denity', 'Term', 'Rate', 'v-density2', (pf.TXT('../bin/v-dense2'), 'density'))
    pfactory.setImage('TcellSize', 'Term', 'Size', 'tcell-size', (pf.TXT('../bin/tcell-size'), 'size'))
    pfactory.setImage('IsIncubation', 'Term', 'Count', 'is-infection', (pf.TXT('../bin/isInfection'), 'count'))
    pfactory.setImage('IsInfection', 'Term', 'Count', 'inf-human', (pf.TXT('../bin/inf-human'), 'count'))
    pfactory.generate()

    # html
    # fhtml = open('index.html', 'w')

    hfactory = hf.HtmlFactory('index.html')
    hfactory.setConfig('../include/Config.hpp')
    hfactory.setCss('../asset/layout.css')
    hfactory.setSection('density', 2, hf.IMG('density'))
    hfactory.setSection('tcell-size', 2, hf.IMG('tcell-size'))
    hfactory.setSection('v-density', 2, hf.IMG('v-density'))
    hfactory.setSection('v-density2', 2, hf.IMG('v-density2'))
    hfactory.setSection('inf-human', 2, hf.IMG('inf-human'))
    hfactory.setSection('is-infection', 2, hf.IMG('is-infection'))
    hfactory.generate()

if __name__ == '__main__':
    main()
