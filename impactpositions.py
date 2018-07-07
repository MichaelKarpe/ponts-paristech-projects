#!/usr/bin/python
# -*- coding: utf-8 -*-

from ball import Ball
import matplotlib.pyplot as plt
from utils import dist, Point


class Impactposition(Ball):
    def __init__(self, white_ball, coords_balls, index_ball, index_pos, verbose=True):
        super().__init__(white_ball, coords_balls, index_ball, verbose=verbose)
        self.index_pos = index_pos
        self.impact_pos = self.impact_positions[index_pos]
        self.achievable_impact_pos = self.check_impact_position()
        self.slope = (self.white_ball.y - self.pt.y) / (self.white_ball.x - self.pt.x)

        if verbose:
            self.draw_impact_pos()

    def check_impact_position(self):
        for ball_coords in self.coords_balls[:self.index_ball] + self.coords_balls[self.index_ball+1:]:
            if dist(ball_coords, self.impact_pos) < 2 * self.radius:
                return False
        return True

    def line_trajectory(self, pt_color, verbose=False):
        if self.slope >= 0:

            if pt_color.x - self.white_ball.x >= 0:
                y = pt_color.y + self.slope * (self.length - self.radius - pt_color.x)

                if y <= self.width - self.radius:
                    (x, y) = (self.length - self.radius, y)
                else:
                    (x, y) = (pt_color.x + (self.width - self.radius - pt_color.y) / self.slope,
                              self.width - self.radius)

            else:
                y = pt_color.y - self.slope * (pt_color.x - self.radius)

                if y >= self.radius:
                    (x, y) = (self.radius, y)
                else:
                    (x, y) = (pt_color.x - (pt_color.y - self.radius) / self.slope, self.radius)

        else:
            if pt_color.x - self.white_ball.x >= 0:
                x = pt_color.x - (pt_color.y - self.radius) / self.slope

                if x <= self.length - self.radius:
                    (x, y) = (x, self.radius)
                else:
                    (x, y) = (self.length - self.radius,
                              pt_color.y + self.slope * (self.length - self.radius - pt_color.x))

            else:
                x = pt_color.x + (self.width - self.radius - pt_color.y) / self.slope

                if x >= self.radius:
                    (x, y) = (x, self.width - self.radius)
                else:
                    (x, y) = (self.radius, pt_color.y - self.slope * (pt_color.x - self.radius))

        if verbose:
            plt.plot([self.white_ball.x, x], [self.white_ball.y, y], 'black')

        return Point(x, y)

    def rebound_trajectory(self, pt_color, nb_rebounds, verbose=False):

        rebound_pt = self.line_trajectory(pt_color, verbose)
        rebound_x, rebound_y = rebound_pt.x, rebound_pt.y
        rebound_slope = self.slope

        for rebound in range(nb_rebounds):
            if rebound_x == self.radius:

                if rebound_slope >= 0:
                    (x, y) = (self.length - self.radius, rebound_y - (self.length - 2 * self.radius) * rebound_slope)
                    if y < self.radius:
                        (x, y) = (self.radius + (rebound_y - self.radius) / rebound_slope, self.radius)

                else:
                    (x, y) = (self.length - self.radius, rebound_y - (self.length - 2 * self.radius) * rebound_slope)
                    if y > self.width - self.radius:
                        (x, y) = (self.radius - (self.width - self.radius - rebound_y) / rebound_slope,
                                  self.width - self.radius)

            elif rebound_x == self.length - self.radius:

                if rebound_slope >= 0:
                    (x, y) = (self.radius, rebound_y + (self.length - 2 * self.radius) * rebound_slope)
                    if y > self.width - self.radius:
                        (x, y) = (self.length - self.radius - (self.width - self.radius - rebound_y) / rebound_slope,
                                  self.width - self.radius)

                else:
                    (x, y) = (self.radius, rebound_y + (self.length - 2 * self.radius) * rebound_slope)
                    if y < self.radius:
                        (x, y) = (self.length - self.radius + (rebound_y - self.radius) / rebound_slope, self.radius)

            elif rebound_y == self.radius:

                if rebound_slope >= 0:
                    (x, y) = (rebound_x - (self.width - 2 * self.radius) / rebound_slope, self.width - self.radius)
                    if x < self.radius:
                        (x, y) = (self.radius, self.radius + (rebound_x - self.radius) * rebound_slope)

                else:
                    (x, y) = (rebound_x - (self.width - 2 * self.radius) / rebound_slope, self.width - self.radius)
                    if x > self.length - self.radius:
                        (x, y) = (self.length - self.radius,
                                  self.radius - (self.length - self.radius - rebound_x) * rebound_slope)
            else:

                if rebound_slope >= 0:
                    (x, y) = (rebound_x + (self.width - 2 * self.radius) / rebound_slope, self.radius)
                    if x > self.length - self.radius:
                        (x, y) = (self.length - self.radius,
                                  self.width - self.radius - (self.length - self.radius - rebound_x) * rebound_slope)

                else:
                    (x, y) = (rebound_x + (self.width - 2 * self.radius) / rebound_slope, self.radius)
                    if x < self.radius:
                        (x, y) = (self.radius, self.width - self.radius + (rebound_x - self.radius) * rebound_slope)

            rebound_x, rebound_y, rebound_slope = x, y, -rebound_slope

        return Point(rebound_x, rebound_y)

    def draw_impact_pos(self):
        if self.achievable_impact_pos:
            self.draw_ball(self.impact_pos, 'orange')
