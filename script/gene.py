#! /usr/bin/python

import os

from package import *

info_data = {}

# Read data file
for line in open('INFO.txt', 'r'):
    item = line[:-1].split(' ')
    info_data[item[0]] = float(item[1])

def main():
    os.system('mkdir -vp img')
    fplot = open('auto.plt', 'w')
    fhtml = open('index.html', 'w')
    generatePngPlot(fplot, info_data)
    generateResultHTML(fhtml)

    os.system('gnuplot auto.plt')

if __name__ == "__main__":
    print '>>> INFO...'
    for i in info_data.items():
        print '\t', i
    main()
    print '>>> finished creating "auto.plt"'
