#! /usr/bin/python

import os

from package import *

info_data = {}

# Read data file
for line in open('INFO.txt', 'r'):
    item = line[:-1].split(' ')
    info_data[item[0]] = float(item[1])

def main():
    fplot = open('auto.plt', 'w')
    fhtml = open('index.html', 'w')
    generatePngPlot(fplot, info_data)
    generateResultHTML(fhtml, info_data)
    os.system('gnuplot auto.plt')

if __name__ == "__main__":
    main()
