#! /usr/bin/python
# coding=utf-8

### CONFIGURE #################################################################
SEPARATOR = ','
CONFIG_FNAME = '../include/Config.h'
INFO_FNAME = 'INFO.txt'
###############################################################################

def read_config( config_fname=CONFIG_FNAME, info_fname=INFO_FNAME ):
  print 'read configure...'
  n = 0
  fi = open(config_fname, 'r')
  fo = open(info_fname, 'a')
  for l in fi:
    dataline = ''
    ll = l.split()
    lc = l.split(':')
    if '=' in ll:
      if(':' in l):
        dataline += '%s,%s,%s\n' % (ll[2], ll[4],lc[1])
      else:
        dataline += '%s,%s\n' % (ll[2], ll[4])
      fo.write(dataline)
      n += 1
    elif '#define' in ll:
      if len(ll) == 2:
        if(':' in l):
          dataline += '%s,%s,%s\n' % (ll[1], '1', lc[1])
        else:
          dataline += '%s,%s\n' % (ll[1], '1')
      else:
        if(':' in l):
          dataline += '%s,%s,%s\n' % (ll[1], ll[2], lc[1])
        else:
          dataline += '%s,%s\n' % (ll[1], ll[2])
      fo.write(dataline)
      n += 1
  print '( %d param in config )' % n

def main():
  read_config(CONFIG_FNAME)

if __name__ == '__main__':
  main()
