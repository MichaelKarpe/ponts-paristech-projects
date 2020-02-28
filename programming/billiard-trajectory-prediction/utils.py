#!/usr/bin/python
# -*- coding: utf-8 -*-


class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y


def dist(pt1, pt2):
    return ((pt2.x - pt1.x) ** 2 + (pt2.y - pt1.y) ** 2) ** (1 / 2)
