#! /usr/bin/python
# -*- coding: utf-8 -*-

import plotfactory as pf
import htmlfactory as hf

STAT_DIR_PATH = '../stat/'

def main():
    # plot
    fplot = open('../stat/auto.plt', 'w')
    pf.initialize_for_plot(fplot)
    pf.set_terminal(fplot)
    pf.output_img(fplot, 'Denity', 'Term', 'Rate', 'density', (pf.TXT('../bin/dense'), 'density'))
    pf.output_img(fplot, 'TcellSize', 'Term', 'Size', 'tcell-size', (pf.TXT('../bin/tcell-size'), 'size'))
    pf.output_img(fplot, 'IsIncubation', 'Term', 'Count', 'is-infection', (pf.TXT('../bin/isInfection'), 'count'))

    # html
    fhtml = open('../stat/index.html', 'w')
    hf.output_section(fhtml, 'density', 2, hf.IMG('density'))
    hf.output_section(fhtml, 'tcell-size', 2, hf.IMG('tcell-size'))
    hf.output_section(fhtml, 'is-infection', 2, hf.IMG('is-infection'))

if __name__ == '__main__':
    main()
