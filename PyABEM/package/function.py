#! /usr/bin/python
# coding=utf-8

import random

def probability(p):
    if random.randint(0, 100) < p:
        return True
    else:
        return False

def rand_binary():
    return random.randint(0, 1)

def ham_distance(a, b):
    """ count hamming distance """
    diff = 0
    for i in range(len(a)):
        if a[i] != b[i]:
            diff += 1
        else: pass
    return diff

def min_ham_distance(a, b):
    """ return cling point """
    if len(a)<len(b):
        t = a; a = b; b = t;

    l = len(b)
    mi = [l+1, -1]

    for i in range(len(a)-len(b)+1):
        m = ham_distance(a[i:i+l], b)
        if mi[0] > m:
            if m == 0: return -1
            mi[0] = m
            mi[1] = i
    return mi[1]

def flip_once(a, b):
    for i in range(len(b)):
        if a[i] == b[i]:
            continue
        else:
            print a[:i]+b[i]+a[i+1:]
            a = a[:i]+b[i]+a[i+1:]
            print a
            return 1
    return 0
