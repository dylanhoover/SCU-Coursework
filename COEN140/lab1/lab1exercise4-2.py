import numpy as np

v = np.arange(7)

x = np.matrix('1,2; 3,4')

print(np.linalg.norm(v))
print(np.linalg.norm(x))

