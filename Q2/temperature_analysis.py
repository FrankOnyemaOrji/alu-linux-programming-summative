import pandas as pd
import numpy as np
from scipy import stats

def analyze_temperatures(filename):
    data = pd.read_csv(filename)
    temperatures = data['Temperature(K)']

    mean_temp = np.mean(temperatures)
    mode_temp = stats.mode(temperatures)[0][0]
    stddev_temp = np.std(temperatures)

    return mean_temp, mode_temp, stddev_temp
