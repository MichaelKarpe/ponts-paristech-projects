#!/usr/bin/python
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
from numpy.random import rand
from utils import dist, Point


class Billiard:
    def __init__(self, white_ball=None, coords_balls=None, verbose=True):
        self.width = 91
        self.length = 2 * self.width

        self.radius = 2.5

        self.nb_holes = 6
        self.nb_strips = 4
        self.hole_width = 3 * self.radius

        self.holes = [
            Point(self.radius, self.radius),
            Point(self.radius, self.width - self.radius),
            Point(self.length / 2, self.width - self.radius),
            Point(self.length - self.radius, self.width - self.radius),
            Point(self.length - self.radius, self.radius),
            Point(self.length / 2, self.radius),
        ]

        self.max_speed = 2
        self.acceleration = 0.17
        self.border_restitution = 0.8

        self.nb_balls = 15

        self.white_ball, self.coords_balls = white_ball, coords_balls

        if verbose:
            self.draw_billiard()
            self.draw_random_balls()

    def put_random_balls(self, nb_balls):
        coords_balls = []
        while len(coords_balls) < nb_balls:
            if len(coords_balls) == 0:
                new_coords = Point(
                    (self.length - 4 * self.hole_width) * rand() + 2 * self.hole_width,
                    (self.width - 4 * self.hole_width) * rand() + 2 * self.hole_width,
                )
            else:
                new_coords = Point(
                    (self.length - 2 * self.hole_width) * rand() + self.hole_width,
                    (self.width - 2 * self.hole_width) * rand() + self.hole_width,
                )

            if sum([dist(new_coords, coords) > 2 * self.radius for coords in coords_balls]) == len(coords_balls):
                coords_balls.append(new_coords)

        white_ball = coords_balls[0]
        coords_balls = coords_balls[1:]

        return white_ball, coords_balls

    def draw_billiard(self):
        holes_borders = {
            "bottom_left": [Point(0, self.hole_width), Point(0, 0), Point(self.hole_width, 0)],
            "bottom_middle": [
                Point(self.length / 2 - self.hole_width, 0),
                Point(self.length / 2, 0),
                Point(self.length / 2 + self.hole_width, 0),
            ],
            "bottom_right": [
                Point(self.length - self.hole_width, 0),
                Point(self.length, 0),
                Point(self.length, self.hole_width),
            ],
            "top_right": [
                Point(0, self.width - self.hole_width),
                Point(0, self.width),
                Point(self.hole_width, self.width),
            ],
            "top_middle": [
                Point(self.length / 2 - self.hole_width, self.width),
                Point(self.length / 2, self.width),
                Point(self.length / 2 + self.hole_width, self.width),
            ],
            "top_left": [
                Point(self.length - self.hole_width, self.width),
                Point(self.length, self.width),
                Point(self.length, self.width - self.hole_width),
            ],
        }

        plt.fill_between((0, self.length), 0, self.width, facecolor="green")

        for ind in range(self.nb_holes):
            plt.gcf().gca().add_artist(plt.Circle((self.holes[ind].x, self.holes[ind].y), self.radius, color="gray"))

        for borders in holes_borders.values():
            plt.plot(
                [borders[i].x for i in range(len(borders))], [borders[i].y for i in range(len(borders))], color="red"
            )

        plt.xlim(-5, self.length + 5)
        plt.ylim(-5, self.width + 5)

    def draw_ball(self, pt, color):
        plt.gcf().gca().add_artist(plt.Circle((pt.x, pt.y), self.radius, color=color))

    def draw_random_balls(self):
        self.draw_ball(self.white_ball, "white")
        self.draw_ball(self.coords_balls[0], "black")
        for ind, pt in enumerate(self.coords_balls[1:]):
            if ind % 2 == 0:
                self.draw_ball(pt, "red")
            else:
                self.draw_ball(pt, "yellow")
