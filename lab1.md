# Lab1


## Q15



```c
bfly[0].r = SAT_ADD16(SAT_ADD16(x[n2].r,x[N2 + n2].r),SAT_ADD16(x[2*N2 + n2].r,x[3*N2 + n2].r));
bfly[0].i = SAT_ADD16(SAT_ADD16(x[n2].i,x[N2 + n2].i),SAT_ADD16(x[2*N2 + n2].i,x[3*N2 + n2].i));
bfly[1].r = SAT_ADD16(SAT_ADD16(x[n2].r,x[N2 + n2].i),-SAT_ADD16(x[2*N2 + n2].r,x[3*N2 + n2].i));
bfly[1].i = SAT_ADD16(SAT_ADD16(x[n2].i,-x[N2 + n2].r),SAT_ADD16(-x[2*N2 + n2].i,x[3*N2 + n2].r));

bfly[2].r = SAT_ADD16(SAT_ADD16(x[n2].r,-x[N2 + n2].r),SAT_ADD16(x[2*N2 + n2].r,-x[3*N2 + n2].r));
bfly[2].i = SAT_ADD16(SAT_ADD16(x[n2].i,-x[N2 + n2].i),SAT_ADD16(x[2*N2 + n2].i,-x[3*N2 + n2].i));

bfly[3].r = SAT_ADD16(SAT_ADD16(x[n2].r,-x[N2 + n2].i),SAT_ADD16(-x[2*N2 + n2].r,x[3*N2 + n2].i));
bfly[3].i = SAT_ADD16(SAT_ADD16(x[n2].i,x[N2 + n2].r),-SAT_ADD16(x[2*N2 + n2].i,x[3*N2 + n2].r));
```

```c
// In-place results
for (k1=0; k1<N1; k1++)
{
twiddle_fixed(&W, N, (double)k1*(double)n2);
x[n2 + N2*k1].r = SAT_ADD16(FIX_MPY(bfly[k1].r,W.r),FIX_MPY(-bfly[k1].i,W.i));
x[n2 + N2*k1].i = SAT_ADD16(FIX_MPY(bfly[k1].i,W.r),FIX_MPY(bfly[k1].r,W.i));

}

```


### Q15_QPSK

![Q15_QPSK_r.png](work/Q15_QPSK_r.png)


### Q15_cos

![Q15_cos_r.png](work/Q15_cos_r.png)

### Q15_16QAM


![Q15_16QAM_r.png](work/Q15_16QAM_r.png)

## Q24x17

```c
bfly[0].r = SAT_ADD25(SAT_ADD25(x[n2].r,x[N2 + n2].r),SAT_ADD25(x[2*N2 + n2].r,x[3*N2 + n2].r));
bfly[0].i = SAT_ADD25(SAT_ADD25(x[n2].i,x[N2 + n2].i),SAT_ADD25(x[2*N2 + n2].i,x[3*N2 + n2].i));
bfly[1].r = SAT_ADD25(SAT_ADD25(x[n2].r,x[N2 + n2].i),-SAT_ADD25(x[2*N2 + n2].r,x[3*N2 + n2].i));
bfly[1].i = SAT_ADD25(SAT_ADD25(x[n2].i,-x[N2 + n2].r),SAT_ADD25(-x[2*N2 + n2].i,x[3*N2 + n2].r));

bfly[2].r = SAT_ADD25(SAT_ADD25(x[n2].r,-x[N2 + n2].r),SAT_ADD25(x[2*N2 + n2].r,-x[3*N2 + n2].r));
bfly[2].i = SAT_ADD25(SAT_ADD25(x[n2].i,-x[N2 + n2].i),SAT_ADD25(x[2*N2 + n2].i,-x[3*N2 + n2].i));

bfly[3].r = SAT_ADD25(SAT_ADD25(x[n2].r,-x[N2 + n2].i),SAT_ADD25(-x[2*N2 + n2].r,x[3*N2 + n2].i));
bfly[3].i = SAT_ADD25(SAT_ADD25(x[n2].i,x[N2 + n2].r),-SAT_ADD25(x[2*N2 + n2].i,x[3*N2 + n2].r));
```
```c
for (k1=0; k1<N1; k1++)
{
twiddle_fixed_Q17(&W, N, (double)k1*(double)n2);
x[n2 + N2*k1].r = SAT_ADD25(FIX_MPY25by18(bfly[k1].r,W.r),-FIX_MPY25by18(bfly[k1].i,W.i));
x[n2 + N2*k1].i = SAT_ADD25(FIX_MPY25by18(bfly[k1].i,W.r),FIX_MPY25by18(bfly[k1].r,W.i));
}
```

```c
// Do Q24 FFT
radix4_fixed_Q24xQ17(data32, N,scale,0);
bit_r4_reorder_fixed_Q17(data32, N);


// Compute Distortion statistics
mean_error = 0.0;
mean_in = 0.0;
for (i=0;i<N;i++) {
  mean_in += data[i].r*data[i].r + data[i].i*data[i].i;
  mean_error += pow((data[i].r-((double)data32[i].r/32767.0)),2) + pow((data[i].i-((double)data32[i].i/32767.0)),2);
}


```

### Q24x17_cos


![Q24xQ17_cos_r.png](work/Q24xQ17_cos.png)


### Q24xQ17_QPSK

![Q24xQ17_cos_r.png](work/Q24xQ17_QPSK.png)
