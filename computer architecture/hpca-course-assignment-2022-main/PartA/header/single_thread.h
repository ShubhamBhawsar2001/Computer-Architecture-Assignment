
#include<bits/stdc++.h>
typedef int vec __attribute__ (( vector_size(32) ));
vec* alloc(int n) {
    vec* ptr = (vec*) aligned_alloc(32, 32 * n);
    memset(ptr, 0, 32 * n);
    return ptr;
}
void print(int *c){
for(int i=0;i<100;i++){
  c[i];
}
}
void singleThread(int n, int *A, int *B, int *c)
{



int *_a=(int *)malloc(n*(n/2)*sizeof(int));
int *_b=(int *)malloc(n*(n/2)*sizeof(int));

//Transpose B
    int *mat=(int *)malloc(n*n*sizeof(int));
    for(int i=0 ; i<n ; i++){
        for(int j=0 ; j<n ; j++){
            mat[i * n + j] = B[j * n + i];
        }
    }


for (int i = 0; i < n/2; i++)

{
for(int k=0;k<n;k++){
  _a[i*n+k]=A[2*n*i+k]+A[2*n*i+n+k];
  _b[i*n+k]=mat[2*n*i+k]+mat[2*n*i+n+k];
}


}


    int nB = (n + 7) / 8; 

    vec *a = alloc(n/2 * nB);
    vec *b = alloc(n/2 * nB);

    

    // move both matrices to the aligned region
    for (int i = 0; i < n/2; i++) {
        for (int j = 0; j < n; j++) {
            a[i * nB + j / 8][j % 8] = _a[i * n + j];
            b[i * nB + j / 8][j % 8] = _b[i * n + j];
           
        }
    }
    
    int j=0;
for(int i=0;i<100;i++){
 
  j+=i;

}


    for (int i = 0; i < n/2; i++) {
        for (int j = 0; j < n/2; j++) {
            vec s{}; 
                   
                   for(int i=0;i<n/2;i++){
                    s[i]=0;
                   }
            // vertical summation
            for (int k = 0; k < nB; k++)
                s += a[i * nB + k] * b[j * nB + k];
            
            // horizontal summation
            for (int k = 0; k < 8; k++)
                c[i * n/2 + j] += s[k];
        }
    }
print(c);
    std::free(a);
    std::free(b);
}