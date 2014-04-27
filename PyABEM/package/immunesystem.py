#! /usr/bin/python
# coding=utf-8

from function import *
from config import *
from agent import *
from virus import *
from landscape import *

### ImmuneSystem
class ImmuneSystem( object ):
    """ 免疫機構システム """
    def __init__(self, tag):
        self.stand_by_virus = []
        self.virus_list = []

    def contact(self, agents):
        """ 接触する """
        _vlist = []
        for a in agents:
            for vl in a.immune.virus_list:
                _vlist.append( vl )
        if len( _vlist ) > 0:
            if probability(INFECTION_RATE):
                self.stand_by_virus.append(
                    (random.choice( _vlist )).virus
                    )

    def infection(self, tag, v=None):
        """ 感染する """
        if v is None:
            if len(self.stand_by_virus) > 0:
                v = random.choice( self.stand_by_virus ) # ランダムに選んで
                if not self.hasImmunity(tag, v) and not self.hasVirus(v):
                    cp = min_ham_distance(tag, v.tag)
                    if cp >=0:
                        self.virus_list.append( VirusList(v, cp) )
                        self.stand_by_virus = []
                        return True
            self.stand_by_virus = []
            return False
        else:
            if not self.hasImmunity(tag, v) and not self.hasVirus(v):
                cp = min_ham_distance(tag, v.tag)
                if cp >=0:
                    self.virus_list.append( VirusList(v, cp) )
                    self.stand_by_virus = []
                    return True
            self.stand_by_virus = []
            return False

    def response(self, tag):
        """ 免疫獲得する
            フリップする : return 1
            免疫獲得済み : return 0
        """
        if len(self.virus_list) > 0:
            cp = self.virus_list[0].cling_point # 先頭のウイルスの取りつく位置
            v = self.virus_list[0].virus
            if len(tag) < len(v.tag):
                return tag, V_LETHAL_TIME+1
            for i in range(v.length):
                if tag[cp+i] == v.tag[i]:
                    continue
                else: # タグが異なれば
                    ret = tag[:cp+i] + v.tag[i] + tag[cp+i+1:] # 1つタグを変更
                    self.virus_list[0].time += 1
                    return ret, self.virus_list[0].time # 変更後のタグを返す
            del self.virus_list[0] # フリップする必要がなければ免疫獲得
        return tag, None

    def hasImmunity(self, tag, v):
        if tag.find(v.tag) >= 0:
            return True
        else:
            return False

    def isInfected(self):
        """ has virus or not """
        if len(self.virus_list) > 0 :
            return True
        else:
            return False

    def hasVirus(self, v):
        for iv in self.virus_list :
            if iv.virus == v:
                return True
        return False

