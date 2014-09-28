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
    pfactory.setImage('Average', 'Term', 'Value', 'ave-newvirus', (pf.TXT('../bin/ave-newvirus-value'), 'average'))
    pfactory.setImage('Denity', 'Term', 'Rate', 'v-density', (pf.TXT('../bin/v-dense'), 'density'))
    pfactory.setImage('Denity', 'Term', 'Rate', 'v-density2', (pf.TXT('../bin/v-dense2'), 'density'))
    pfactory.setImage('TcellSize', 'Term', 'Size', 'tcell-size', (pf.TXT('../bin/tcell-size'), 'size'))
    pfactory.setImage('IsIncubation', 'Term', 'Count', 'is-infection', (pf.TXT('../bin/isInfection'), 'count'))
    pfactory.setImage('IsInfection', 'Term', 'Count', 'inf-human', (pf.TXT('../bin/inf-human'), 'count'))
    pfactory.setImage('VirusSize', 'Term', 'Size', 'virus-size', (pf.TXT('../bin/virus-size'), 'size'))
    pfactory.generate()

    # html
    # fhtml = open('index.html', 'w')

    hfactory = hf.HtmlFactory('index.html')
    hfactory.setConfig('../include/Config.hpp')
    hfactory.setCss('../asset/layout.css')
    hfactory.setSection('感染細胞数 / 全細胞数', 2, hf.IMG('density'))
    hfactory.setSection('全T細胞数', 2, hf.IMG('tcell-size'))
    hfactory.setSection('細胞０の細胞内密度', 2, hf.IMG('v-density'))
    hfactory.setSection('細胞１の細胞内密度', 2, hf.IMG('v-density2'))
    hfactory.setSection('感染ヒト数', 2, hf.IMG('inf-human'))
    hfactory.setSection('全ウイルス数', 2, hf.IMG('virus-size'))
    hfactory.setSection('感染しているかどうか', 2, hf.IMG('is-infection'))
    hfactory.setSection('平均評価値', 2, hf.IMG('ave-newvirus'))
    hfactory.generate()

if __name__ == '__main__':
    main()
