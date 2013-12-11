import sys

array = []
ci = 2

for line in open('bin/txt/A_hasImmunity.txt', 'r'):
    item = line[:-1].split(' ')
    array.append( int(item[1]) )

def max_term( interval ):
    m = 0
    for i in interval:
        if m < i:
            m = i
    return m

cursor = [ 0, 0 ]
flag = 0
for i in range(10000):
    if i<4: continue
    temp = max_term( array[i-ci:i+ci] )
    if cursor[1] == temp:
        flag += 1
    else:
        cursor = [ i, temp ]
        flag = 0
    if flag > 3:
        print cursor
        cursor = [0,0]
        flag = 0

