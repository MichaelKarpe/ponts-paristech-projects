# Automatic and optimal course allocation with wishlists from students

This project has been realized in February and March 2017, during my first year at École des Ponts ParisTech. It has been organized to automate and to boost optimization of course allocation for first year students, which was done manually up to 2017. The first use of our algorithms on real wishlists of first year students in Fall 2017 has been a great success, and almost all students were satisfied with the results obtained.

This project used first GLPK for the optimization part and C++ for the software part, but I reimplented it in Python in August 2017, using _pymprog_, for faster results.

The aim of the project was to solve two optimization problems:
- _optimisation\_departement_ was a simple problem of course allocation of students in some projects at the same time, considering admission limits
- _optimisation\_recherche_ was a more complex course allocation, as it was the global optimization at the same time of four problems like _optimisation\_departement_, plus a project allocation depending on the results of the four _optimisation\_departement_ problems mentioned.

The results obtained have been very satisfactory. Considering wishlists with seven wishes:
- 79% of course allocations corresponded to first wishes from students
- 20% of course allocations corresponded to second wishes from students
- Only 1% of course allocations corresponded to third wishes from students

The main part of the final report of the project is available in the `doc` file (in French only).


## Index

1.  [Dependencies](#dependencies)
1.  [Installation](#installation)
1.  [Launch App](#launch-app)

## Dependencies

- [anaconda](https://www.anaconda.com/distribution/)

## Installation

Install a conda environment:

```bash
conda create -n course-allocation anaconda python=3.7.2
conda activate course-allocation
pip install -r ./requirements.txt
```

_N.B.:_ The `requirements.txt` file has been generated with the following command lines:

```bash
conda create -n course-allocation anaconda python=3.7.2
conda activate course-allocation
pip install black pandas pymprog xlsxwriter
pip freeze > requirements.txt
```

## Launch App

Set the correct `PATH_TO_FOLDER` in the `src/config.py` file and then launch the following commands:

```bash
conda activate course-allocation
python src/department.py
python src/research.py
```