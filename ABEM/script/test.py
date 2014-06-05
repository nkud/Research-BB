f = open('Log.txt', 'r')

for line in f:
	if line[0] == '>':
		break

data = []
for line in f:
	if line[0] == '>': break
	data.append( line[0:15] )

info = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]

for d in data:
	for i in range(15):
		info[i] += int(d[i])

print info

fo = open('test.dat', 'w')

t = 0
for i in info:
	fo.write('%d %s\n' % (t, i))
	t+=1