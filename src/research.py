from config import (
    PARAMETERS_FILE,
    RESEARCH_RESULTS_FILE,
    RESEARCH_STAFFREQUIRED_FILE,
    RESEARCH_WISHLISTS_FILE,
    STUDENTS_FILE,
)
from model import (
    BaseAssignmentSolverComponent,
    BaseParametersParserComponent,
    BaseResultsInterpreterComponent,
    BaseResultsSaverComponent,
    BaseStaffRequiredParserComponent,
    BaseWishlistsParserComponent,
)
from pymprog import iprod, model
from utils import read_csv

import xlsxwriter as xlsx


class ParametersParser(BaseParametersParserComponent):
    """Parses parameters of the assignment problem."""

    def __init__(self, parameters_file):
        self.parameters = read_csv(parameters_file).values[:, 1:]
        self.nb_students = int(self.parameters[0, 0])
        self.nb_days = 4
        self.nb_courses = [int(self.parameters[i + 2, 0]) for i in range(self.nb_days)]
        self.nb_wishes_PIR = int(self.parameters[6, 0])


class StaffRequiredParser(BaseStaffRequiredParserComponent):
    """Parses staff required for all tasks of the assignment problem."""

    def __init__(self, staffrequired_file, parameters_parser):
        self.staffrequired = read_csv(staffrequired_file).values[:, 1:]
        self.parameters = parameters_parser

    def course_min_staff(self, jour, projet):
        return self.staffrequired[int(sum(self.parameters.nb_courses[: (jour - 1)]) + projet - 1)][0]

    def course_max_staff(self, jour, projet):
        return self.staffrequired[int(sum(self.parameters.nb_courses[: (jour - 1)]) + projet - 1)][1]

    def project_min_staff(self, jour, projet):
        return self.staffrequired[int(sum(self.parameters.nb_courses[: (jour - 1)]) + projet - 1)][2]

    def project_max_staff(self, jour, projet):
        return self.staffrequired[int(sum(self.parameters.nb_courses[: (jour - 1)]) + projet - 1)][3]


class WishlistsParser(BaseWishlistsParserComponent):
    """Parses wishlists from students."""

    pass


class AssignmentSolver(BaseAssignmentSolverComponent):
    """Parses wishlists from students."""

    def __init__(self, parameters_parser, staffrequired_parser, wishlists_parser):
        self.parameters = parameters_parser
        self.staffrequired = staffrequired_parser
        self.wishlists = wishlists_parser

        self.E = range(self.parameters.nb_students)
        self.J = range(self.parameters.nb_days)
        self.C = [range(self.parameters.nb_courses[k]) for k in range(self.parameters.nb_days)]
        self.PR = range(sum(self.parameters.nb_courses))

        self.ExC = [iprod(self.E, self.C[j]) for j in range(self.parameters.nb_days)]
        self.ExJ = iprod(self.E, self.J)

        self.cost_matrix_courses = self.cost_function_courses()
        self.cost_matrix_projects = self.cost_function_projects()
        (
            self.model,
            self.ouv_cours,
            self.aff_cours,
            self.eff_cours,
            self.ouv_projet,
            self.aff_projet,
            self.eff_projet,
        ) = self.solve()

    def cost_function_courses(self):
        cost_matrix_courses = [
            [[10000 for p in range(self.parameters.nb_courses[j])] for e in range(self.parameters.nb_students)]
            for j in range(self.parameters.nb_days)
        ]

        for jour in range(self.parameters.nb_days):
            for eleve in range(self.parameters.nb_students):
                for poids in range(self.parameters.nb_courses[jour]):
                    cost_matrix_courses[jour][eleve][
                        self.wishlists.wishes[eleve][int(sum(self.parameters.nb_courses[:jour]) + poids)] - 1
                    ] = (poids ** 2)

        return cost_matrix_courses

    def cost_function_projects(self):
        cost_matrix_projects = [
            [10000 for projet in range(sum(self.parameters.nb_courses))] for eleve in range(self.parameters.nb_students)
        ]

        for eleve in range(self.parameters.nb_students):
            for poids in range(self.parameters.nb_wishes_PIR):
                cost_matrix_projects[eleve][
                    self.wishlists.wishes[eleve][int(sum(self.parameters.nb_courses) + poids)] - 1
                ] = (poids ** 2)

        return cost_matrix_projects

    def solve(self):
        assignment_model = model("assign")

        # Variables
        ouv_cours = [assignment_model.var("ouv_cours", self.C[jour]) for jour in range(self.parameters.nb_days)]
        aff_cours = [assignment_model.var("aff_cours", self.ExC[jour]) for jour in range(self.parameters.nb_days)]
        eff_cours = [assignment_model.var("eff_cours", self.C[jour]) for jour in range(self.parameters.nb_days)]

        ouv_projet = assignment_model.var("ouvproj", self.PR)
        aff_projet = assignment_model.var("aff_proj", iprod(self.E, self.PR))
        eff_projet = assignment_model.var("effproj", self.PR)

        # Objective function
        assignment_model.min(
            sum(
                sum(
                    self.cost_matrix_courses[jour][eleve][projet] * aff_cours[jour][eleve, projet]
                    for eleve, projet in self.ExC[jour]
                )
                for jour in range(self.parameters.nb_days)
            )
            + sum(
                self.cost_matrix_projects[eleve][projet] * aff_projet[eleve, projet]
                for eleve, projet in iprod(self.E, self.PR)
            )
        )

        # Constraints
        for eleve, jour in self.ExJ:
            sum(aff_cours[jour][eleve, projet] for projet in self.C[jour]) == 1
        for eleve in self.E:
            sum(aff_projet[eleve, projet] for projet in self.PR) == 1

        for jour in range(self.parameters.nb_days):
            for projet in self.C[jour]:
                sum(aff_cours[jour][eleve, projet] for eleve in self.E) == eff_cours[jour][projet]
                sum(
                    aff_projet[eleve, sum(self.parameters.nb_courses[:jour]) + projet] for eleve in self.E
                ) == eff_projet[sum(self.parameters.nb_courses[:jour]) + projet]
                ouv_cours[jour][projet] * self.staffrequired.course_min_staff(jour, projet) <= eff_cours[jour][projet]
                ouv_cours[jour][projet] * self.staffrequired.course_max_staff(jour, projet) >= eff_cours[jour][projet]
                ouv_projet[int(sum(self.parameters.nb_courses[:jour]) + projet)] * self.staffrequired.project_min_staff(
                    jour, projet
                ) <= eff_projet[int(sum(self.parameters.nb_courses[:jour]) + projet)]
                ouv_projet[int(sum(self.parameters.nb_courses[:jour]) + projet)] * self.staffrequired.project_max_staff(
                    jour, projet
                ) <= eff_projet[int(sum(self.parameters.nb_courses[:jour]) + projet)]
            for eleve, projet in self.ExC[jour]:
                aff_projet[eleve, int(sum(self.parameters.nb_courses[:jour]) + projet)] <= aff_cours[jour][
                    eleve, projet
                ]

        # Solve
        assignment_model.solve()

        return assignment_model, ouv_cours, aff_cours, eff_cours, ouv_projet, aff_projet, eff_projet


