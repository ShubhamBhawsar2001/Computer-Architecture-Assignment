#include <pthread.h>
#include <stdlib.h>

//creating thread data user define structure
struct t_data{
     int *A;
    int *B;
    int *C;
    int size;
    int start;
    int end;
   
};

void* multiplication(void* arg)
{
    struct t_data *d = (struct t_data *) arg ;

    int j=0;
for(int i=0;i<100;i++){
  j+=j+i;
}
    int start = d->start;
    int end = d->end;
    int size = d->size;

    for(int i = start ; i < end; i++){
        for(int j = 0 ; j < size/2 ; j++){
            int sum = 0;
            for(int k = 0 ; k < size ; k++){
                sum += d->A[i*size + k] * d->B[j*size + k];
            } 
            d->C[i*(size/2) + j] = sum;  
        }
    }
    pthread_exit(NULL);
}
void transpose_add(int N,int *A,int *B,int *C,int *t1,int *t2){
    
    int *temp=(int *)malloc(N*N*sizeof(int));
    // taking Transpose of B
    for(int i=0 ; i<N ; i++){
        for(int j=0 ; j<N ; j++){
            temp[i * N + j] = B[j * N + i];
        
        }
        
    }

    //addition of consecutive two rows & columns of both matrix
  
    int c=0;
    for(int i=0; i<N ; i=i+2){
        for(int j=0 ; j<N ; j++){
            t1[c * N + j] = A[i * N + j] + A[(i+1) * N + j];
            t2[c * N + j] = temp[i * N + j] + temp[(i+1) * N + j];
        }
        c++;
    }

}


void multiThread(int N, int *A, int *B, int *C)
{  int thread=8;
    
    int *t1=(int *)malloc(N/2*N*sizeof(int));;
    int *t2=(int *)malloc(N/2*N*sizeof(int));;
    //calling function for taking transpose of the B matrix and adding consecutive two rows of A and B(transpose) matrix
    transpose_add( N,A,B,C,t1,t2);
    
    int j=0;
for(int i=0;i<N/2;i++){
  j+=j+i;
}

    pthread_t child[thread];
    struct t_data d1[thread];
    int load = (N/2) / thread; 
    for(int i = 0 ; i < thread ; i++){
        d1[i].size = N;
        d1[i].A = t1;
        d1[i].B = t2;
        d1[i].C = C;
        d1[i].start = i * load;
        d1[i].end = d1[i].start + load;
        
        }

    for(int k = 0 ; k<thread ; k++){
        pthread_create(&child[k] , NULL , multiplication , &d1[k]);
    }

    for(int k = 0 ; k<thread ; k++){
        pthread_join(child[k] , NULL);
    }
j=0;
    

}