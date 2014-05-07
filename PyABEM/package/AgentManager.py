#! /usr/bin/python
# coding=utf-8
from landscape import *
from tag import *
from virus import *
from config import *
from function import *
from immunesystem import *

# Agent Management
def agentContact(agents, viruses, land):
    for myself in agents:
        myself.contact( neighbors(myself, land) )

def agentMove(agents, landscape):
    for a in agents:
        a.move( landscape )

def agent_aging(agents, landscape):
    """ 老化させる """
    n = len(agents)
    for i in range( n ):
        if agents[i].aging() > A_MAX_AGE:
            landscape.remove_agent_from_map(agents[i])
            agents[i] = None
    while None in agents:
        agents.remove(None)  

def agentInfection(agents):
    """ 感染させる """
    for a in agents:
        a.infection()

def neighbors(myself, landscape):
    """ 近隣のエージェントをリストとして返す """
    ax = myself.x
    ay = myself.y
    # _neighbors = list(landscape.myself_map[ax][ay])
    _neighbors = []
    for i in [-1, 0, 1]:
        for j in [-1, 0, 1]:
            if landscape.isOnMap(ax+i, ay+j):
                _neighbors += list(landscape.agent_map[ax+i][ay+j])
    _neighbors.remove(myself)
    random.shuffle(_neighbors)
    return _neighbors

def agentResponse(agents):
    """ 免疫応答させる """
    for a in agents:
        a.response()

def agentDie(agents, landscape):
    for i in range( len(agents) ):
        for vl in agents[i].immune.virus_list:              # any virus agent has
            if vl.time > V_LETHAL_TIME or len(agents[i].tag)<len(vl.virus.tag):# 致死期間感染すると
                landscape.remove_agent_from_map(agents[i])  # マップから削除して
                agents[i] = None                            # 空にする
                break                                       # next agent
        # if _t > V_LETHAL_TIME:
            # agents[i] = None
    while None in agents:
        agents.remove(None)                                 # エージェント配列を短縮する
    for a in agents:                                        # for all agents
        for vl in a.immune.virus_list:                      # for all vlist of an agent
            vl.time += 1                                    # infected time +1
    #        _dies.append( i )
    #for i in _dies:
    #    print i,
    #    del agents[i]

def agentImmuneDepression(agents):
    for i in range( len(agents) ):
        if agents[i].immune.isOnset() and probability(IMMUNE_DEPRESSION_RATE):
            agents[i].tag = agents[i].tag[:-1]

def list_of_bearing_age_agents(agents):
    _bearing_age_agents = []
    for a in agents:
        if a.age > CHILD_BEARING_AGE:
            _bearing_age_agents.append( a )

def is_able_to_birth(agent):
    """ 出産可能かどうか """
    if agent.birth_time < BIRTH_MAX_TIME:
        if agent.is_birth == False:
            if agent.age > CHILD_BEARING_AGE:
                return True
    return False


def agent_mating(agents, landscape):
    """ エージェント集団に出産させる """
    _new_child = []
    random.shuffle(agents)
    n = len(agents)
    for i in range(n):
        if agents[i].is_birth == False and agents[i].birth_time < BIRTH_MAX_TIME:
            p = neighbors(agents[i], landscape)
            np = len(p)
            for ip in range(np):
                if probability(BIRTH_RATE) and is_able_to_birth( p[ip] ):
                    _new_child.append( mating( agents[i], p[ip] ) )
                    # 出産済みにして、出産回数を増やす

                    agents[i].is_birth = True
                    agents[i].birth_time += 1
                    p[ip].is_birth = True
                    p[ip].birth_time += 1
                    break
    for i in range(n):
        agents[i].is_birth = False
    return _new_child

# 計測
def agentIsInfected(agents, v):
    """ ウイルス v に感染しているエージェント数を返す """
    n = 0
    for a in agents:
        if a.hasVirus(v):
            n += 1
    return n

def numHasVirus(agents):
    n = 0
    for a in agents:
        if len(a.immune.virus_list) > 0:
            n += 1
    return n

def numIsIncubate(agents):
    """ 潜伏期間のエージェント数を返す """
    n = 0
    for a in agents:
        if a.immune.isIncubate():
            n += 1
    return n

def numIsOnset(agents):
    """ 発症しているエージェント数を返す """
    n = 0
    for a in agents:
        if a.immune.isOnset():
            n += 1
    return n

def show_agent_information(agents, n):
    """ 0-n エージェントの情報を表示する """
    print '[ Agents 0 ~ %d ]' % (n-1)
    for a in agents[:n]:
        a.info()

def initial_infection(agents, viruses, rate = INIT_INFECTION_RATE):
    """ エージェントに初期感染させる """
    for a in agents:
        if probability(rate):
            a.infection(random.choice(viruses))

def mating(a, b):
    """ 交配させる
    @desctiption:
        タグ長は、aとbの間からランダムな長さになる
        a < b
    """
    # 突然変異
    # if probability(MUTATION_RATE):
    #     ret = type(a)( random.randint(A_TAG_MIN_LEN, A_TAG_MAX_LEN))
    #     return ret
    # 通常出産
    if len(a.tag) > len(b.tag):
        a, b = b, a
    # ret = type(a)(random.randint(len(a.tag), len(b.tag)))
    # diff_len = float( len(b.tag) - len(a.tag) )
    mu = float(len(b.tag) + len(a.tag)) / 2
    variate = float(len(b.tag) - len(a.tag)) / VARIATE_ALPHA
    if probability(MUTATION_RATE):
        variate += MUTATION_VARIATE
    # if variate == 0: variate = MIN_VARIATE
    length = round_off( random.gauss( mu, variate ))
    ret = type(a)( length )
    #ret = type(a)((len(a.tag)+len(b.tag))/2)
    return ret

def ave_tag_len(agents):
    """ タグ長の平均 """
    n = len(agents)
    if n == 0:
        return False
    lens = 0
    for a in agents:
        lens += len(a.tag)
    return float(lens)/n

def complement_agent(
    agents, num = A_NUM, lenf = A_TAG_LEN_FROM, lent = A_TAG_LEN_TO
    ):
    """ エージェントを補う """
    while( len(agents) < num ):
        agents.append( Agent(lenf, lent) )
