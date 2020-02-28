#!/usr/bin/python
# -*- coding: utf-8 -*-

from abc import abstractmethod
from impactpositions import Impactposition
import matplotlib.pyplot as plt
import numpy as np


class Trajectory(Impactposition):
    def __init__(self, white_ball, coords_balls, index_ball, index_pos, verbose=True):
        super().__init__(white_ball, coords_balls, index_ball, index_pos, verbose=verbose)
        self.rebound_coords, self.distances, self.initial_speed, self.achievable_trajectory = {}, {}, {}, {}

    @abstractmethod
    def rebound_positions(self, direction):
        raise NotImplementedError("Must override rebound_positions")

    @abstractmethod
    def check_if_in_reachable_zone(self, direction):
        raise NotImplementedError("Must override rebound_positions")

    def compute_all(self, directions):
        self.achievable_trajectory = {key: False for key in directions}
        for direction in directions:

            if self.achievable_impact_pos and self.check_if_in_reachable_zone(direction):
                rebound_coords, distances = self.rebound_positions(direction)

                if self.check_if_not_in_hole(rebound_coords) and self.check_trajectory(rebound_coords):
                    self.rebound_coords[direction] = rebound_coords
                    self.distances[direction] = distances
                    collision_angle = self.shock_return(rebound_coords[-1], self.impact_pos, self.pt)

                    if collision_angle >= 0:
                        # TODO : Check if always necessary or only for perpendicular trajectories
                        self.initial_speed[direction] = self.compute_initial_speed(distances, collision_angle)

                        if self.check_initial_speed(direction):
                            self.achievable_trajectory[direction] = True

    def shock_return(self, pt_init, pt_impact, pt_color):
        # TODO : Check why if result is negative, impact_position is not reachable
        u1, u2 = pt_impact.x - pt_init.x, pt_impact.y - pt_init.y
        matrix = (u1 ** 2 + u2 ** 2) ** (-0.5) * np.array([[u1, -u2], [u2, u1]])
        inv_matrix = np.linalg.inv(matrix)
        vect = np.dot(inv_matrix, np.array([[pt_color.x - pt_impact.x], [pt_color.y - pt_impact.y]]))
        return vect[0][0] / (2 * self.radius)

    def compute_initial_speed(self, distances, collision_angle):
        n = len(distances)
        if sum(distances) == 0:
            return 0
        else:
            return np.sqrt(
                2
                * self.acceleration
                * 0.01
                * (
                    sum([self.border_restitution ** (n - i - 2) * collision_angle * distances[i] for i in range(n - 1)])
                    + distances[n - 1]
                )
                / (self.border_restitution ** (n - 2) * collision_angle)
            )

    def check_if_not_in_hole(self, rebound_coords):
        for rebound_pos in rebound_coords:
            if (
                (rebound_pos.x <= self.hole_width or rebound_pos.x >= self.length - self.hole_width)
                and (rebound_pos.y <= self.hole_width or rebound_pos.y >= self.width - self.hole_width)
                or (
                    self.width - self.hole_width <= rebound_pos.x <= self.width + self.hole_width
                    and (rebound_pos.y == self.radius or rebound_pos.y == self.width - self.radius)
                )
            ):
                return False
        return True

    def check_initial_speed(self, direction):
        return self.initial_speed[direction] < self.max_speed

    def check_path(self, pt1, pt2=None):
        if pt2 is None:
            return True

        vects = [np.array([[self.white_ball.x - pt1.x], [self.white_ball.y - pt1.y]])] + [
            np.array([[self.coords_balls[ind_ball].x - pt1.x], [self.coords_balls[ind_ball].y - pt1.y]])
            for ind_ball in range(len(self.coords_balls))
        ]

        u1, u2 = pt2.x - pt1.x, pt2.y - pt1.y
        matrix = (u1 ** 2 + u2 ** 2) ** (-0.5) * np.array([[u1, -u2], [u2, u1]])
        inv_matrix = np.linalg.inv(matrix)
        vects_new_basis = [(np.dot(inv_matrix, vect)[0][0], np.dot(inv_matrix, vect)[1][0]) for vect in vects] + [
            (np.dot(inv_matrix, np.array([[u1], [u2]]))[0][0], np.dot(inv_matrix, np.array([[u1], [u2]]))[1][0])
        ]

        for vect in vects_new_basis[1:-1]:
            eps = 1e-3
            if eps <= vect[0] <= vects_new_basis[-1][0] and eps <= abs(vect[1]) <= 2 * self.radius:
                return False

        return True

    def check_trajectory(self, rebound_coords):
        checked_paths = (
            [self.check_path(self.white_ball, rebound_coords[0])]
            + [
                self.check_path(rebound_coords[ind_rebound], rebound_coords[ind_rebound + 1])
                for ind_rebound in range(len(rebound_coords) - 1)
            ]
            + [
                self.check_path(rebound_coords[-1], self.impact_pos),
                self.check_path(self.pt, self.holes[self.index_pos]),
            ]
        )

        return sum(checked_paths) == len(checked_paths)

    def display_trajectory(self, direction):
        if self.achievable_trajectory[direction]:
            x = (
                [self.white_ball.x]
                + [
                    self.rebound_coords[direction][ind_rebound].x
                    for ind_rebound in range(len(self.rebound_coords[direction]))
                ]
                + [self.impact_pos.x]
            )
            y = (
                [self.white_ball.y]
                + [
                    self.rebound_coords[direction][ind_rebound].y
                    for ind_rebound in range(len(self.rebound_coords[direction]))
                ]
                + [self.impact_pos.y]
            )
            plt.plot(x, y, color="black")
