matrix.In(Zero,5,5):
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0

matrix.In(A,5,5):
13.6 23 3.3 4.3 2
6.3 7.3 8.3 9.3 1.7
1.1 12.3 13 143 1.8
1.63 1.73 1.8 1.93 2.26
21.3 2.23 2.3 24 2

matrix.In(B,5,5):
13.6 23 3.3 4.3 2.4
6.3 7.3 8.3 9.7 1.7
1.1 12.3 16 14.3 1.8
16.3 17.3 18 1.93 2.2
1.5 12.3 1.3 14.7 1.8

matrix.Tran(B,B^T)
matrix.Add(A,B,(A+B))
matrix.Multi(B^T,(A+B),(A+B)*(B^T))
matrix.Inv((A+B)*(B^T),((A+B)*(B^T))^-1)
matrix.Multi((A+B)*(B^T),((A+B)*(B^T))^-1,I)
matrix.Multi((A+B),B,C)
matrix.Inv(C,C^-1)
matrix.Multi(C^-1,((A+B)*(B^T))^-1,D)
matrix.Multi(I,D,Answer)
matrix.Out(Answer)
matrix.Add(Answer,Zero,M)

matrix.In(vector.a,5,1):
1.2 2.3 3.4 4.5 5.6

matrix.Multi(M,vector.a,M->vector.a)
matrix.Out(M->vector.a)

matrix.In(vector.test,5,1):
1.3 2.2 3.7 9.5 5.7

matrix.Tran(vector.a,a^T)
matrix.Multi(a^T,vector.test,RESULT)

matrix.Del(Zero)
matrix.Del(A)
matrix.Del(B)
matrix.Del(B^T)
matrix.Del((A+B))
matrix.Del((A+B)*(B^T))
matrix.Del(((A+B)*(B^T))^-1)
matrix.Del(I)
matrix.Del(C)
matrix.Del(C^-1)
matrix.Del(D)
matrix.Del(Answer)
matrix.Del(vector.a)
matrix.Del(M)
value.Del(RESULT)

matrix.In(A,2,2):
1 2 3 4

exit()
