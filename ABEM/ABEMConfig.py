#! /usr/bin/python
# coding=utf-8
import os

CONFIG_PATH = 'include/Config.h'

def configure(inc, sym):
  command_incubation = 'cat %s | \
      sed -e "/INCUBATION_PERIOD/c const int V_INCUBATION_PERIOD = %d;" \
      > %s' \
      % ( CONFIG_PATH, inc, CONFIG_PATH )
  command_lethal = 'cat %s | \
      sed -e "/LETHAL_PERIOD/c const int V_LETHAL_PERIOD = %d;" \
      > %s' \
      % ( CONFIG_PATH, inc+sym, CONFIG_PATH )

  os.system( command_incubation );
  os.system( command_lethal );

def run(inc, sym):
  command = 'make build run gene pack mail R="IN%dSY%d"' \
      % ( int(inc), int(sym) )
  os.system( command );


def main():
  inc_range = 1
  sym_range = 20

  for inc in range(inc_range):
    for sym in range(sym_range):
      configure(inc, sym)
      run(inc, sym)

if __name__ == "__main__":
  main();
