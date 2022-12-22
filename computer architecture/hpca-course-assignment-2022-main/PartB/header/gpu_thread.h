

__global__ void matrixMul(int *a,int *b, int *c, int N) {
  // Compute each thread's global row and column index
  int row = blockIdx.y * blockDim.y + threadIdx.y;
  int col = blockIdx.x * blockDim.x + threadIdx.x;

  // Iterate over row, and down column

  //c[row * (N/2) + col] = 0;
  int temp=0;
  int temp1=0;
  for (int k = 0; k < N; k++) {
    // Accumulate results for a single element of c
    temp+= a[row *2*N + k] * b[k * N + col*2];
    temp+= a[(row*2+1)*N + k] * b[k * N + col*2];
    temp += a[row *N*2 + k] * b[k * N + col*2+1];
    temp += a[(row*2+1) * N + k] * b[k * N + col*2+1];
  }
   for (int k = 0; k < N; k++) {
    temp1+= a[row *2*N + k] * b[k * N + col*2];
    temp1+= a[(row*2+1)*N + k] * b[k * N + col*2];
    temp1+= a[row *N*2 + k] * b[k * N + col*2+1];
    temp1+= a[(row*2+1) * N + k] * b[k * N + col*2+1];
  }
  c[row * (N/2) + col]=temp;
}




void gpuThread(int N, int *matA, int *matB, int *output)
{




  size_t bytes = N * N * sizeof(int);
   size_t bytes1 = (N/2) * (N/2) * sizeof(int);
     int *a, *b, *c;
  cudaMalloc(&a, bytes);
  cudaMalloc(&b, bytes);
  cudaMalloc(&c, bytes1);

 
  cudaMemcpy(a, matA, bytes, cudaMemcpyHostToDevice);
  cudaMemcpy(b, matB, bytes, cudaMemcpyHostToDevice);

  
  int THREADS = 32;

  int BLOCKS = (N/2) / THREADS;

  
  dim3 threads(THREADS, THREADS);
  dim3 blocks(BLOCKS, BLOCKS);

  // Launch kernel
  matrixMul<<<blocks, threads>>>(d_a, d_b, d_c, N);

  // Copy back to the host
  cudaMemcpy(output,c, bytes1, cudaMemcpyDeviceToHost);

  // Free memory on device
  cudaFree(d_a);
  cudaFree(d_b);
  cudaFree(d_c);

 
}


