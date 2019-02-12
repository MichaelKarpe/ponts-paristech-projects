import pandas as pd


def read_csv(path_to_file):
    return pd.read_csv(path_to_file, encoding='utf-8', quotechar='"', delimiter=';')
