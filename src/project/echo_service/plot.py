import numpy as np
import argparse

import matplotlib.pyplot as plt

parser = argparse.ArgumentParser()
parser.add_argument(
    "filename", nargs=1, type=str, help="name of file that contains stats")
args = parser.parse_args()

data = np.genfromtxt(args.filename[0], delimiter=",")
print(data)
plt.plot(data[:, 0], data[:, 1], label="Default blocking server")
plt.plot(data[:, 0], data[:, 2], label="Non blocking server")
plt.xlabel("Number of test clients")
plt.ylabel("Clients per second")
plt.legend()
plt.show()
