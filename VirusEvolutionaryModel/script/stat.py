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
    pfactory.setImage('TcellSize', 'Term', 'Size', 'tcell-size', (pf.TXT('../bin/tcell-size'), 'size'))
    pfactory.setImage('IsIncubation', 'Term', 'Count', 'is-infection', (pf.TXT('../bin/isInfection'), 'count'))
    pfactory.setImage('IsInfection', 'Term', 'Count', 'inf-human', (pf.TXT('../bin/inf-human'), 'count'))
    pfactory.generate()

    # html
    fhtml = open('index.html', 'w')
    hf.output_section(fhtml, 'density', 2, hf.IMG('density'))
    hf.output_section(fhtml, 'tcell-size', 2, hf.IMG('tcell-size'))
    hf.output_section(fhtml, 'inf-human', 2, hf.IMG('inf-human'))
    hf.output_section(fhtml, 'is-infection', 2, hf.IMG('is-infection'))


if __name__ == '__main__':
    main()
