import numpy as np

M = np.arange(2, 27)
print(M)
M = M.reshape(5, 5)
print(M)
M[:, 0] = [0, 0, 0, 0, 0]
print(M)
M = M@M
print(M)
v = np.sqrt(sum(M[0]*M[0]))
print(v)
