#!/usr/bin/python
# -*- coding: utf-8 -*-

from billiard import Billiard
import matplotlib.pyplot as plt
from trajectories.direct import Directtraj
from trajectories.oneparallel import Oneparallel
from trajectories.twoparallel import Twoparallel
from trajectories.perpendicular import Perpendicular


if __name__ == "__main__":
    test_billiard = Billiard(verbose=False)
    white_ball, coords_balls = test_billiard.put_random_balls(test_billiard.nb_balls)
    test_billiard = Billiard(white_ball, coords_balls)
    for ind_ball in range(test_billiard.nb_balls - 1):
        for ind_pos in range(test_billiard.nb_holes):
            test_direct_trajectory = Directtraj(
                white_ball=white_ball, coords_balls=coords_balls, index_ball=ind_ball, index_pos=ind_pos
            )
            test_oneparallel_trajectory = Oneparallel(
                white_ball=white_ball, coords_balls=coords_balls, index_ball=ind_ball, index_pos=ind_pos
            )
            test_twoparallel_trajectory = Twoparallel(
                white_ball=white_ball, coords_balls=coords_balls, index_ball=ind_ball, index_pos=ind_pos
            )
            test_perpendicular_trajectory = Perpendicular(
                white_ball=white_ball, coords_balls=coords_balls, index_ball=ind_ball, index_pos=ind_pos
            )
    plt.show()
