import numpy as np

x = np.random.rand(5,1)

xt = np.dot(x, np.transpose(x))

print(xt)

print(np.linalg.matrix_rank(xt))