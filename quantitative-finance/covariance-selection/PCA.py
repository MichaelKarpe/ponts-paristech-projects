from math import *
from numpy import *

##Paramètres

n = 4
rho = 1

##Variables globales

D2 = n * n / 2

S = array([[1, 2, 3, 4], [9, 10, 11, 12], [13, 14, 15, 16], [5, 6, 7, 8]])
Xtest = array([[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, 16]])
A = ones((4, 4))
B = 5 * eye(2)


##Step 1


def uetoile(X, mu):
    return max(min(X.min() / mu, rho), -rho)


def gradfmu(X, S, mu):
    return -X.inv() + S + uetoile(X, mu)


def psieps(x, eps):
    if abs(x) >= (eps / (2 * rho * D2)):
        return abs(x) - (eps / 4 * D2)
    else:
        return D2 * x * x / eps


def feps(X, eps):
    return fchap(X) + sum([[sum([psieps(X[i][j], eps) for j in range(n)])] for i in range(n)])
