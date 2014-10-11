#! /usr/bin/python
# -*- coding: utf-8 -*-

import plotfactory as pf
import htmlfactory as hf

def main():
    # plot
    pfactory = pf.PlotFactory('auto.plt')
    
    pfactory.setFont = 'verdana,13'
    
    pfactory.setImage('Density', 'Term', 'Rate', 'density', (pf.TXT('../bin/dense'), 'density', 'w boxes'))
    pfactory.setImage('Average', 'Term', 'Value', 'ave-newvirus', (pf.TXT('../bin/ave-newvirus-value'), 'average', 'w boxes'))
    pfactory.setImage('Denity', 'Term', 'Rate', 'v-density', (pf.TXT('../bin/v-dense'), 'density', 'w boxes'))
    pfactory.setImage('Denity', 'Term', 'Rate', 'v-density2', (pf.TXT('../bin/v-dense2'), 'density', 'w boxes'))
    pfactory.setImage('TcellSize', 'Term', 'Size', 'tcell-size', (pf.TXT('../bin/tcell-size'), 'size', 'w boxes'))
    pfactory.setImage('IsIncubation', 'Term', 'Count', 'is-infection', (pf.TXT('../bin/isInfection'), 'count', 'w boxes'))
    pfactory.setImage('IsInfection', 'Term', 'Count', 'inf-human', (pf.TXT('../bin/inf-human'), 'count', 'w l'))
    pfactory.setImage('VirusSize', 'Term', 'Size', 'virus-size', (pf.TXT('../bin/virus-size'), 'size', 'w boxes'))
    
    pfactory.generate()

    # html
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
