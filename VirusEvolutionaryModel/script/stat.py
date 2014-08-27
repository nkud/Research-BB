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

    # html
    fhtml = open('../stat/index.html', 'w')
    hf.output_section(fhtml, 'density', 2, hf.IMG('density'))

if __name__ == '__main__':
    main()
