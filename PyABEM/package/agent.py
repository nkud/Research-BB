#! /usr/bin/python
# coding=utf-8

from landscape import *
from tag import *
from virus import *
from config import *
from function import *
from immunesystem import *

import landscape

### Agent
class Agent( Tag ):
    def __init__(self, tl = A_TAG_LEN):
        super(Agent, self).__init__(tl)
        self.x = random.randint(0, WIDTH-1)
        self.y = random.randint(0, WIDTH-1)

        self.immune = ImmuneSystem(self.tag)

    def move(self, land):
        """ 移動して土地に登録する """
        #self.x += random.randint(-MOVE_DIST, MOVE_DIST)
        #self.y += random.randint(-MOVE_DIST, MOVE_DIST)
        self.x = random.randint(0, WIDTH-1)
        self.y = random.randint(0, WIDTH-1)
        self.x %= WIDTH
        self.y %= WIDTH
        land.resist_agent_to_map(self, self.x, self.y)

    def contact(self, agent):
        self.immune.contact(agent)

    def infection(self, v = None):
        return self.immune.infection(v)

    def response(self):
        return self.immune.response()

    def hasImmunity(self, v):
        return self.immune.hasImmunity(v)

    def isInfected(self):
        return self.immune.isInfected()

    def hasVirus(self, v):
        return self.immune.hasVirus(v)

    def info(self):
        """ 個人情報を表示 """
        print "\t%s %s: %3d, %3d " % ( self.tag, self.immune.tag,  self.x, self.y ),
        for vl in self.immune.virus_list:
            print vl.virus, vl.cling_point,
        print '\n'

### PolyAgent
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
        #self.x += random.randint(-MOVE_DIST, MOVE_DIST)
        #self.y += random.randint(-MOVE_DIST, MOVE_DIST)
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
        print "%d %d" % ( self.x, self. y )

# Agent Management
def agentContact(agents, viruses, land):
    for myself in agents:
        ax = myself.x
        ay = myself.y
        a_list = land.agent_map[ax][ay]
        for i in [-1, 1]:
            for j in [-1, 1]:
                if land.isOnMap(ax+i, ay+j):
                    a_list += land.agent_map[ax+i][ay+j]
        a_list.remove( myself )
        if( len(a_list) > 0 ):
            myself.contact( random.choice(a_list) )

def agentMove(agents, land):
    for a in agents:
        a.move(land)

def agentInfection(agents):
    n = 0
    for a in agents:
        if a.infection() == True:
            n += 1
    print '\tinfection', n

def agentResponse(agents):
    for a in agents:
        a.response()

def agentIsInfected(agents, v):
    n = 0
    for a in agents:
        if a.hasVirus(v):
            n += 1
    return n

def showAgentInformation(agents, n):
    """ エージェントの情報を表示する """
    print '[ Agents 0 ~ %d ]' % (n-1)
    for a in agents[:n]:
        a.info()
        #print '\t%d:\t( %d, %d ) %s %s' % (i, agents[i].x, agents[i].y, agents[i].immunes[0].tag, agents[i].immunes[0].virus_list)
