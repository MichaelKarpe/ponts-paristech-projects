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


def nom_eleve(eleve):
    return nom_eleves[eleve - 1][0]


effectifs_recherche = pandas.read_csv(open('EffectifsRecherche.csv'),
                                      encoding='utf-8', quotechar='"', delimiter=';').values[:, 2:]


def eff_min_cours(jour, projet):
    return effectifs_recherche[int(sum(nb_projets[:(jour - 1)]) + projet - 1)][0]


def eff_max_cours(jour, projet):
    return effectifs_recherche[int(sum(nb_projets[:(jour - 1)]) + projet - 1)][1]


def eff_min_proj(jour, projet):
    return effectifs_recherche[int(sum(nb_projets[:(jour - 1)]) + projet - 1)][2]


def eff_max_proj(jour, projet):
    return effectifs_recherche[int(sum(nb_projets[:(jour - 1)]) + projet - 1)][3]


def nom_proj_rech(jour, projet):
    return effectifs_recherche[int(sum(nb_projets[:(jour - 1)]) + projet - 1)][4]


def nom_proj_rech_2(projet):
    return effectifs_recherche[projet - 1][5]


# Mise en forme des résultats


def affectation_recherche(aff_cours, aff_proj):
    # Cout total
    print("Total Cost = %g" % vobj())

    results = [[0 for projet in range(5)] for eleve in range(nb_eleves)]

    # Cours chaque jour
    for jour in range(nb_jours):
        assign2 = [(eleve, projet) for eleve in E for projet in P[jour]
                   if aff_cours[jour][eleve, projet].primal > 0.5]
        for eleve, projet in assign2:
            results[eleve][jour] = projet + 1
            print("Student %d gets on Day %d Course %d" % (eleve + 1, jour + 1, projet + 1))

    # Projets de recherche
    for eleve in E:
        assign3 = [projet for projet in PR
                   if aff_proj[eleve, projet].primal > 0.5]
        for projet in assign3:
            results[eleve][4] = projet + 1
            print("Student %d gets Research Project %d" % (eleve + 1, projet + 1))

    return results


# Résolution complète du problème


def optimisation_recherche():
    # Paramètres : Lecture des données
    donnees = pandas.read_csv(open('VoeuxRecherche.csv'),
                              encoding='utf-8', quotechar='"', delimiter=';').values[:, 1:]

    # Paramètres : Regret associé aux cours ou projets
    regret_cours = [[[10000 for p in range(nb_projets[j])] for e in range(nb_eleves)] for j in range(nb_jours)]

    for jour in range(nb_jours):
        for eleve in range(nb_eleves):
            for poids in range(nb_projets[jour]):
                regret_cours[jour][eleve][donnees[eleve][int(sum(nb_projets[:jour]) + poids)] - 1] \
                    = poids ** 2  # ou regret de p si autre fct poids

    regret_projet = [[10000 for projet in range(sum(nb_projets))] for eleve in range(nb_eleves)]

    for eleve in range(nb_eleves):
        for poids in range(nb_voeux_PIR):
            regret_projet[eleve][donnees[eleve][int(sum(nb_projets) + poids)] - 1] = poids ** 2

    begin("assign")

    # Variables
    ouv_cours = [var('ouv_cours', P[jour]) for jour in range(nb_jours)]
    aff_cours = [var('aff_cours', ExP[jour]) for jour in range(nb_jours)]
    eff_cours = [var('eff_cours', P[jour]) for jour in range(nb_jours)]

    ouv_projet = var('ouvproj', PR)
    aff_projet = var('aff_proj', iprod(E, PR))
    eff_projet = var('effproj', PR)

    # Fonction objectif
    minimize(sum((sum(regret_cours[jour][eleve][projet] * aff_cours[jour][eleve, projet]
                      for eleve, projet in ExP[jour]))
                 for jour in range(nb_jours)) + sum(regret_projet[eleve][projet] * aff_projet[eleve, projet]
                                                    for eleve, projet in iprod(E, PR)))

    # Contraintes
    for eleve, jour in ExJ:
        sum(aff_cours[jour][eleve, projet] for projet in P[jour]) == 1
    for eleve in E:
        sum(aff_projet[eleve, projet] for projet in PR) == 1

    for jour in range(nb_jours):
        for projet in P[jour]:
            sum(aff_cours[jour][eleve, projet] for eleve in E) == eff_cours[jour][projet]
            sum(aff_projet[eleve, sum(nb_projets[:jour]) + projet] for eleve in E) == eff_projet[sum(nb_projets[:jour]) + projet]
            ouv_cours[jour][projet] * eff_min_cours(jour, projet) <= eff_cours[jour][projet]
            ouv_cours[jour][projet] * eff_max_cours(jour, projet) >= eff_cours[jour][projet]
            ouv_projet[int(sum(nb_projets[:jour]) + projet)] * eff_min_proj(jour, projet) <= eff_projet[int(sum(nb_projets[:jour]) + projet)]
            ouv_projet[int(sum(nb_projets[:jour]) + projet)] * eff_max_proj(jour, projet) <= eff_projet[int(sum(nb_projets[:jour]) + projet)]
        for eleve, projet in ExP[jour]:
            aff_projet[eleve, int(sum(nb_projets[:jour]) + projet)] <= aff_cours[jour][eleve, projet]

    # Résolution
    solve()

    # Ecriture des résultats
    results = affectation_recherche(aff_cours, aff_projet)
    resultats_recherche_xlsx(results)


# Fonction d'écriture des résultats


def resultats_recherche_xlsx(results):
    # Dans un fichier Excel

    # Create a workbook and add a worksheet.
    workbook = xlsxwriter.Workbook('ResultatsRecherche.xlsx')
    worksheet = workbook.add_worksheet()

    # Some data we want to write to the worksheet.
    expenses = ([nom_eleve(i + 1), results[i][0], results[i][1], results[i][2], results[i][3], results[i][4]]
                for i in range(nb_eleves))

    # Start from the first cell. Rows and columns are zero indexed.
    row = 0
    col = 0

    worksheet.write(row, col, "Elèves")
    worksheet.write(row, col + 1, "Jour 1")
    worksheet.write(row, col + 2, "Jour 2")
    worksheet.write(row, col + 3, "Jour 3")
    worksheet.write(row, col + 4, "Jour 4")
    worksheet.write(row, col + 5, "PIR")
    row += 1

    # Iterate over the data and write it out row by row.
    for i, j, k, l, m, n in expenses:
        worksheet.write(row, col, i)
        worksheet.write(row, col + 1, nom_proj_rech(1, j))
        worksheet.write(row, col + 2, nom_proj_rech(2, k))
        worksheet.write(row, col + 3, nom_proj_rech(3, l))
        worksheet.write(row, col + 4, nom_proj_rech(4, m))
        worksheet.write(row, col + 5, nom_proj_rech_2(n))
        row += 1

    workbook.close()


if __name__ == '__main__':
    optimisation_recherche()
