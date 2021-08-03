import numpy as np

p = [[1,0],[0,1],[1,1]]
q = [[1,2],[3,4]]

ans = np.dot(p,q)
ans2 = np.matmul(p,q)
print('Ans:',ans)
print('Ans2: ',ans2)