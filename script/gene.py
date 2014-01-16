#! /usr/bin/python

from module import *

info_data = {}

for line in open('bin/assets/INFO.txt', 'r'):
    item = line[:-1].split(' ')
    info_data[item[0]] = float(item[1])

def main():
    f = open('auto.plt', 'w')
    scriptForInitSetting(f)
    scriptForHasVirusPng(f, info_data)
    scriptForHasImmunityPng(f, info_data)
    scriptForSIR(f, info_data)

if __name__ == "__main__":
    print '>>> INFO...'
    for i in info_data.items():
        print '\t', i
    main()
    print '>>> finished creating "auto.plt"'
