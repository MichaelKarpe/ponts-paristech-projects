#!/usr/bin/python
# -*- coding: utf-8 -*-

from trajectory import Trajectory
from utils import Point, dist


class Twoparallel(Trajectory):
    def __init__(self, white_ball, coords_balls, index_ball, index_pos, verbose=True):
        super().__init__(white_ball, coords_balls, index_ball, index_pos, verbose=verbose)
        self.directions = ["left", "top", "right", "bottom"]

        self.compute_all(directions=self.directions)

        if verbose:
            for direction in self.directions:
                self.display_trajectory(direction)

    def check_if_in_reachable_zone(self, direction):
        return True

    def rebound_positions(self, direction):
        dist_to_directions = {"x_left": 2 * self.length + self.white_ball.x - self.impact_pos.x - 4 * self.radius,
                              "x_top": abs(self.white_ball.x - self.impact_pos.x),
                              "x_right": 2 * self.length + self.impact_pos.x - self.white_ball.x - 4 * self.radius,
                              "x_bottom": abs(self.white_ball.x - self.impact_pos.x),
                              "y_left": abs(self.white_ball.y - self.impact_pos.y),
                              "y_top": 2 * self.width + self.impact_pos.y - self.white_ball.y - 4 * self.radius,
                              "y_right": abs(self.white_ball.y - self.impact_pos.y),
                              "y_bottom": 2 * self.width + self.white_ball.y - self.impact_pos.y - 4 * self.radius}

        rebound_coords = {
            "left": [Point(self.radius,
                           self.white_ball.y + (self.impact_pos.y - self.white_ball.y)
                           / abs(self.impact_pos.y - self.white_ball.y) * (self.white_ball.x - self.radius)
                           * dist_to_directions["y_left"] / dist_to_directions["x_left"]),
                     Point(self.length - self.radius,
                           self.white_ball.y + (self.impact_pos.y - self.white_ball.y)
                           / abs(self.impact_pos.y - self.white_ball.y)
                           * (self.white_ball.x + self.length - 3 * self.radius)
                           * dist_to_directions["y_left"] / dist_to_directions["x_left"])],
            "top": [Point(self.white_ball.x + (self.impact_pos.x - self.white_ball.x)
                          / abs(self.impact_pos.x - self.white_ball.x)
                          * (self.width - self.white_ball.y - self.radius) * dist_to_directions["x_top"] /
                          dist_to_directions[
                              "y_top"],
                          self.width - self.radius),
                    Point(self.white_ball.x + (self.impact_pos.x - self.white_ball.x)
                          / abs(self.impact_pos.x - self.white_ball.x)
                          * (2 * self.width - self.white_ball.y - 3 * self.radius)
                          * dist_to_directions["x_top"] / dist_to_directions["y_top"],
                          self.radius)],
            "right": [Point(self.length - self.radius,
                            self.white_ball.y + (self.impact_pos.y - self.white_ball.y)
                            / abs(self.impact_pos.y - self.white_ball.y)
                            * (self.length - self.white_ball.x - self.radius)
                            * dist_to_directions["y_right"] / dist_to_directions["x_right"]),
                      Point(self.radius, self.white_ball.y + (self.impact_pos.y - self.white_ball.y)
                            / abs(self.impact_pos.y - self.white_ball.y) * (
                                    2 * self.length - self.white_ball.x - 3 * self.radius)
                            * dist_to_directions["y_right"] / dist_to_directions["x_right"])],
            "bottom": [Point(self.white_ball.x + (self.impact_pos.x - self.white_ball.x)
                             / abs(self.impact_pos.x - self.white_ball.x)
                             * (self.white_ball.y - self.radius)
                             * dist_to_directions["x_bottom"] / dist_to_directions["y_bottom"],
                             self.radius),
                       Point(self.white_ball.x + (self.impact_pos.x - self.white_ball.x)
                             / abs(self.impact_pos.x - self.white_ball.x)
                             * (self.width + self.white_ball.y - 3 * self.radius)
                             * dist_to_directions["x_bottom"] / dist_to_directions["y_bottom"],
                             self.width - self.radius)]
        }

        distances = [dist(self.white_ball, rebound_coords[direction][0]),
                     dist(rebound_coords[direction][0], rebound_coords[direction][1]),
                     dist(rebound_coords[direction][1], self.impact_pos),
                     dist(self.pt, self.holes[self.index_pos])]

        return rebound_coords[direction], distances
