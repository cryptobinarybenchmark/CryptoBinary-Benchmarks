import numpy as np
# Input: number of features F
# numpy matrix X, with n rows (samples), d columns (features)
# numpy vector mu, with d rows, 1 column
# numpy matrix Z, with d rows, F columns
# Output: numpy matrix P, with n rows, F columns
import pcalearn
np.set_printoptions(precision=4)


def run(X,mu,Z):
    # Your code goes here
    X = np.copy(X)
    for i in range(np.shape(X)[0]):
        for j in range(np.shape(X)[1]):
            X[i][j] = X[i][j] - mu[j]
    P = np.zeros((np.shape(X)[0],np.shape(Z)[1]))
    P = np.dot(X,Z)
    print (P)
    return P

n = 30
d = 25
F = 20
X = np.random.rand(n, d)
mu = np.random.rand(d, 1)
Z = np.random.rand(d, F)

run(X,mu,Z)
pcalearn.run(F, X)
