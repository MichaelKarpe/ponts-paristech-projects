#!/usr/bin/python
# -*- coding: utf-8 -*-

from ball import Ball
import numpy as np
from trajectory import Trajectory
from utils import dist, Point


class Perpendicular(Trajectory):
    def __init__(self, white_ball, coords_balls, index_ball, index_pos, verbose=True):
        super().__init__(white_ball, coords_balls, index_ball, index_pos, verbose=verbose)

        self.directions = [
            "left_to_up",
            "up_to_left",
            "up_to_right",
            "right_to_up",
            "right_to_down",
            "down_to_right",
            "down_to_left",
            "left_to_down",
        ]

        self.opposite = {
            "left_to_up": self.white_ball.x - self.hole_width,
            "up_to_left": self.white_ball.y - self.hole_width,
            "up_to_right": self.width - self.white_ball.y - self.hole_width,
            "right_to_up": self.white_ball.x - self.hole_width,
            "right_to_down": self.length - self.white_ball.x - self.hole_width,
            "down_to_right": self.width - self.white_ball.y - self.hole_width,
            "down_to_left": self.white_ball.y - self.hole_width,
            "left_to_down": self.length - self.white_ball.x - self.hole_width,
        }

        self.adjacent = {
            "left_to_up": self.white_ball.y - self.radius,
            "up_to_left": self.white_ball.x - self.radius,
            "up_to_right": self.white_ball.x - self.radius,
            "right_to_up": self.width - self.white_ball.y - self.radius,
            "right_to_down": self.width - self.white_ball.y - self.radius,
            "down_to_right": self.length - self.white_ball.x - self.radius,
            "down_to_left": self.length - self.white_ball.x - self.radius,
            "left_to_down": self.white_ball.y - self.radius,
        }

        self.correct_opposite = {
            "left_to_up": self.white_ball.x - self.radius,
            "up_to_left": self.white_ball.y - self.radius,
            "up_to_right": self.width - self.white_ball.y - self.radius,
            "right_to_up": self.white_ball.x - self.radius,
            "right_to_down": self.length - self.white_ball.x - self.radius,
            "down_to_right": self.width - self.white_ball.y - self.radius,
            "down_to_left": self.white_ball.y - self.radius,
            "left_to_down": self.length - self.white_ball.x - self.radius,
        }

        self.correct_adjacent = {
            "left_to_up": self.white_ball.y - self.radius,
            "up_to_left": self.white_ball.x - self.radius,
            "up_to_right": self.white_ball.x - self.radius,
            "right_to_up": self.width - self.white_ball.y - self.radius,
            "right_to_down": self.width - self.white_ball.y - self.radius,
            "down_to_right": self.length - self.white_ball.x - self.radius,
            "down_to_left": self.length - self.white_ball.x - self.radius,
            "left_to_down": self.white_ball.y - self.radius,
        }

        self.compute_all(directions=self.directions)

        if verbose:
            for direction in self.directions:
                self.display_trajectory(direction)

    def reachable_zone(self, direction):
        alpha, correct_alpha = {}, {}
        for direction in self.directions:
            alpha[direction] = np.arctan(self.opposite[direction] / self.adjacent[direction])
            if alpha[direction] <= np.pi / 4:
                correct_alpha[direction] = alpha[direction]
            else:
                correct_alpha[direction] = np.arctan(
                    self.correct_opposite[direction]
                    / (self.correct_adjacent[direction] + self.hole_width - self.radius)
                )

        plots = {
            "left_to_up": Point(
                self.white_ball.x - 2 * self.radius * np.sin(correct_alpha["left_to_up"]),
                self.white_ball.y - 2 * self.radius * np.cos(correct_alpha["left_to_up"]),
            ),
            "up_to_left": Point(
                self.white_ball.x - 2 * self.radius * np.cos(correct_alpha["up_to_left"]),
                self.white_ball.y - 2 * self.radius * np.sin(correct_alpha["up_to_left"]),
            ),
            "up_to_right": Point(
                self.white_ball.x - 2 * self.radius * np.cos(correct_alpha["up_to_right"]),
                self.white_ball.y + 2 * self.radius * np.sin(correct_alpha["up_to_right"]),
            ),
            "right_to_up": Point(
                self.white_ball.x - 2 * self.radius * np.sin(correct_alpha["right_to_up"]),
                self.white_ball.y + 2 * self.radius * np.cos(correct_alpha["right_to_up"]),
            ),
            "right_to_down": Point(
                self.white_ball.x + 2 * self.radius * np.sin(correct_alpha["right_to_down"]),
                self.white_ball.y + 2 * self.radius * np.cos(correct_alpha["right_to_down"]),
            ),
            "down_to_right": Point(
                self.white_ball.x + 2 * self.radius * np.cos(correct_alpha["down_to_right"]),
                self.white_ball.y + 2 * self.radius * np.sin(correct_alpha["down_to_right"]),
            ),
            "down_to_left": Point(
                self.white_ball.x + 2 * self.radius * np.cos(correct_alpha["down_to_left"]),
                self.white_ball.y - 2 * self.radius * np.sin(correct_alpha["down_to_left"]),
            ),
            "left_to_down": Point(
                self.white_ball.x + 2 * self.radius * np.sin(correct_alpha["left_to_down"]),
                self.white_ball.y - 2 * self.radius * np.cos(correct_alpha["left_to_down"]),
            ),
        }

        pt_color = plots[direction]

        return self.rebound_trajectory(pt_color, 1), self.rebound_trajectory(pt_color, 2)

    def change_of_basis(self, direction):
        first_rebound, second_rebound = self.reachable_zone(direction)

        vectors_balls = [
            np.array([[self.coords_balls[i].x - first_rebound.x], [self.coords_balls[i].y - first_rebound.y]])
            for i in range(self.nb_balls - 1)
        ]

        (u1, u2) = (second_rebound.x - first_rebound.x, second_rebound.y - first_rebound.y)

        matrix = (u1 ** 2 + u2 ** 2) ** (-0.5) * np.array([[u1, -u2], [u2, u1]])
        inv_matrix = np.linalg.inv(matrix)
        vectors_balls_in_new_basis = [np.dot(inv_matrix, vector) for vector in vectors_balls]

        all_vectors_shocks_in_new_basis = []

        for index_ball in range(self.nb_balls - 1):
            impact_positions = Ball(
                white_ball=self.white_ball, coords_balls=self.coords_balls, index_ball=index_ball, verbose=False
            ).impact_positions
            vectors_shocks = [
                np.array(
                    [
                        [impact_positions[index_pos].x - first_rebound.x],
                        [impact_positions[index_pos].y - first_rebound.y],
                    ]
                )
                for index_pos in range(self.nb_holes)
            ]

            vectors_shocks_in_new_basis = [np.dot(inv_matrix, vector) for vector in vectors_shocks]
            all_vectors_shocks_in_new_basis.append(vectors_shocks_in_new_basis)

        return vectors_balls_in_new_basis, all_vectors_shocks_in_new_basis

    def check_if_in_reachable_zone(self, direction):
        _, all_vectors_shocks_in_new_basis = self.change_of_basis(direction)
        if direction in {"left_to_up", "up_to_right", "right_to_down", "down_to_left"}:
            return all_vectors_shocks_in_new_basis[self.index_ball][self.index_pos][1][0] >= 0
        else:
            return all_vectors_shocks_in_new_basis[self.index_ball][self.index_pos][1][0] < 0

    def two_rebounds_angle(self, direction):
        a = self.correct_adjacent
        b = self.correct_opposite

        # adjacent
        c = {
            "left_to_up": self.impact_pos.y - self.radius,
            "up_to_left": self.impact_pos.x - self.radius,
            "up_to_right": self.impact_pos.x - self.radius,
            "right_to_up": self.width - self.impact_pos.y - self.radius,
            "right_to_down": self.width - self.impact_pos.y - self.radius,
            "down_to_right": self.length - self.impact_pos.x - self.radius,
            "down_to_left": self.length - self.impact_pos.x - self.radius,
            "left_to_down": self.impact_pos.y - self.radius,
        }

        # opposite
        d = {
            "left_to_up": self.impact_pos.x - self.radius,
            "up_to_left": self.impact_pos.y - self.radius,
            "up_to_right": self.width - self.impact_pos.y - self.radius,
            "right_to_up": self.impact_pos.x - self.radius,
            "right_to_down": self.length - self.impact_pos.x - self.radius,
            "down_to_right": self.width - self.impact_pos.y - self.radius,
            "down_to_left": self.impact_pos.y - self.radius,
            "left_to_down": self.length - self.impact_pos.x - self.radius,
        }

        return np.arctan((b[direction] + d[direction]) / (a[direction] + c[direction])), a, b, c, d

    def rebound_positions(self, direction):
        alpha, a, b, c, d = self.two_rebounds_angle(direction)
        b1, c2 = a[direction] * np.tan(alpha), d[direction] / np.tan(alpha)

        rebound_coords = {
            "left_to_up": [Point(self.white_ball.x - b1, self.radius), Point(self.radius, self.impact_pos.y - c2)],
            "up_to_left": [Point(self.radius, self.white_ball.y - b1), Point(self.impact_pos.x - c2, self.radius)],
            "up_to_right": [
                Point(self.radius, self.white_ball.y + b1),
                Point(self.impact_pos.x - c2, self.width - self.radius),
            ],
            "right_to_up": [
                Point(self.white_ball.x - b1, self.width - self.radius),
                Point(self.radius, self.impact_pos.y + c2),
            ],
            "right_to_down": [
                Point(self.white_ball.x + b1, self.width - self.radius),
                Point(self.length - self.radius, self.impact_pos.y + c2),
            ],
            "down_to_right": [
                Point(self.length - self.radius, self.white_ball.y + b1),
                Point(self.impact_pos.x + c2, self.width - self.radius),
            ],
            "down_to_left": [
                Point(self.length - self.radius, self.white_ball.y - b1),
                Point(self.impact_pos.x + c2, self.radius),
            ],
            "left_to_down": [
                Point(self.white_ball.x + b1, self.radius),
                Point(self.length - self.radius, self.impact_pos.y - c2),
            ],
        }

        distances = [
            a[direction] / np.cos(alpha),
            (b[direction] - b1) / np.sin(alpha),
            d[direction] / np.sin(alpha),
            dist(self.holes[self.index_pos], self.coords_balls[self.index_ball]),
        ]

        return rebound_coords[direction], distances
