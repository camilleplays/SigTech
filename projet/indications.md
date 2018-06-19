precoding function itself.
on the machines phoenix and bellatrix: 20 cores (8-10 ru's in parallele)

precoding:
ru1: fep-prectx
-on each of the ru, we have a emulrf. We can measure the threading latences (how long it takes for the ru to wake up)
-one enb entity for several ru (flow in and out between the two): measure rX/TX timing.
from ru to enb: wakeupenb. the last one goes to enB extx thread. measure all the timing from the first one sending data to the last one sending data.

chrnologie: the ru wake up one by one, followed by the RX and TX (those dont overlap, one after the other) and then the rxtx: the all thing should take less then 2 ms.

-vcd: vcd-signal-temper equivalent to start-meas and stop-meas.
inline measurement => logs

understanding the setup and the limits of the timing measurements.



2e reu:

all on develop

several ru_thread: function ru_thread
lte_ru program:
fh_south_in: 1st thing done, generic function.
rx_rf fucntion (either info from an emulated rf or from a real hardware device): garantees a constant flow of information to the inputs of ru_thread. measure the difference of time between the threads.
After there is the fep-rx: constant processing function, does a little bit of signal processsing, after it completes, we have the wake up eNBs.
ru_list: connections between one of the thread to one of the enbs entity.
enb_list: connections between one of the enb to a thread.
ligne 660: put time mesurement around the function.

in the 'if, else' function we loop into the enb_list and wake up a thread.

cond_enb needs to be finished to launch ru_tx.


4 threads: ru_tx, ru_rx, enb_tx and enb_rx.


deep into fep_tx: we have main thread + worker (checks if the machine has enough cores.)

in lte_enb:
wakeup_rxtx: picks the ru that happens to be calling the enb.


around line 418: an if condition checks we have done the right thing before jumping into the particular function.
in general the code is either calling a function or waking up a thread to do it.


use vcd with option -v to actually see the output (run it for like 5/6 sec). A file is created: /tmp/openair_dump_eNB.vcd and run it with gtkwave file.vcd -a file.gtkw (in targets/USER)


in openair2/UTIL/LOG: we can add things in vcd_dumper: list of active signals, list of variables and list of functions.
in the h file: enumeration (actual numbers in the program).


TO DO:
Generate the configuration file in targets/PROJECTS/GENERIC_LTE-EPC/enb.band7.tm1.100PRB.usrpx310.conf and add as many RUs section as needed. Start testing with two RUs and one eNB.
in UTIL/LOG in openair2, replace read and write of trx and replace it with fh_south_in.

signal FH_south_in0 + ru-> idx (around 1607)

ligne 776 suppress the condition

look inside the ru_procedure or ru_thread
in ru_procedure : ligne 387


explain all of this.
structure of the entities, ru with input/output and the enb_thread
