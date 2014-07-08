#! /usr/bin/python
# coding=utf-8
import os

CONFIG_PATH = 'include/Config.h'

incubation = int( raw_input("Incubation Period = ") )
symptomatic = int( raw_input("Symptomatic Period = ") )

command_incubation = 'cat "%s" | \
    sed -e "/INCUBATION_PERIOD/c const int V_INCUBATION_PERIOD = %d;" \
    > %s' \
    % ( CONFIG_PATH, incubation, CONFIG_PATH )
command_lethal = 'cat "%s" | \
    sed -e "/LETHAL_PERIOD/c const int V_LETHAL_PERIOD = %d;" \
    > %s' \
    % ( CONFIG_PATH, incubation+symptomatic, CONFIG_PATH )

os.system( command_incubation );
os.system( command_lethal );
