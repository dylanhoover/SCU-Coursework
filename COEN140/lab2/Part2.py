import numpy as np

X = np.random.randint(0,10,(3,5))       #creates matrix X (3x5), with random ints ranging from 0 to 10
A = np.dot(X,np.matrix.transpose(X))    #creates matrix A by the dot product between X and X transpose
print("Shape of A: ",np.shape(A))

w = np.random.randint(0,10,(3,1))       #create matrix W (3x1) with random ints ranging from 0 to 10
print("Shape of Aw: ",np.shape(np.matmul(A,w)))     #the shape of A dot product w

print("Shape of w^TA: ", np.shape((np.dot(np.matrix.transpose(w),A))))  #the shape of w transposed dot product A

wTA = np.dot(np.matrix.transpose(w),A)      #dot prodcut of w transpose and A
print("Shape of w^TAw: ", np.shape(np.dot(wTA,w))) #print the shape of the dot product of wTransponse A w

print("Is XX^T symmetric: ",(np.transpose(A) == A).all())   #checks if symmetric by commparing the transposed matrix to the original


Ainv = np.linalg.inv(A)         #inverse of A
print("Ainv*A: ",np.dot(Ainv,A))
print("A*Ainv: ", np.dot(A,Ainv))