import numpy as np

A = np.random.rand(2,5)         #create 2x5 matrix with random float ranging from 0 to 1
print("Rank of A: ", np.linalg.matrix_rank(A)) #Prints the rank of A using built in numpy function

B = np.dot(A,(np.matrix.transpose(A)))  #Creates matrix B from the dot product between A and A transposed
print("Shape of B: ", np.shape(B))
print("Rank of B: ", np.linalg.matrix_rank(B))

C = np.dot(np.matrix.transpose(A),A)    #creates matrix C in the same way matrix B was created
print("Shape of C: ", np.shape(C))
print("Rank of C: ", np.linalg.matrix_rank(C))