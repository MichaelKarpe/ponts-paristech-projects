from utils import read_csv

import abc


class BaseParametersParserComponent(metaclass=abc.ABCMeta):
    """Defines an Abstract Base Class for ParametersParser classes."""

    def __init__(self, parameters_file):
        self.parameters = read_csv(parameters_file).values[:, 1:]


class BaseStaffRequiredParserComponent(metaclass=abc.ABCMeta):
    """Defines an Abstract Base Class for StaffRequiredParser classes."""

    def __init__(self, staffrequired_file):
        self.staffrequired = read_csv(staffrequired_file).values[:, 1:]


class BaseWishlistsParserComponent(metaclass=abc.ABCMeta):
    """Defines an Abstract Base Class for WishlistsParser classes."""

    def __init__(self, wishlists_file):
        self.wishes = read_csv(wishlists_file).values[:, 1:]


class BaseAssignmentSolverComponent(metaclass=abc.ABCMeta):
    """Defines an Abstract Base Class for AssignmentSolver classes."""

    @abc.abstractmethod
    def __init__(self, parameters_parser, staffrequired_parser, wishlists_parser):
        pass

    @abc.abstractmethod
    def solve(self):
        pass


class BaseResultsInterpreterComponent(metaclass=abc.ABCMeta):
    """Defines an Abstract Base Class for ResultsInterpreter classes."""

    def __init__(self, parameters_parser, assignment_solver):
        self.parameters = parameters_parser
        self.solver = assignment_solver
        self.results = self.interpreter()

    @abc.abstractmethod
    def interpreter(self):
        pass


class BaseResultsSaverComponent(metaclass=abc.ABCMeta):
    """Defines an Abstract Base Class for ResultsSaver classes."""

    def __init__(self, students_file, parameters_parser, staffrequired_parser, interpreter, results_file):
        self.student_names = read_csv(students_file).values[:, 1:]
        self.results_file = results_file

        self.parameters = parameters_parser
        self.staffrequired = staffrequired_parser
        self.results = interpreter.results

        self.save_to_xlsx()

    @abc.abstractmethod
    def save_to_xlsx(self):
        pass
