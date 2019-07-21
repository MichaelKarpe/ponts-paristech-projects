#!/usr/bin/python
# -*- coding: utf-8 -*-

from trajectory import Trajectory
from utils import Point, dist


class Oneparallel(Trajectory):
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
        dist_to_directions = {
            "x_left": self.white_ball.x + self.impact_pos.x - 2 * self.radius,
            "x_top": abs(self.white_ball.x - self.impact_pos.x),
            "x_right": 2 * self.length - (self.white_ball.x + self.impact_pos.x + 2 * self.radius),
            "x_bottom": abs(self.white_ball.x - self.impact_pos.x),
            "y_left": abs(self.white_ball.y - self.impact_pos.y),
            "y_top": 2 * self.width - (self.white_ball.y + self.impact_pos.y + 2 * self.radius),
            "y_right": abs(self.white_ball.y - self.impact_pos.y),
            "y_bottom": self.white_ball.y + self.impact_pos.y - 2 * self.radius,
        }

        rebound_coords = {
            "left": [
                Point(
                    self.radius,
                    self.white_ball.y
                    + (self.impact_pos.y - self.white_ball.y)
                    / abs(self.impact_pos.y - self.white_ball.y)
                    * dist_to_directions["y_left"]
                    * (self.white_ball.x - self.radius)
                    / dist_to_directions["x_left"],
                )
            ],
            "top": [
                Point(
                    self.white_ball.x
                    + (self.impact_pos.x - self.white_ball.x)
                    / abs(self.impact_pos.x - self.white_ball.x)
                    * dist_to_directions["x_top"]
                    * (self.width - (self.white_ball.y + self.radius))
                    / dist_to_directions["y_top"],
                    self.width - self.radius,
                )
            ],
            "right": [
                Point(
                    self.length - self.radius,
                    self.white_ball.y
                    + (self.impact_pos.y - self.white_ball.y)
                    / abs(self.impact_pos.y - self.white_ball.y)
                    * dist_to_directions["y_right"]
                    * (self.length - (self.white_ball.x + self.radius))
                    / dist_to_directions["x_right"],
                )
            ],
            "bottom": [
                Point(
                    self.white_ball.x
                    + (self.impact_pos.x - self.white_ball.x)
                    / abs(self.impact_pos.x - self.white_ball.x)
                    * dist_to_directions["x_bottom"]
                    * (self.white_ball.y - self.radius)
                    / dist_to_directions["y_bottom"],
                    self.radius,
                )
            ],
        }

        distances = [
            dist(self.white_ball, rebound_coords[direction][0]),
            dist(rebound_coords[direction][0], self.impact_pos),
            dist(self.pt, self.holes[self.index_pos]),
        ]

        return rebound_coords[direction], distances
