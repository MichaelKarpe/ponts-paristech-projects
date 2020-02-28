# Perfect trajectory prediction in billiards

This project has been realized from June 2015 to June 2016, during the end of my first year and my second year in _Classe Préparatoire_, for an exam called "Personal Initiative Workshop" _(Travail d'Initiative Personnelle Encadré - TIPE)_.

As I had at this time very few knowledge in Python, I have totally remade the code in June and July 2018 to make it readable for anyone. This has been possible thanks to knowledge developed during my second year at *École des Ponts ParisTech* in _Applied Mathematics and Computer Science_, particularly thanks to the course _Software design and development_ from Xavier Clerc.

Some documentation written in 2016 _(in French only)_ is available to understand the physical and geometric approaches used to develop a code which is able to compute perfect trajectories to win at billiard (under some conditions...)!

## Index

1.  [Dependencies](#dependencies)
1.  [Installation](#installation)
1.  [Launch App](#launch-app)

## Dependencies

- [anaconda](https://www.anaconda.com/distribution/)

## Installation

Install a conda environment:

```bash
conda create -n billiard anaconda python=3.7.2
conda activate billiard
pip install -r ./requirements.txt
```

_N.B.:_ The `requirements.txt` file has been generated with the following command lines:

```bash
conda create -n billiard anaconda python=3.7.2
conda activate billiard
pip install matplotlib numpy
pip freeze > requirements.txt
```

## Launch App

```bash
conda activate billiard
python main.py
```