class ResultsInterpreter(BaseResultsInterpreterComponent):
    """Saves assignment results in XLSX format."""

    def interpreter(self):
        print("Total Cost = %g" % self.solver.model.vobj())

        results = [[0 for projet in range(5)] for eleve in range(self.parameters.nb_students)]

        # Courses
        for jour in range(self.parameters.nb_days):
            assign2 = [
                (eleve, projet)
                for eleve in self.solver.E
                for projet in self.solver.C[jour]
                if self.solver.aff_cours[jour][eleve, projet].primal > 0.5
            ]
            for eleve, projet in assign2:
                results[eleve][jour] = projet + 1
                print("Student %d gets on Day %d Course %d" % (eleve + 1, jour + 1, projet + 1))

        # Research projects
        for eleve in self.solver.E:
            assign3 = [projet for projet in self.solver.PR if self.solver.aff_projet[eleve, projet].primal > 0.5]
            for projet in assign3:
                results[eleve][4] = projet + 1
                print("Student %d gets Research Project %d" % (eleve + 1, projet + 1))

        return results


class ResultsSaver(BaseResultsSaverComponent):
    """Saves assignment results in XLSX format."""

    def get_student_name(self, ind_eleve):
        return self.student_names[ind_eleve - 1][0]

    def get_course_name(self, jour, projet):
        return self.staffrequired.staffrequired[int(sum(self.parameters.nb_courses[: (jour - 1)]) + projet - 1)][4]

    def get_research_project_name(self, projet):
        return self.staffrequired.staffrequired[projet - 1][5]

    def save_to_xlsx(self):
        # Create a workbook and add a worksheet.
        workbook = xlsx.Workbook(self.results_file)
        worksheet = workbook.add_worksheet()

        # Some data we want to write to the worksheet.
        expenses = (
            [self.get_student_name(i + 1)] + [self.results[i][j] for j in range(5)]
            for i in range(self.parameters.nb_students)
        )

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
            worksheet.write(row, col + 1, self.get_course_name(1, j))
            worksheet.write(row, col + 2, self.get_course_name(2, k))
            worksheet.write(row, col + 3, self.get_course_name(3, l))
            worksheet.write(row, col + 4, self.get_course_name(4, m))
            worksheet.write(row, col + 5, self.get_research_project_name(n))
            row += 1

        workbook.close()


if __name__ == "__main__":
    parameters_parser = ParametersParser(PARAMETERS_FILE)
    staffrequired_parser = StaffRequiredParser(RESEARCH_STAFFREQUIRED_FILE, parameters_parser)
    wishlists_parser = WishlistsParser(RESEARCH_WISHLISTS_FILE)
    assignment_solver = AssignmentSolver(parameters_parser, staffrequired_parser, wishlists_parser)
    interpreter = ResultsInterpreter(parameters_parser, assignment_solver)
    results_saver = ResultsSaver(
        STUDENTS_FILE, parameters_parser, staffrequired_parser, interpreter, RESEARCH_RESULTS_FILE
    )
