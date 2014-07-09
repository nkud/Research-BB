#! /usr/bin/python
# coding=utf-8
import os

CONFIG_PATH = 'include/Config.h'

def sed( command, fname ):
  line = 'sed -i -e "%s" %s' % ( command, fname )
  os.system( line )

def configure(inc, sym):
  sed( '/V_NONINFECTIOUS_PERIOD/c const int V_NONINFECTIOUS_PERIOD = %d;' % inc, CONFIG_PATH )
  sed( '/V_INFECTIOUS_PERIOD/c const int V_INFECTIOUS_PERIOD = %d;' % sym, CONFIG_PATH )

def run(inc, sym):
  command = 'cd ~/workspace/AgentBasedEpidemicModel/ABEM;make build run gene pack mail R="IN%dSY%d"' \
      % ( int(inc), int(sym) )
  os.system( command );


def main():
  inc_range = 20
  sym_range = 20

  for inc in range(inc_range):
    for sym in range(sym_range):
      configure(inc, sym)
      run(inc, sym)

if __name__ == "__main__":
  main();
