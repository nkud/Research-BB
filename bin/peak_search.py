#! /usr/bin/python
import sys

array = []
interval = 2

for line in open('A_hasImmunity.txt', 'r'):
    item = line[:-1].split(' ')
    array.append( [ int(item[0]), int(item[1]) ] )

def max_term( interval ):
    m = [ 0, 0 ]
    for t, v in interval:
        if m[1] < v:
            m = [ t, v ]
    return m

f = open('peak.txt', 'w')

cursor = [ 0, 0 ]
count = 1
log = []
for term, value in array:
    _temp = max_term( array[term-interval:term+interval] )
    if cursor[1] == _temp[1]:
        count += 1
    else:
        cursor = _temp
        count = 1
    if count >= interval*2:
        if(cursor[0]>9800):
            f.write(str(cursor[0])+' '+str(cursor[1])+'\n')
            log.append( cursor )
        count = 0

sum_ = 0
pre = 0
for t, v in log:
    if(pre == 0):
        pre=t
    else:
        sum_ += t - pre;
        pre = t

average = float(sum_)/(len(log)-1)

flog = open('peak_log.txt', 'w')
flog.write( str(average)+'\n' )

print average
