#! /usr/bin/python
# coding=utf-8

################################################################################
### Constant Variables

# File, Directory
BIN = 'bin'
BINDIR = BIN + '/'

FNAME_TAGLEN = BINDIR + 'ave.txt'
FNAME_INFO = BINDIR + 'info.txt'
FNAME_HASVIRUS = BINDIR + 'has_virus.txt'
FNAME_CONFIG = BINDIR + 'config.txt'
FNAME_POPULATION = BINDIR + 'population.txt'
FNAME_IS_INCUBATE = BINDIR + 'is_incubate.txt'
FNAME_IS_ONSET = BINDIR + 'is_onset.txt'

# Term, Landscape
TERM = 1000
GENERATION_INTERVAL = 1
WIDTH = 30

# Agent
A_NUM = 200
A_TAG_LEN = 10
A_TAG_NUM = 1

A_MAX_AGE = 100

MOVE_DIST = 1

A_TAG_LEN_FROM = 40
A_TAG_LEN_TO = 80

A_TAG_MAX_LEN = 200
A_TAG_MIN_LEN = 1

BIRTH_INTERVAL = 30

BIRTH_MAX_TIME = 3
CHILD_BEARING_AGE = 20
BIRTH_RATE =5

# VARIATE_ALPHA = 3.92 # 0.05
VARIATE_ALPHA = 2.56 # 0.20

MUTATION_RATE = 5
MUTATION_VARIATE = 20

# Virus
V_NUM = 2
V_TAG_LEN = 30
V_LETHAL_TIME = 10

V_INCUBATE_PERIOD = 8
V_ONSET_PERIOD = 11

IMMUNE_DEPRESSION_RATE = 50

INFECTION_RATE = 100
INIT_INFECTION_RATE = 0.5
################################################################################
