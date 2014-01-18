#! /usr/bin/python

from plot_module import *
from html_module import *
from function import *

info_data = {}

# Read data file
for line in open('bin/assets/INFO.txt', 'r'):
    item = line[:-1].split(' ')
    info_data[item[0]] = float(item[1])

def main():
    fplot = open('auto.plt', 'w')
    fhtml = open('index.html', 'w')
    generatePngPlot(fplot, info_data)
    generateResultHTML(fhtml)

if __name__ == "__main__":
    print '>>> INFO...'
    for i in info_data.items():
        print '\t', i
    main()
    print '>>> finished creating "auto.plt"'
