from numpy import *
from pymprog import *
import pandas
import xlsxwriter


# Lecture des paramètres

parametres = pandas.read_csv(open('Parametres.csv'),
                             encoding='utf-8', quotechar='"', delimiter=';').values[:, 1:]

nb_eleves = int(parametres[0, 0])
nb_proj_dep = int(parametres[1, 0])
nb_jours = 4
nb_projets = [int(parametres[i + 2, 0]) for i in range(nb_jours)]
nb_voeux_PIR = int(parametres[6, 0])

E = range(nb_eleves)
D = range(nb_proj_dep)
J = range(nb_jours)
P = [range(nb_projets[k]) for k in range(nb_jours)]
PR = range(sum(nb_projets))

ExD = iprod(E, D)
ExP = [iprod(E, P[j]) for j in range(nb_jours)]
ExJ = iprod(E, J)

nom_eleves = pandas.read_csv(open('ListeEleves.csv'),
                             encoding='utf-8', quotechar='"', delimiter=';').values[:, 1:]


def nom_eleve(ind_eleve):
    return nom_eleves[ind_eleve - 1][0]


effectifs_departement = pandas.read_csv(open('EffectifsDepartement.csv'),
                                        encoding='utf-8', quotechar='"', delimiter=';').values[:, 1:]


def eff_min_dep(num_proj):
    return effectifs_departement[num_proj][0]


def eff_max_dep(num_proj):
    return effectifs_departement[num_proj][1]


def nom_proj_dep(num_proj):
    return effectifs_departement[num_proj - 1][2]


# Mise en forme des résultats

def affectation_departement(aff_dep):
    # Cout total
    print("Total Cost = %g" % vobj())

    results = [0 for eleve in range(nb_eleves)]
    assign = [(eleve, projet) for eleve in E for projet in D
              if aff_dep[eleve, projet].primal > 0.5]
    for eleve, projet in assign:
        results[eleve] = projet + 1
        print("Student %d gets Project %d" % (eleve + 1, projet + 1))

    return results


# Résolution complète du problème

def optimisation_departement():
    donnees = pandas.read_csv(open('VoeuxDepartement.csv'),
                              encoding='utf-8', quotechar='"', delimiter=';').values[:, 1:]

    regret_departement = [[(donnees[eleve][projet] - 1) ** 2 for projet in range(nb_proj_dep)]
                          for eleve in range(nb_eleves)]

    begin("assign")

    # Variables
    ouv_dep = var('ouv_dep', D)
    aff_dep = var('aff_dep', ExD)
    eff_dep = var('eff_dep', D)

    # Fonction objectif
    minimize(sum(regret_departement[eleve][projet] * aff_dep[eleve, projet] for eleve, projet in ExD))

    # Contraintes
    for eleve in E:
        sum(aff_dep[eleve, projet] for projet in D) == 1
    for projet in D:
        sum(aff_dep[eleve, projet] for eleve in E) == eff_dep[projet]
        eff_min_dep(projet) <= eff_dep[projet]
        eff_max_dep(projet) >= eff_dep[projet]

    # Résolution
    solve()

    # Ecriture des résultats
    results = affectation_departement(aff_dep)
    resultats_departement_xlsx(results)


# Fonction d'écriture des résultats

def resultats_departement_xlsx(results):
    # Dans un fichier Excel

    # Create a workbook and add a worksheet.
    workbook = xlsxwriter.Workbook('ResultatsDepartement.xlsx')
    worksheet = workbook.add_worksheet()

    # Some data we want to write to the worksheet.
    expenses = ([nom_eleve(i + 1), results[i]] for i in range(nb_eleves))

    # Start from the first cell. Rows and columns are zero indexed.
    row = 0
    col = 0

    worksheet.write(row, col, "Elèves")
    worksheet.write(row, col + 1, "Projet de département")
    row += 1

    # Iterate over the data and write it out row by row.
    for i, j in expenses:
        worksheet.write(row, col, i)
        worksheet.write(row, col + 1, nom_proj_dep(j))
        row += 1

    workbook.close()


if __name__ == '__main__':
    optimisation_departement()
