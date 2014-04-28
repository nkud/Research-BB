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

# Term, Landscape
TERM = 100000
GENERATION_INTERVAL = 50
WIDTH = 20

# Agent
A_NUM = 100
A_TAG_LEN = 10
A_TAG_NUM = 1
MOVE_DIST = 1

A_TAG_LEN_FROM = 40
A_TAG_LEN_TO = 80

A_TAG_MAX_LEN = 200
A_TAG_MIN_LEN = 1

# VARIATE_ALPHA = 3.92 # 0.05
VARIATE_ALPHA = 2.56 # 0.20

MUTATION_RATE = 0.05
MUTATION_LEN = 40

# Virus
V_NUM = 3
V_TAG_LEN = 30
V_LETHAL_TIME = 20

INFECTION_RATE = 100
INIT_INFECTION_RATE = 100
################################################################################
