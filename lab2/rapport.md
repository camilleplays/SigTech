# LAB2





```c++

void componentwise_multiply_real_scalar(int16_t *x,int16_t *y,int16_t *z,uint16_t N) {
  for(int i=0; i<N; i++){
    z[i]=FIX_MPY(x[i],y[i]);
  }


}

// routines to be written
void componentwise_multiply_real_sse4(int16_t *x,int16_t *y,int16_t *z,uint16_t N) {

__m128i *x128 = (__m128i *)x;
__m128i *y128 = (__m128i *)y;
__m128i *z128 = (__m128i *)z;

for (int i=0; i<N; i++){
  z128[i] = _mm_mulhrs_epi16(x128[i], y128[i]);
}
}


void componentwise_multiply_real_avx2(int16_t *x,int16_t *y,int16_t *z,uint16_t N) {

__m256i *x256 = (__m256i *)x;
__m256i *y256 = (__m256i *)y;
__m256i *z256 = (__m256i *)z;
for (int i=0; i<N; i++){
  z256[i] = _mm256_mullo_epi16(x256[i], y256[i]);
}
}
```


```c++
int main() {

	int N = 1000;

  int16_t *x, *y, *z;
  // x=(int16_t *)memalign(16, N << 1);
	// y=(int16_t *)memalign(16, N << 1);
	// z=(int16_t *)memalign(16, N << 1);

	//
	// x=malloc((N*160) *sizeof(int16_t));
	// y=malloc((N*160) *sizeof(int16_t));
	// z=malloc((N*160) *sizeof(int16_t));

	x=aligned_alloc(32,(N + N*288) *sizeof(int16_t));
	y=aligned_alloc(32,(N + N*288) *sizeof(int16_t));
	z=aligned_alloc(32,(N + N*288) *sizeof(int16_t));

  generate_random(x, y, N);
 // printf("%d\n", x[4]);
 // componentwise_multiply_real_scalar(x, y, z, N);




	// x=(int16_t *)memalign(64, 32);
	// y=(int16_t *)memalign(64, 32);
	// z=(int16_t *)memalign(64, 32);


 // generate_random(x, y, N);
 // componentwise_multiply_real_sse4(x, y, z, N);


	// void free(void *x);
	// void free(void *y);
	// void free(void *z);

  int16_t *u, *v, *w;
	u=aligned_alloc(32,(N + N*288) *sizeof(int16_t));
	v=aligned_alloc(32,(N + N*288) *sizeof(int16_t));
	w=aligned_alloc(32,(N + N*288) *sizeof(int16_t));


 generate_random(u, v, N);
// for (int i = 0; i<N; i++){
//	 printf("%d", u[i]);
//	printf("%d\n", v[i]);
//}
  // componentwise_multiply_real_avx2(u, v, w, 10);


  //componentwise_multiply_real_avx2(u,v,w,N);


  time_stats_t ts;

	FILE *file;
	file=fopen("scalar_version","w+");

 	 for (int i = 0; i<N; i++){
		reset_meas(&ts);
    		for (int j = 0; j<10000; j++){
      			start_meas(&ts);
      			componentwise_multiply_real_scalar(x,y,z,i);
      			stop_meas(&ts);
    		}

		fprintf(file, "%lld\n", ts.diff/10000);

  	}

	fclose(file);


        file=fopen("ssE4","w+");

	for (int i = 0; i<N; i++){
   	 	reset_meas(&ts);
    		for (int j = 0; j<10000; j++){
      			start_meas(&ts);
      			componentwise_multiply_real_sse4(x,y,z,i);
      			stop_meas(&ts);
    		}
		fprintf(file, "%lld\n", ts.diff/10000);
  	}

        fclose(file);



  	for (int i = 0; i<N; i++){
    		reset_meas(&ts);
    		for (int j = 0; j<10000; j++){
			start_meas(&ts);
      			componentwise_multiply_real_avx2(u,v,w,i);
      			stop_meas(&ts);
    		}
		file = fopen("test","a+");
        	fprintf(file, "%lld\n", ts.diff/10000);
		fclose(file);
		printf("%d\n", i);
  	}


	free(x);
	free(y);
	free(z);
	free(u);
	free(v);
	free(w);

  return(0);


}
```
