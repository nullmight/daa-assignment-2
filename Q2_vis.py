import matplotlib.pyplot as plt

f = open('output.txt')
n = int(f.readline())
x_arr = []
y_arr = []
for i in range(n):
    x, y = [float(val) for val in f.readline().split(' ')]
    x_arr.append(x)
    y_arr.append(y)

fig, axes = plt.subplots(nrows=1, ncols=2, sharex=True, sharey=True)

axes[0].scatter(x_arr, y_arr, marker="o")
axes[0].set_xlabel('Original Points', labelpad=5)
axes[0].set_aspect('square', adjustable='box')

axes[1].scatter(x_arr, y_arr, marker="o")
axes[1].set_aspect('square', adjustable='box')

m = int(f.readline())
for i in range(m):
    x1, x2, a, b = [float(val) for val in f.readline().split(' ')]
    plt.plot([x1, x2], [a * x1 + b, a * x2 + b], '-')
axes[1].set_xlabel('Segmented least squares', labelpad=5)

# Add separate colourbar axes
# cbar_ax = fig.add_axes([0.85, 0.15])

# Autoscale none
# fig.colorbar(axes[0], cax=cbar_ax)

plt.show()