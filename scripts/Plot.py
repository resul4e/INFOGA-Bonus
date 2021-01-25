import matplotlib.pyplot as plt
import csv

points = []
y = []
with open('../build/Noutput.csv', newline='') as csvfile:
    spamreader = csv.reader(csvfile, delimiter=' ', quotechar='|')
    for row in spamreader:
        split = row[0].split(',')
        points.append(float(split[0]))
        y.append(float(split[2]))


plt.plot(points, y)
plt.xlabel('# of points in set')
plt.ylabel('time(μs)')
plt.show()