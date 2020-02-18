# Exercises: `jsrun` Basics

For these exercises, you should request a Summit allocation of 1 or 2 compute nodes, as needed. While these will be most easily worked in an interactive job, they can all be run as job scripts in a non-interactive format.

To submit a 2 node job under this event's reservation (and avoid waiting in the queue), run the following command from a Summit login node:

```
$ bsub -P <PROJID> -nnodes 2 -W 20 -U jsrun -Is $SHELL
```

where `<PROJID>` will need to be replaced with an OLCF project you are associated with.

Recall that there are options to `bsub` that are applied allocation-wide. If a value needs to be set for `bsub -alloc_flags ____`, this must be specified during job submission.

#### Use what's in the `jsrun` toolbox!

* The Manual Page (`man jsrun`)
* [Job Step Viewer](https://jobstepviewer.olcf.ornl.gov/)
* [Hello_jsrun](https://code.ornl.gov/t4p/Hello_jsrun)
* Built-in Test Executable (`js_task_info`)

> NOTE: If you already feel comfortable with the essentials of `jsrun`, find an option that you're unfamiliar with in the manual page (`man jsrun`) and experiment with its behavior. There are many more `jsrun` configurations than we've covered in this section. Use the tools listed above to explore.

## Exercise 1

Design a Resource Set that meets the following criteria:

* 6 Physical Cores
* 1 task per Physical Core

How many of these Resource Sets can you fit in your 1 or 2 node job? How many could fit in a 1,000 node job?

Run this `jsrun` layout on Summit using Job Step Viewer, `Hello_jsrun`, or `js_task_info`.

## Exercise 2

The previous example did not use the available NVIDIA V100 GPUs, and as a result didn't realize the full capability of Summit's compute nodes. For this exercise, create 1 Resource Set per socket in your job that includes all GPU and Physical Core resources. Start 1 task per Physical Core. 

Run this `jsrun` layout on Summit using Job Step Viewer, `Hello_jsrun`, or `js_task_info`.

In this case, what option could you give `jsrun` to ensure even numbered and odd numbered tasks are never in the same Resource Set?

## Exercise 3

```
$ jsrun -n6 -c7 -g1 -a1 -EOMP_NUM_THREADS=7
```

The `jsrun` line above oversubscribes Hardware Threads with OpenMP threads. 

Run this `jsrun` layout on Summit using Job Step Viewer, `Hello_jsrun`, or `js_task_info` to see this behavior. You should receive the following warning, as oversubscription is often undesirable and can reduce performance:

```
Warning: OMP_NUM_THREADS=7 is greater than available PU's
```

What option can be added to distribute the OpenMP threads 1 per Physical Core?

**BONUS:** What's a different option that has the same distribution effect?

## Exercise 4

Repeat any of the previous exercises, but restrict process placement using various Simultaneous Multithreading (SMT) levels. Recall that setting the SMT level is a value to `bsub -alloc_flags` and is fixed for the entire allocation at time of job launch.
