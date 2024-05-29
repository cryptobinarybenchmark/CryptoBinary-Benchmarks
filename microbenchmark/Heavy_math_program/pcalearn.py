import numpy as np
import numpy.linalg as la
# Input: number of features F
# numpy matrix X, with n rows (samples), d columns (features)
# Output: numpy vector mu, with d rows, 1 column
# numpy matrix Z, with d rows, F columns

def run(F,X):
    X = np.copy(X)
    mu = np.zeros((np.shape(X)[1],1))
    Z = np.zeros((np.shape(X)[1],F))
    # Your code goes here
    for i in range(np.shape(X)[1]):
        for j in range(np.shape(X)[0]):
            mu[i][0] = X[j][i] + mu[i][0]
        mu[i][0] = mu[i][0]/np.shape(X)[0]
    for n in range(np.shape(X)[0]):
        for m in range(np.shape(X)[1]):
            X[n][m] = X[n][m] - mu[m][0]
    U,s,Vt = la.svd(X,False)
    g = np.zeros(F)
    for i in range(F):
        g[i] = s[i]
    for i in range(F):
        if g[i] > 0:
            g[i] = 1/g[i]
    W = np.zeros((F,np.shape(X)[1]))
    for i in range(F):
        for j in range(np.shape(X)[1]):
            W[i][j] = Vt[i][j]
    Z = np.dot(W.T,np.diag(g))
    print (mu)
    print (Z)
    return (mu, Z)



