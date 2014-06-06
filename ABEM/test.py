def out(n):
	fi = open('%d_VirusDataBase.txt' % n, 'r')
	fo = open('%d_statics.txt' % n, 'w')

	data = [[0 for i in range(10)] for j in range(12)]

	for line in fi:
		line = line.split(' ')
		for i in range(12):
			data[i][int(line[0][i])] += int(line[1])

	for i in range(12):
		for j in range(10):
			fo.write('%d %d %d\n' % (i+1, j, data[i][j]))

for i in range(20):
	out((i+1)*100)