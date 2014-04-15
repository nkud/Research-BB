#! /usr/bin/python
# coding=utf-8

print 'This is an Agent Based Model using Binary Tags. '

### Tag
class Tag(object):
	gene = '11110000'

### Agent
class Agent(object):
	gene = Tag()

### Virus
class Virus(object):
	gene = Tag()

### Main
def main():
	"""
	Yields:
		Running BTABM
	"""
	agents = {}
	virus = Virus()
	virus.gene = "11"
	print virus.gene

if __name__ == "__main__":
	print 'start main()'
	main()