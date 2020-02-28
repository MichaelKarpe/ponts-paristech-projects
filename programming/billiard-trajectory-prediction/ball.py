#!/usr/bin/python
# -*- coding: utf-8 -*-

from billiard import Billiard
from utils import Point


class Ball(Billiard):
    def __init__(self, white_ball, coords_balls, index_ball, verbose=True):
        super().__init__(white_ball, coords_balls, verbose=verbose)
        self.index_ball = index_ball
        self.pt = self.coords_balls[index_ball]
        self.impact_positions = self.impact_positions()

    def impact_positions(self):
        coords_impact_positions = []

        for i in range(self.nb_holes):
            slope = (self.holes[i].y - self.pt.y) / (self.holes[i].x - self.pt.x)

            if self.holes[i].x - self.pt.x >= 0:
                coords_impact_positions.append(
                    Point(
                        self.pt.x - 2 * self.radius / (1 + slope ** 2) ** (1 / 2),
                        self.pt.y - slope * 2 * self.radius / (1 + slope ** 2) ** (1 / 2),
                    )
                )
            else:
                coords_impact_positions.append(
                    Point(
                        self.pt.x + 2 * self.radius / (1 + slope ** 2) ** (1 / 2),
                        self.pt.y + slope * 2 * self.radius / (1 + slope ** 2) ** (1 / 2),
                    )
                )

        return coords_impact_positions
