test()

mat.in(A,3,3):
1.2 2.3 3.4 
4.5 1.32 2.2
3.12 2.65 9.5

mat.in((A|E),3,6)
1.2 2.3 3.4 1 0 0
4.5 1.32 2.2 0 1 0
3.12 2.65 9.5 0 0 1
mat.eche((A|E),(E|A^-1))

mat.in(B,3,3): 
2.2 3.3 5.3
5.5 1 3
3 0.5 9

vct.in(v.a,3,1): 3.1415 2.71842 4.33
vct.in(v.b,3,1): 3.1415 2.718142  1.22

mat.add(A,B,A+B)
mat.multi(A,A+B,A*(A+B))
mat.inv(A*(A+B),[A*(A+B)]^-1)
mat.det(A*(A+B))
mat.det([A*(A+B)]^-1)
mat.multi(A*(A+B),v.a,A*(A+B)->v.a)
mat.multi([A*(A+B)]^-1,A*(A+B)->v.a,v.GOOD)

vct.mag(A*(A+B)->v.a) val.del(Mag(A*(A+B)->v.a)) 
vct.mag(v.b) val.del(Mag(v.b))

vct.angle(A*(A+B)->v.a,v.b,theta(T->v.a|v.b))
vct.n0(A*(A+B)->v.a,v.b,v.n0Cross_(v.a|v.b))
vct.cross(A*(A+B)->v.a,v.b,v.Cross_(v.a|v.b))
vct.minus(v.GOOD,v.a,v.delta(v.GOOD-v.a))
vct.approx(v.delta(v.GOOD-v.a),r%v.delta(v.GOOD-v.a))

file.del(matrix) file.del(matrixstream) file.del(value)

mat.in(A,5,5):
1 2 2 1 2
5 6 7 8 3
9 3 0 5 3
7 2 1 4 6
3 0 8 2 4
mat.inv(A,A^-1)

mat.in(B,5,5):
1.37 2.7 2 1 2
5 6.7 7.7 8.7 3
9.7 3.7 0 5 3
7 2 1.7 4 6.7
3.7 0.7 8 2 4.7
mat.tran(B,B^T)

mat.multi(A^-1,B^T,C)
mat.multi(A^-1,A,I[5])
mat.approx(I[5],r%I[5])

mat.det(A) mat.det(A^-1)
mat.det(B) mat.det(B^T)

mat.det(I[5]) 
mat.det(r%I[5])

mat.in((BIG|E),10,20):
2 3 5 7 11 13 17 19 23 29 1 0 0 0 0 0 0 0 0 0
31 37 41 43 47 53 59 61 67 71 0 1 0 0 0 0 0 0 0 0
73 79 83 89 97 101 103 107 109 113 0 0 1 0 0 0 0 0 0 0
127 131 137 139 149 151 157 163 167 173 0 0 0 1 0 0 0 0 0 0
179 181 191 193 197 199 211 223 227 229 0 0 0 0 1 0 0 0 0 0
233 239 241 251 257 263 269 271 277 281 0 0 0 0 0 1 0 0 0 0
283 293 307 311 313 317 331 337 347 349 0 0 0 0 0 0 1 0 0 0
353 359 367 373 379 383 389 397 401 409 0 0 0 0 0 0 0 1 0 0
419 421 431 433 439 443 449 457 461 463 0 0 0 0 0 0 0 0 1 0
467 479 487 491 499 503 509 521 523 541 0 0 0 0 0 0 0 0 0 1
mat.eche((BIG|E),(BIG^-1|E))

file.del(value) file.del(matrix) file.del(matrixstream)

quit()

