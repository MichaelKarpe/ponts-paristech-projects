import csv


def diff(A):
    B = []
    for i in range(len(A) - 1):
        rowDiff = [A[i + 1][j] - A[i][j] for j in range(len(A[0]))]
        B.append(rowDiff)
    return B


def readCsv(fileName):
    matrix = []
    with open(fileName, newline="") as csvfile:
        filereader = csv.reader(csvfile)
        next(filereader)
        for row in filereader:
            isComplete = True
            for i in row:
                if i == ".":
                    isComplete = False
            if isComplete:
                matrix.append(list(map(float, row[1:])))
    return diff(matrix)


def writeCsv(A, fileName):
    with open(fileName, "w", newline="") as csvfile:
        filewritten = csv.writer(csvfile)
        for i in range(len(A)):
            filewritten.writerow(A[i, :])
