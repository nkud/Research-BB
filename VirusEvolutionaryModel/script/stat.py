#! /usr/bin/python
# -*- coding: utf-8 -*-

import plotfactory as pf
import htmlfactory as hf

def main():
    # plot
    fplot = open('auto.plt', 'w')
    pf.initialize_for_plot(fplot)
    pf.set_terminal(fplot)
    pf.output_img(fplot, 'Denity', 'Term', 'Rate', 'density', (pf.TXT('../bin/dense'), 'density'))
    pf.output_img(fplot, 'TcellSize', 'Term', 'Size', 'tcell-size', (pf.TXT('../bin/tcell-size'), 'size'))
    pf.output_img(fplot, 'IsIncubation', 'Term', 'Count', 'is-infection', (pf.TXT('../bin/isInfection'), 'count'))
    pf.output_img(fplot, 'IsInfection', 'Term', 'Count', 'inf-human', (pf.TXT('../bin/inf-human'), 'count'))

    # html
    fhtml = open('index.html', 'w')
    hf.output_section(fhtml, 'density', 2, hf.IMG('density'))
    hf.output_section(fhtml, 'tcell-size', 2, hf.IMG('tcell-size'))
    hf.output_section(fhtml, 'inf-human', 2, hf.IMG('inf-human'))
    hf.output_section(fhtml, 'is-infection', 2, hf.IMG('is-infection'))


if __name__ == '__main__':
    main()
