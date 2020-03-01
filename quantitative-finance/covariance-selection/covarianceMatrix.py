import numpy as np
import random


def covarianceMatrix(A):
    meanVector = []
    lineNumber = len(A)
    varNumber = len(A[0])
    for j in range(varNumber):
        mean = 0
        for i in range(lineNumber):
            mean += A[i][j]
        meanVector.append(mean / lineNumber)
    covariance = np.zeros((varNumber, varNumber))
    for i in range(varNumber):
        for j in range(i + 1):
            cov = 0
            for k in range(lineNumber):
                cov += (A[k][i] - meanVector[i]) * (A[k][j] - meanVector[j])
            covariance[i][j] = cov / lineNumber
            covariance[j][i] = covariance[i][j]
    return covariance


matriceTest = np.zeros((100, 3))
for i in range(100):
    for j in range(3):
        if j == 0:
            matriceTest[i][j] = random.gauss(10, 1)
        elif j == 1:
            matriceTest[i][j] = random.randint(0, 50)
        elif j == 2:
            matriceTest[i][j] = np.random.binomial(60, 0.3)
