# Launching Multiple jsruns

Jsrun provides the ability to launch multiple jsrun job launches within a single node and across multiple nodes within a single batch allocation.  This section provides examples of job launches where multiple jsruns are executed within a single batch job allocation.  The section is divided into examples running multiple jsruns both sequentially and simultaneously.

The js_task_info command paired with sleep can be used to test layout of multiple jsruns.  The js_task_info will display the resource set while the sleep will hold resources to help simulate code execution.

## Exercise 1: Sequential

This method launches multiple jsruns in a sequential manner.  Each jsrun is executed one at a time.  

The following batch job will execute three jsruns sequentially. 

```
#!/bin/bash
#BSUB -W 2:00
#BSUB -nnodes 2
#BSUB -P abc007
#BSUB -J SequentialEx

cd $MEMBERWORK/abc007

jsrun -n12 -r6 -g1 -a1 -c2 csh -c "js_task_info; sleep 30"
jsrun -n12 -r6 -g1 -a1 -c2 csh -c "js_task_info; sleep 30"
jsrun -n12 -r6 -g1 -a1 -c2 csh -c "js_task_info; sleep 30"

jslist
```



**Batch job considerations**
Batch job node requests should be equal to the node requirements of the largest jsrun.  The requested walltime should be greater than the sum of all jsruns.

## Exercise 2: Simultaneous

This method launches multiple jsruns in a simultaneous manner.  Multiple jsruns are executed at the same time.  Each jsrun is allocated separate GPU and CPU resources in all test cases.

The following batch job will execute three jsruns simultaneously: 
```
#!/bin/bash
#BSUB -W 1:00
#BSUB -nnodes 6
#BSUB -P abc007
#BSUB -J SimultaneousEx

cd $MEMBERWORK/abc007

jsrun -n12 -r6 -g1 -a1 -c2 csh -c "js_task_info; sleep 30" &
jsrun -n12 -r6 -g1 -a1 -c2 csh -c "js_task_info; sleep 30" &
jsrun -n12 -r6 -g1 -a1 -c2 csh -c "js_task_info; sleep 30" &

jslist 

wait

jslist
```

>NOTE: When backgrounding tasks, the wait command is needed to prevent the batch script's shell from exiting before all backgrounded tasks complete.
>

**Batch job considerations**
Batch job node requests should be equal to the sum of all simultaneous jsrun node requirements.  The requested walltime should be greater than the longest running jsrun.


## Exercise 3: Viewing the jsrun queue

IBM’s Cluster System Management (CSM) manages placement of all jsruns.  This allows placement of jsruns on unique hardware within the allocation.  When running multiple jsruns the system will queue requests as needed until resources free.  Jslist can be used to view the jsrun queue.  The command will list running, pending, and completed jsruns within a CSM allocation.  

The following example uses a two node interactive batch allocation to show how the system queues requests than cannot fit on the allocated resources.  In the example the first jsrun requests 6 GPUs and one core.  The second example requests 42 cores.  The third example requests one core and one GPU.  Since the third jsrun cannot fit within a node, the system will queue the request until either the first or second jsrun completes and frees enough resources.
```
summit-login3> bsub -Is -nnodes2 -Pabc007 -W1:00 $SHELL

summit-batch3> jsrun -n1 -a1 -c1 -g6 -bpacked:1 csh -c "js_task_info; sleep 30" &
Task 0 ( 0/1, 0/1 ) is bound to cpu[s] 0-3 on host a01n02

summit-batch3> jsrun -n1 -a1 -c42 -g0 -bpacked:1 csh -c "js_task_info; sleep 30" &
Task 0 ( 0/1, 0/1 ) is bound to cpu[s] 0-3 on host a01n01

summit-batch3> jsrun -n1 -a1 -c1 -g1 -bpacked:1 csh -c "js_task_info; sleep 30" &

summit-batch3> jslist
        parent               cpus      gpus        exit
   ID     ID       nrs      per RS    per RS     status         status
===============================================================================
   17     0         1          1         6            0         Running
   18     0         1         42         0            0         Running
   19     0         1          1         1            0          Queued
    1     0         1          1         3            0         Complete
   ```
