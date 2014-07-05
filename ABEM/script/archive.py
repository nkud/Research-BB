#! /usr/bin/python
# coding=utf-8

import sys
import os

ARCHIVE = 'tar cfz'
MASTER_DIR = 'master/'

results = []
num = 1
flag = False

for dname in os.listdir(MASTER_DIR):
  if dname[:6]=='result':
    results.append( [dname, num, flag] )
    num += 1

print '========== archive system =========='
print '>>> please choose directories you want to archive.'
print '>>> [1~*]num, [a]ll, [q]uit'
for d in results:
  print '\t%3d: %s' % ( d[1], d[0] )

user_input = raw_input( '[input] ' )
user_input = user_input.split()
for i in user_input:
  results[int(i)-1][2] = True

for d in results:
  flag = ''
  if d[2]: flag = '*'
  print '\t%1s %3d: %s' % ( flag, d[1], d[0] )


archive_dir = ''
for dname in results:
  if dname[2]:
    archive_dir += '%s%s ' % ( MASTER_DIR, dname[0] )


print '>>> input archive name'
archive_name = raw_input( '[input] ' )

os.system('%s %s %s' % ( ARCHIVE, archive_name+'.tar.gz', archive_dir ) )
