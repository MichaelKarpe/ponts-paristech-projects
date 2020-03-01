from math import *
import numpy as np
import matplotlib.pyplot as plt

ecart = 0.15

normalizer = sqrt(2)

Lpts1 = [
    (0, 0),
    (1 / 2 - ecart, sqrt(2) / 2 - sqrt(3) * ecart),
    (1 / 2 - ecart, sqrt(2) / 2 + sqrt(3) * ecart),
    (0, sqrt(2)),
    (1, sqrt(2)),
    (1 / 2 + ecart, sqrt(2) / 2 + sqrt(3) * ecart),
    (1 / 2 + ecart, sqrt(2) / 2 - sqrt(3) * ecart),
    (1, 0),
]

Lpts = []
for ind in range(len(Lpts1)):
    Lpts.append((Lpts1[ind][0] / normalizer, Lpts1[ind][1] / normalizer))

file = []
for i in range(len(Lpts) - 1):
    lign = "{} {} {} {}".format(Lpts[i][0], Lpts[i][1], Lpts[i + 1][0], Lpts[i + 1][1])
    print(lign)

lign = "{} {} {} {}".format(Lpts[-1][0], Lpts[-1][1], Lpts[0][0], Lpts[0][1])
print(lign)
