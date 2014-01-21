#! /usr/bin/python

import os
import csv

from package import *

info_dict = {}

# Read data file
for item in csv.reader( open('INFO.txt', 'r') ):
    info_dict[item[0]] = item[1]

def main():
    fplot = open('auto.plt', 'w')
    fhtml = open('index.html', 'w')
    generatePngPlot(fplot, info_dict)
    generateResultHTML(fhtml, info_dict)

if __name__ == "__main__":
    main()
