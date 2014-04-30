#! /usr/bin/python
# coding=utf-8

################################################################################
### Constant Variables

# File, Directory
BIN = 'bin'
BINDIR = BIN + '/'

FNAME_TAGLEN = BINDIR + 'ave.txt'
FNAME_INFO = BINDIR + 'info.txt'
FNAME_HASVIRUS = BINDIR + 'output.txt'
FNAME_CONFIG = BINDIR + 'config.txt'
FNAME_POPULATION = BINDIR + 'population.txt'

# Term, Landscape
TERM = 10000
GENERATION_INTERVAL = 50
WIDTH = 20

# Agent
A_NUM = 100
A_TAG_LEN = 10
A_TAG_NUM = 1

A_MAX_AGE = 100

MOVE_DIST = 1

A_TAG_LEN_FROM = 40
A_TAG_LEN_TO = 80

A_TAG_MAX_LEN = 200
A_TAG_MIN_LEN = 1

BIRTH_INTERVAL = 10
CHILD_BEARING_AGE = 0
BIRTH_RATE = 0.5

# VARIATE_ALPHA = 3.92 # 0.05
VARIATE_ALPHA = 2.56 # 0.20

MUTATION_RATE = 0
MUTATION_VARIATE = 0

# Virus
V_NUM =5
V_TAG_LEN = 20
V_LETHAL_TIME = 10

INFECTION_RATE = 100
INIT_INFECTION_RATE = 10
################################################################################
