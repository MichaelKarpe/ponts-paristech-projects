#!/usr/bin/python
# -*- coding: utf-8 -*-

from trajectory import Trajectory
from utils import dist


class Directtraj(Trajectory):
    def __init__(self, white_ball, coords_balls, index_ball, index_pos, verbose=True):
        super().__init__(white_ball, coords_balls, index_ball, index_pos, verbose=verbose)

        self.initial_speed, self.achievable_trajectory = {"direct": None}, {"direct": False}
        self.rebound_coords["direct"] = []

        if self.achievable_impact_pos and self.check_path(self.white_ball, self.impact_pos) \
                and self.check_path(self.pt, self.holes[self.index_pos]):
            collision_angle = self.shock_return(self.white_ball, self.impact_pos, self.pt)

            if collision_angle >= 0:  # Tout le temps ou que pour perpendiculaire ?
                distances = self.direct_distances()
                self.initial_speed["direct"] = self.compute_initial_speed(distances, collision_angle)

                if self.check_initial_speed("direct"):
                    self.achievable_trajectory["direct"] = True

        if verbose:
            self.display_trajectory("direct")

    def check_if_in_reachable_zone(self, direction):
        return True

    def direct_distances(self):
        distances = [dist(self.white_ball, self.impact_pos),
                     dist(self.pt, self.holes[self.index_pos])]

        return distances

    def rebound_positions(self, direction):
        return None, None
