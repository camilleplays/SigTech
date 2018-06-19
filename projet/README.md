# report project

## Gitlab info

Branch: develop
two main programs: lte_ru and lte_enb (in targets/RT/USER)

### In lte_ru function

fh_south_in is the first thing done:


```
 // synchronization on input FH interface, acquire signals/data and block
    if (ru->fh_south_in) ru->fh_south_in(ru,&frame,&subframe);
    else AssertFatal(1==0, "No fronthaul interface at south port");
```


Then there is the rx_rf function which can either work with an emulated rf or with an hardware device and garantees a constant flow of information to the inputs of ru_thread.

```
void rx_rf(RU_t *ru,int *frame,int *subframe) {

  RU_proc_t *proc = &ru->proc;
  LTE_DL_FRAME_PARMS *fp = &ru->frame_parms;
  void *rxp[ru->nb_rx];
  unsigned int rxs;
  int i;
  openair0_timestamp ts=0,old_ts=0;
    
  for (i=0; i<ru->nb_rx; i++)
    rxp[i] = (void*)&ru->common.rxdata[i][*subframe*fp->samples_per_tti];

  VCD_SIGNAL_DUMPER_DUMP_FUNCTION_BY_NAME( VCD_SIGNAL_DUMPER_FUNCTIONS_TRX_READ, 1 );

  old_ts = proc->timestamp_rx;
  if(emulate_rf){
    wait_on_condition(&proc->mutex_emulateRF,&proc->cond_emulateRF,&proc->instance_cnt_emulateRF,"emulatedRF_thread");
    release_thread(&proc->mutex_emulateRF,&proc->instance_cnt_emulateRF,"emulatedRF_thread");
    rxs = fp->samples_per_tti;
  }
  else{
    rxs = ru->rfdevice.trx_read_func(&ru->rfdevice,
           &ts,
           rxp,
           fp->samples_per_tti,
           ru->nb_rx);
  }

   VCD_SIGNAL_DUMPER_DUMP_FUNCTION_BY_NAME( VCD_SIGNAL_DUMPER_FUNCTIONS_TRX_READ, 0 );
 
  proc->timestamp_rx = ts-ru->ts_offset;

  //AssertFatal(rxs == fp->samples_per_tti,
        //"rx_rf: Asked for %d samples, got %d from USRP\n",fp->samples_per_tti,rxs);
  if (rxs != fp->samples_per_tti) LOG_E(PHY, "rx_rf: Asked for %d samples, got %d from USRP\n",fp->samples_per_tti,rxs);

  if (proc->first_rx == 1) {
    ru->ts_offset = proc->timestamp_rx;
    proc->timestamp_rx = 0;
  }
  else {
    if (proc->timestamp_rx - old_ts != fp->samples_per_tti) {
      //LOG_I(PHY,"rx_rf: rfdevice timing drift of %"PRId64" samples (ts_off %"PRId64")\n",proc->timestamp_rx - old_ts - fp->samples_per_tti,ru->ts_offset);
      ru->ts_offset += (proc->timestamp_rx - old_ts - fp->samples_per_tti);
      proc->timestamp_rx = ts-ru->ts_offset;
    }

  }

 ``` 


wakeup_enb function:
```

void wakeup_eNBs(RU_t *ru) {

  int i;
  PHY_VARS_eNB **eNB_list = ru->eNB_list;

  LOG_D(PHY,"wakeup_eNBs (num %d) for RU %d ru->eNB_top:%p\n",ru->num_eNB,ru->idx, ru->eNB_top);


  if (ru->num_eNB==1 && ru->eNB_top!=0 && get_nprocs() <= 4) {
    // call eNB function directly

    char string[20];
    sprintf(string,"Incoming RU %d",ru->idx);
    LOG_D(PHY,"RU %d Call eNB_top\n",ru->idx);
    ru->eNB_top(eNB_list[0],ru->proc.frame_rx,ru->proc.subframe_rx,string,ru);
  }
  else {

    LOG_D(PHY,"ru->num_eNB:%d\n", ru->num_eNB);

    for (i=0;i<ru->num_eNB;i++)
    {
      LOG_D(PHY,"ru->wakeup_rxtx:%p\n", ru->wakeup_rxtx);
      eNB_list[i]->proc.ru_proc = &ru->proc;
      if (ru->wakeup_rxtx!=0 && ru->wakeup_rxtx(eNB_list[i],ru) < 0)
      {
	LOG_E(PHY,"could not wakeup eNB rxtx process for subframe %d\n", ru->proc.subframe_rx);
      }
    }
  }
}

```

In this function, we loop into the enb_list and wakeup a thread. The enb_list is the connections between one of the enb to a thread.


In order to measure a function, put 'VCD_SIGNAL_DUMPER_DUMP_VARIABLE_BY_NAME' around it.


1st manip:

### Modification of programs

we put VCD_SIGNAL aroud the function wakeup_enbs in lte-ru (lign 1645, in the ru_thread function)


```
 VCD_SIGNAL_DUMPER_DUMP_FUNCTION_BY_NAME( VCD_SIGNAL_DUMPER_FUNCTIONS_WAKEUP_ENBS, 1 );  
 if (ru->num_eNB>0) wakeup_eNBs(ru);
 VCD_SIGNAL_DUMPER_DUMP_FUNCTION_BY_NAME( VCD_SIGNAL_DUMPER_FUNCTIONS_WAKEUP_ENBS, 0 ); 
```

We added WAKEUP_ENB in the openair2/UTIL/LOG/vcp_signal_dumper.c in the section IF4/IF5 signals:


```
"wakeup_eNBs",
```

and in openair2/UTIL/LOG/vcp_signal_dumper.h:


```
VCD_SIGNAL_DUMPER_FUNCTIONS_WAKEUP_ENBS,
```

### Lauching the vcd file:

Go in cmake_targets

```
./build_oai -w USRP -c --eNB
```
Then we go in /cmake_targets/lte_build_oai/build and type te command:

```
sudo gdb --args ./lte-softmodem -O ../../../targets/PROJECTS/GENERIC-LTE-EPC/CONF/enb.band7.tm1.100PRB.usrpx310.conf --codingw --fepw --emulate-rf  -V
```


After running the program in gdb, we obtain the file 'openair_dump_eNB.vcd' 
We have to open this file with gtkwave but the graphical interface doesn't work in ssh so we had to import the file along with a gtkw file (we used ENB_usrp.gtkw) 
