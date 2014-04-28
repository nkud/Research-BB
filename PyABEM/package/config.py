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

# Term, Landscape
TERM = 1000000
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

MUTATION_RATE = 10
MUTATION_VARIATE = 5

# Virus
V_NUM = 5
V_TAG_LEN = 10
V_LETHAL_TIME = 5

INFECTION_RATE = 100
INIT_INFECTION_RATE = 100
################################################################################
