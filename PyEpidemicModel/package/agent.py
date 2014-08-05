#! /usr/bin/python
# coding=utf-8

from landscape import *
from tag import *
from virus import *
from config import *
from function import *
from immunesystem import *

def random_migrate():
    x = random.randint(0, WIDTH-1)
    y = random.randint(0, WIDTH-1)
    return x, y

def random_walk(x, y, dist):
    difx = random.randint(-dist, dist)
    dify = random.randint(-dist, dist)
    tox = x + difx
    toy = y + dify
    x %= WIDTH
    y %= WIDTH
    return x, y

### Agent
# 通常エージェント
class Agent( Tag ):
    def __init__(self, tl = A_TAG_LEN, tl2 = None):
        """ 初期化 """
        super(Agent, self).__init__(tl, tl2)
        self.x, self.y = random_migrate()

        self.immune = ImmuneSystem(self.tag)

        self.birth_time = 0
        self.is_birth = False
        self.age = 0

    def move(self, land):
        """ 移動して土地に登録する """
        # self.x, self.y = random_migrate()
        if self.immune.isOnset() == False:
            self.x, self.y = random_walk(self.x, self.y, MOVE_DIST)

        land.resist_agent_to_map(self, self.x, self.y)

    def contact(self, agent):
        """ 接触 """
        self.immune.contact(agent)

    def infection(self, v = None):
        """ 感染する
        Attributes:
            v: ウイルス指定
        """
        return self.immune.infection(self.tag, v)

    def response(self):
        """ 免疫応答 
        感染期間を返す
        """
        self.tag = self.immune.response(self.tag)

    def hasImmunity(self, v):
        """ 免疫獲得判定
        Attributes:
            v: ウイルス指定
        """
        return self.immune.hasImmunity(self.tag, v)

    def isInfected(self):
        return self.immune.isInfected()

    def hasVirus(self, v):
        return self.immune.hasVirus(v)

    def aging(self):
        self.age += 1
        return self.age

    def info(self):
        """ 個人情報を表示 """
        print "\t%s: %3d, %3d " % ( self.tag, self.x, self.y ),
        for vl in self.immune.virus_list:
            print vl.virus, vl.cling_point,
        print ''

### PolyAgent
# タグを複数持てるエージェント
class PolyAgent( MultiTag ):
    def __init__(self):
        super(PolyAgent, self).__init__(A_TAG_LEN, A_TAG_NUM)
        self.immunes = []
        self.num = A_TAG_NUM
        #for i in range(self.num):
        for t in self.tags:
            self.immunes.append(ImmuneSystem(t))
        self.x = random.randint(0, WIDTH-1)
        self.y = random.randint(0, WIDTH-1)

        self.stand_by_virus = []
        self.land = land

    def move(self, land):
        """ 移動して土地に登録する """
        self.x = random.randint(0, WIDTH-1)
        self.y = random.randint(0, WIDTH-1)
        self.x %= WIDTH
        self.y %= WIDTH
        land.resist_agent_to_map(self, self.x, self.y)

    def contact(self, agent):
        stv = []
        for im in agent.immunes:
            stv += im.virus_list

        if len(stv) > 0:
            if probability(INFECTION_RATE):
                self.stand_by_virus.append( random.choice(stv) )

    def infection(self):
        if len(self.stand_by_virus) > 0:
            for v in self.stand_by_virus:
                for im in self.immunes:
                    if im.infection(v) :
                        self.stand_by_virus = []
                        return True
        self.stand_by_virus = []
        return False

    def response(self):
        for im in self.immunes:
            return im.response()

    def hasImmunity(self, v):
        for im in self.immunes:
            if im.hasImmunity(v):
                return True
        return False

    def isInfected(self):
        for im in self.immunes:
            if im.isInfected():
                return True
        return False

    def hasVirus(self, v):
        for im in self.immunes:
            if im.hasVirus(v):
                return True
        return False

    def numHasVirus(self):
        n = 0
        for im in self.immunes:
            n += len(im.virus_list)
        return n

    def info(self):
        """ 個人情報を表示 """
        print "%d %d\n" % ( self.x, self. y )
