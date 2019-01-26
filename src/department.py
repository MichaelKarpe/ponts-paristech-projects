from config import (
    DEPARTMENT_RESULTS_FILE, DEPARTMENT_STAFFREQUIRED_FILE, DEPARTMENT_WISHLISTS_FILE, PARAMETERS_FILE, STUDENTS_FILE
)
from model import (
    BaseAssignmentSolverComponent, BaseParametersParserComponent, BaseResultsInterpreterComponent,
    BaseResultsSaverComponent, BaseStaffRequiredParserComponent, BaseWishlistsParserComponent
)
from pymprog import iprod, model
from utils import read_csv

import xlsxwriter as xlsx


class ParametersParser(BaseParametersParserComponent):
    """Parses parameters of the assignment problem."""

    def __init__(self, parameters_file):
        self.parameters = read_csv(parameters_file).values[:, 1:]
        self.nb_students = int(self.parameters[0, 0])
        self.nb_dept_projects = int(self.parameters[1, 0])


class StaffRequiredParser(BaseStaffRequiredParserComponent):
    """Parses staff required for all tasks of the assignment problem."""

    def dept_min_staff(self, num_proj):
        return self.staffrequired[num_proj][0]

    def dept_max_staff(self, num_proj):
        return self.staffrequired[num_proj][1]


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
        self.P = range(self.parameters.nb_dept_projects)
        self.ExP = iprod(self.E, self.P)

        self.cost_matrix = self.cost_function()
        self.model, self.ouv_dep, self.aff_dep, self.eff_dep = self.solve()

    def cost_function(self):
        return [[
            (self.wishlists.wishes[eleve][projet] - 1) ** 2
            for projet in range(self.parameters.nb_dept_projects)
        ] for eleve in range(self.parameters.nb_students)]

    def solve(self):
        assignment_model = model("assign")

        # Variables
        ouv_dep = assignment_model.var('ouv_dep', self.P)
        aff_dep = assignment_model.var('aff_dep', self.ExP)
        eff_dep = assignment_model.var('eff_dep', self.P)

        # Objective function
        assignment_model.min(sum(
            self.cost_matrix[eleve][projet] * aff_dep[eleve, projet]
            for eleve, projet in self.ExP
        ))

        # Constraints
        for eleve in self.E:
            sum(aff_dep[eleve, projet] for projet in self.P) == 1
        for projet in self.P:
            sum(aff_dep[eleve, projet] for eleve in self.E) == eff_dep[projet]
            self.staffrequired.dept_min_staff(projet) <= eff_dep[projet]
            self.staffrequired.dept_max_staff(projet) >= eff_dep[projet]

        # Solve
        assignment_model.solve()

        return assignment_model, ouv_dep, aff_dep, eff_dep


class ResultsInterpreter(BaseResultsInterpreterComponent):
    """Saves assignment results in XLSX format."""

    def interpreter(self):
        print("Total Cost = %g" % self.solver.model.vobj())

        results = [0 for eleve in range(self.parameters.nb_students)]
        assign = [
            (eleve, projet) for eleve in self.solver.E for projet in self.solver.P
            if self.solver.aff_dep[eleve, projet].primal > 0.5
        ]
        for eleve, projet in assign:
            results[eleve] = projet + 1
            print("Student %d gets Project %d" % (eleve + 1, projet + 1))

        return results


class ResultsSaver(BaseResultsSaverComponent):
    """Saves assignment results in XLSX format."""

    def get_student_name(self, ind_eleve):
        return self.student_names[ind_eleve - 1][0]

    def get_dept_proj_name(self, num_proj):
        return self.staffrequired.staffrequired[num_proj - 1][2]

    def save_to_xlsx(self):
        # Create a workbook and add a worksheet.
        workbook = xlsx.Workbook(self.results_file)
        worksheet = workbook.add_worksheet()

        # Some data we want to write to the worksheet.
        expenses = (
            [self.get_student_name(i + 1), self.results[i]]
            for i in range(self.parameters.nb_students)
        )

        # Start from the first cell. Rows and columns are zero indexed.
        row = 0
        col = 0

        worksheet.write(row, col, "Elèves")
        worksheet.write(row, col + 1, "Projet de département")
        row += 1

        # Iterate over the data and write it out row by row.
        for i, j in expenses:
            worksheet.write(row, col, i)
            worksheet.write(row, col + 1, self.get_dept_proj_name(j))
            row += 1

        workbook.close()


if __name__ == '__main__':
    parameters_parser = ParametersParser(PARAMETERS_FILE)
    staffrequired_parser = StaffRequiredParser(DEPARTMENT_STAFFREQUIRED_FILE)
    wishlists_parser = WishlistsParser(DEPARTMENT_WISHLISTS_FILE)
    assignment_solver = AssignmentSolver(parameters_parser, staffrequired_parser, wishlists_parser)
    interpreter = ResultsInterpreter(parameters_parser, assignment_solver)
    results_saver = ResultsSaver(STUDENTS_FILE, parameters_parser, staffrequired_parser, interpreter, DEPARTMENT_RESULTS_FILE)
