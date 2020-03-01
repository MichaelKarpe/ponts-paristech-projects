from math import *
from numpy import *
import random
import csvReader
import covarianceMatrix
import matplotlib.pyplot as plt

##Paramètres

n = 20
rho = 0.15
MaxIter = 1000
eps = 10 ** -5
nonzero = 8
possibleNoise = [-1, 1]

##Variables globales

D2 = n * n / 2
alpha = 10 ** -1
beta = 10
sigma1 = 1 / (beta ** 2)
##Fonctions utiles
def is_pos_def(A):
    return all(linalg.eigvals(A) > 0)


def is_sym(A):
    for i in range(n):
        for j in range(n):
            if A[i][j] != A[j][i]:
                return False
    return True


def uetoile(X, eps):
    return max(min(X.min() / eps, rho), -rho)


def gradfeps(X, covar, eps):  # First step
    return real(-linalg.inv(X) + covar + uetoile(X, eps))


def psieps(x, eps):
    if abs(x) >= (eps / (2 * rho * D2)):
        return abs(x) - (eps / (4 * D2))
    else:
        return D2 * x * x / eps


def feps(X, eps):
    return fchap(X) + sum([[sum([psieps(X[i][j], eps) for j in range(n)])] for i in range(n)])


def L(eps):
    return 1 / (alpha ** 2) + D2 * (rho ** 2) / (2 * eps)


def prodscal(A, B):
    return trace(dot(transpose(A), B))


def computeCard(A):
    card = 0
    for i in range(len(A[0])):
        for j in range(len(A)):
            card += abs(A[i][j])
    return card


##Step 2
def Y(X, gradX, eps, covar):
    G = X - gradX / L(eps)
    gamma, V = linalg.eig(G)  # valeurs, vecteur propres de G
    lambda0 = [min(max(gamma[i], alpha), beta) for i in range(n)]  # tableau des lambda
    return dot(V, dot(diag(lambda0), linalg.inv(V)))


##Step 3
def Z(listeGradX, eps, k, covar):  # listeX=[X[0],...,X[k]]
    S = zeros((n, n))
    for i in range(k + 1):
        S += (i + 1) * listeGradX[i]
    S *= sigma1 / (2 * L(eps))
    sigma, V = linalg.eig(S)  # valeurs, vecteur propres de S
    lambda0 = [min(max(1 / sigma[i], alpha), beta) for i in range(n)]
    return dot(V, dot(diag(lambda0), linalg.inv(V)))


def phi(U, X, covar):
    inverse = linalg.inv(covar + U)
    val, vect = linalg.eig(inverse)
    for i in range(len(val)):
        if val[i] < alpha:
            val[i] = alpha
        elif val[i] > beta:
            val[i] = beta
    Xres = dot(vect, dot(diag(val), linalg.inv(vect)))
    return -log(linalg.det(Xres)) + prodscal(covar + U, Xres)


## Main algorithm function
def nesterov(alpha, beta, rho, eps, covar):
    k = 0
    Xk = beta * eye(n)
    gradXk = gradfeps(Xk, covar, eps)
    listeGradXk = [gradXk]
    Yk = Y(Xk, gradXk, eps, covar)
    Zk = Z(listeGradXk, eps, k, covar)
    Xk = 2 / (k + 3) * Zk + (k + 1) / (k + 3) * Yk
    Uk = zeros((n, n))
    Uk = (k * Uk + 2 * uetoile(Xk, eps)) / (k + 2)
    card = computeCard(Yk)
    duality_gap = -log(linalg.det(Yk)) + prodscal(covar, Yk) + rho * card - phi(Uk, Xk, covar)
    k += 1
    while (duality_gap > eps) and k <= MaxIter:
        gradXk = gradfeps(Xk, covar, eps)
        listeGradXk.append(gradXk)
        Yk = Y(Xk, gradXk, eps, covar)
        Zk = Z(listeGradXk, eps, k, covar)
        Xk = real(2 / (k + 3) * Zk + (k + 1) / (k + 3) * Yk)
        Uk = (k * Uk + 2 * uetoile(Xk, eps)) / (k + 2)
        card = computeCard(Yk)
        duality_gap = -log(linalg.det(Yk)) + prodscal(covar, Yk) + rho * card - phi(Uk, Xk, covar)
        k += 1
    print(k)
    return Xk


##test
def plotmatrix(A):
    im1 = plt.matshow(A)
    plt.colorbar(im1)


def testRandomMatrix():
    A = zeros((n, n))
    while linalg.det(A) == 0:
        bruit = zeros((n, n))
        for c in range(nonzero):
            i = random.randint(0, n - 1)
            j = random.randint(0, n - 1)
            while j == i:
                j = random.randint(0, n - 1)
            bruit[i][j] = possibleNoise[random.randint(0, len(possibleNoise) - 1)]
            bruit[j][i] = bruit[i][j]
        A = eye(n)
        A = A + bruit
    C = zeros((n, n))
    # random.seed(0)
    for i in range(n):
        for j in range(n):
            C[i][j] = random.uniform(-1, 1)
    C = 0.5 * (transpose(C) + C)
    B = linalg.inv(A) + 0.15 * C
    valp, vectp = linalg.eig(B)
    for i in range(len(valp)):
        if valp[i] <= 0:
            valp[i] = 10 ** -3
    B = dot(vectp, dot(diag(valp), linalg.inv(vectp)))
    plotmatrix(A)
    inverseB = linalg.inv(B)
    alpha = 10 ** -1
    beta = 11
    sigma1 = 1 / (beta ** 2)

    solution = linalg.inv(nesterov(alpha, beta, rho, eps, B))
    for i in range(n):
        for j in range(n):
            inverseB[i][j] = floor(inverseB[i][j])
            solution[i][j] = floor(solution[i][j])
    plotmatrix(inverseB)
    plotmatrix(solution)
    plt.show()


def testRealData(fileName):
    empiricalMatrix = csvReader.readCsv(fileName)
    covMat = covarianceMatrix.covarianceMatrix(empiricalMatrix)
    solution = nesterov(alpha, beta, rho, eps, covMat)
    inverseCov = linalg.inv(covMat)
    for i in range(n):
        for j in range(n):
            if i == j:
                solution[i][j] = 0
            elif solution[i][j] <= 10 ** -7 and solution[i][j] >= -(10 ** -7):
                solution[i][j] = 0
    csvReader.writeCsv(solution, "sol.csv")
    csvReader.writeCsv(inverseCov, "invCov.csv")
    plotmatrix(inverseCov)
    plotmatrix(solution)
    plt.show()


# testRealData('Daily.csv')
testRandomMatrix()
