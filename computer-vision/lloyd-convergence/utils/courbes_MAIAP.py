import numpy as np
import matplotlib.pyplot as plt

from numpy.polynomial import Polynomial

plt.close("all")

import os

# os.chdir("~/home")

length = []
file = open("length.txt", "r")
for ligne in file:
    length.append(float(ligne.split(",")[:-1][0]))
av = np.array(length[:])


X = np.array(range(1, len(av) + 1))

# z=np.polyfit(X,av,2)[::-1]
# p=Polynomial(z)
# print([p(x) for x in X])
# plt.plot(X,[p(x) for x in X], color="red",label="Interpolée")


plt.semilogy(X, av, color="blue", marker=".")
plt.xlabel("Number of iterations")
plt.ylabel("Average length")
plt.show()

"""plt.figure()
plt.plot(X,av,color="blue",marker='.')
plt.xlabel("Number of iterations")
plt.ylabel("Average length")
plt.show()"""


# energy = [0.020357, 0.018909, 0.018143, 0.017686, 0.017409, 0.017255, 0.017161, 0.017107, 0.017078, 0.017063, 0.017054, 0.017047, 0.017044, 0.017041, 0.017039, 0.017038, 0.017037, 0.0170436, 0.0170435, 0.0170434]
# X1=np.array(range(len(energy)))
#
# plt.figure()
# plt.plot(X1,energy,color="blue",marker='o',label="Valeurs")
# plt.xlabel("Number of iterations")
# plt.ylabel("Energy")
# plt.legend()
# plt.show()


energies = []
file = open("energies.txt", "r")
for ligne in file:
    energies.append(ligne.split(",")[:-1])

energies = np.array([[float(energies[i][j]) for j in range(len(energies[0]))] for i in range(len(energies))])

plt.figure()


X2 = np.array(range(1, len(energies) + 1))

for i in range(len(energies[0])):
    plt.plot(X2, energies[:, i], label="Cell " + str(i + 1))
plt.xlabel("Number of iterations")
plt.ylabel("Energy")
# plt.legend()
plt.show()
