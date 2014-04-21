#! /usr/bin/python
# coding=utf-8

from agent import *
from config import *

### Landscape
class Landscape(object):
    agent_map = []
    def __init__(self):
        self.reset_agent_map()
    def reset_agent_map(self):
        """ エージェントのマップを初期化する """
        self.agent_map = []
        for h in range(WIDTH):
            t = []
            for w in range(WIDTH):
                t.append([])
            self.agent_map.append(t)
    def resist_agent_to_map(self, a, x, y):
        """ エージェントをマップに登録する """
        self.agent_map[x][y].append(a)
    def isOnMap(self, x, y):
        if x < 0: return False
        if y < 0: return False
        if x > WIDTH-1: return False
        if y > WIDTH-1: return False
        return True
