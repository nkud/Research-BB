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
for item in csv.reader( open('INFO.txt', 'r') ):
    info_dict[item[0]] = item[1]

def main():
    """
    Yields:
        Generate a script for plotting.
        Generate a html for gathering images and listing up information.
    """
    # info_dict = {}
    info_dict = read_data('INFO.txt')
    # generatePngPlot('auto.plt', info_dict)
    # generateResultHTML('index.html', info_dict)
    pf = PlotFactory('auto.plt')
    hf = HtmlFactory('index.html')
    pf.generate()
    hf.generate()
    pf.close()
    hf.close()

if __name__ == "__main__":
    main()