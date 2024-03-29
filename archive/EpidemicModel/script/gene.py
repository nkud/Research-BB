#! /usr/bin/python
# coding=utf-8

import os
import csv

from package import *
from plot import *

info_dict = {}

def read_data(fname):
    _data = {}
    for item in csv.reader( open(fname, 'r') ):
        _data[item[0]] = item[1]
    return _data

# Read data file
for item in csv.reader( open('info.txt', 'r') ):
    info_dict[item[0]] = item[1]

def main():
    """
    Yields:
        Generate a script for plotting.
        Generate a html for gathering images and listing up information.
    """
    info_dict = read_data('INFO.txt')
    pf = PlotFactory('auto.plt')
    hf = HtmlFactory('index.html')
    pf.generate()
    hf.generate()

    last_term = int(info_dict['LAST_TERM'])
    interval = int(info_dict['DATABASE_INTERVAL'])
    generatePlotForVirusValueHistogram(last_term, interval);
    generatePlotForAgentValueHistogram(last_term, interval);

    generatePlotForVirusValueAnimation(last_term, interval);
    generatePlotForAgentValueAnimation(last_term, interval);

    pf.close()
    hf.close()

if __name__ == "__main__":
    main()
