// Include files for SSE4
#include "emmintrin.h"
#include "xmmintrin.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <tmmintrin.h>
#include <immintrin.h>
#include "time_meas.h"
#include <malloc.h>


//
// int FIX_MPY(short x,short y){
// 	return ((short)(((int)x * (int)y)>>15));
// }




int FIX_MPY(short x,short y){
	return ((int32_t)x* (int32_t)y )>>15;
}

// example SIMD macros, not necessary to be used, write your own


//
// inline void cmult(__m128i a,__m128i b, __m128i *re32, __m128i *im32) {
//
//
//   register __m128i mmtmpb;
//   mmtmpb    = _mm_sign_epi16(b,*(__m128i*)reflip);
//   *re32     = _mm_madd_epi16(a,mmtmpb);
//   mmtmpb    = _mm_shufflelo_epi16(b,_MM_SHUFFLE(2,3,0,1));
//   mmtmpb    = _mm_shufflehi_epi16(mmtmpb,_MM_SHUFFLE(2,3,0,1));
//   *im32  = _mm_madd_epi16(a,mmtmpb);
//
// }
//
// __m128i cpack_tmp1,cpack_tmp2;
// inline __m128i cpack(__m128i xre,__m128i xim) {
//
//   cpack_tmp1 = _mm_unpacklo_epi32(xre,xim);
//   cpack_tmp1 = _mm_srai_epi32(cpack_tmp1,15);
//   cpack_tmp2 = _mm_unpackhi_epi32(xre,xim);
//   cpack_tmp2 = _mm_srai_epi32(cpack_tmp2,15);
//   return(_mm_packs_epi32(cpack_tmp1,cpack_tmp2));
//
// }

// routines to be written
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

for (int i=0; i<N; i+=8){
  z128[i] = _mm_mulhrs_epi16(x128[i], y128[i]);
	z128[i+1] = _mm_mulhrs_epi16(x128[i], y128[i+1]);
	z128[i+2] = _mm_mulhrs_epi16(x128[i], y128[i+2]);
	z128[i+3] = _mm_mulhrs_epi16(x128[i], y128[i+3]);
	z128[i+4] = _mm_mulhrs_epi16(x128[i], y128[i+4]);
	z128[i+5] = _mm_mulhrs_epi16(x128[i], y128[i+5]);
	z128[i+6] = _mm_mulhrs_epi16(x128[i], y128[i+6]);
	z128[i+7] = _mm_mulhrs_epi16(x128[i], y128[i+7]);
}
}


void componentwise_multiply_real_avx2(int16_t *x,int16_t *y,int16_t *z,uint16_t N) {

__m256i *x256 = (__m256i *)x;
__m256i *y256 = (__m256i *)y;
__m256i *z256 = (__m256i *)z;
for (int i=0; i<N; i+=8){
  z256[i] = _mm256_mullo_epi16(x256[i], y256[i]);
	z256[i+1] = _mm256_mullo_epi16(x256[i], y256[i+1]);
	z256[i+2] = _mm256_mullo_epi16(x256[i], y256[i+2]);
	z256[i+3] = _mm256_mullo_epi16(x256[i], y256[i+3]);
	z256[i+4] = _mm256_mullo_epi16(x256[i], y256[i+4]);
	z256[i+5] = _mm256_mullo_epi16(x256[i], y256[i+5]);
	z256[i+6] = _mm256_mullo_epi16(x256[i], y256[i+6]);
	z256[i+7] = _mm256_mullo_epi16(x256[i], y256[i+7]);
}
}


void componentwise_multiply_real_avx2_hrs(int16_t *x,int16_t *y,int16_t *z,uint16_t N) {

__m256i *x256 = (__m256i *)x;
__m256i *y256 = (__m256i *)y;
__m256i *z256 = (__m256i *)z;
for (int i=0; i<N; i+=8){
	z256[i] = _mm256_mulhrs_epi16(x256[i], y256[i]);
	z256[i+1] = _mm256_mulhrs_epi16(x256[i], y256[i+1]);
	z256[i+2] = _mm256_mulhrs_epi16(x256[i], y256[i+2]);
	z256[i+3] = _mm256_mulhrs_epi16(x256[i], y256[i+3]);
	z256[i+4] = _mm256_mulhrs_epi16(x256[i], y256[i+4]);
	z256[i+5] = _mm256_mulhrs_epi16(x256[i], y256[i+5]);
	z256[i+6] = _mm256_mulhrs_epi16(x256[i], y256[i+6]);
	z256[i+7] = _mm256_mulhrs_epi16(x256[i], y256[i+7]);
}
}

void generate_random(int16_t *x, int16_t *y, int N){
  for (int i=0; i<N; i++){
    x[i]=rand();
    y[i]=rand();
  }
}


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
	//
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
  	}

		for (int i = 0; i<N; i++){
    		reset_meas(&ts);
    		for (int j = 0; j<10000; j++){
			start_meas(&ts);
      			componentwise_multiply_real_avx2_hrs(u,v,w,i);
      			stop_meas(&ts);
    		}
		file = fopen("test2","a+");
        	fprintf(file, "%lld\n", ts.diff/10000);
		fclose(file);
  	}


	free(x);
	free(y);
	free(z);
	free(u);
	free(v);
	free(w);

  return(0);


}
