import numpy as np
import matplotlib.pyplot as plt 
import seaborn as sns
sns.set_style('white')
import warnings
warnings.filterwarnings("ignore")

# import data
fname = "results_201.dat" #change this line to switch between q_i[3] = 2.00 and 2.01
results = np.loadtxt(open(fname), delimiter = ' ')

# label data
time = np.asarray([var[0] for var in results])
theta_1 = np.asarray([var[1] for var in results]) 
theta_1 = np.asarray([var[2] for var in results])
p_1 = np.asarray([var[3] for var in results])
p_2 = np.asarray([var[4] for var in results])
x_1 = np.asarray([var[5] for var in results]) 
y_1 = np.asarray([var[6] for var in results]) 
x_2 = np.asarray([var[7] for var in results])
y_2 = np.asarray([var[8] for var in results])
energy = np.asarray([var[9] for var in results])

# x_1 vs y_1
fig = plt.figure()
plt.title("x_1 vs y_1")
plt.xlabel("x_1")
plt.ylabel("y_1")
plt.plot(x_1, y_1, c = 'red')
plt.savefig("x1_vs_y1_201.pdf") #change this plot title between 2.00 and 2.01
plt.show()

# p_1 vs p_2
fig = plt.figure()
plt.title("p_1 vs p_2")
plt.xlabel("p_1")
plt.ylabel("p_2")
plt.plot(p_1, p_2, c = 'red')
plt.savefig("p1_vs_p2_201.pdf") #change this plot title between 2.00 and 2.01
plt.show()

# x_2 vs y_2 
fig = plt.figure()
plt.title("x_2 vs y_2")
plt.xlabel("x_2")
plt.ylabel("y_2")
plt.plot(x_2, y_2, c = 'red')
plt.savefig("x2_vs_y2_201.pdf") #change this plot title between 2.00 and 2.01
plt.show()

# total energy vs time
fig = plt.figure()
plt.title("Total energy vs time")
plt.xlabel("Time")
plt.ylabel("Total Energy")
avg = np.average(energy) #to define range of graph
plt.ylim([avg - 0.1, avg + 0.1])
plt.plot(time, energy, c = 'red')
plt.savefig("ene_vs_t_201.pdf") #change this plot title between 2.00 and 2.01
plt.show(block = True)

###