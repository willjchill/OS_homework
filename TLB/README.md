## Studying Translation Lookaside Buffers (TLB)

This directory contains scripts that will allow you to measure
the TLB cache levels and hit rate for a single core.

A tlb.c file will see how long it takes on average (depending on the # of trials)
to go through a number of pages specified. It will do this by going through 
a loop in an array containing memory equivalent to the number of pages requested.

How to use:

1. ./tlb <number of pages to touch> <number of trials>  ---> OUTPUTS TIME TO ACCESS # OF PAGES IN NANOSECONDS
2. ./graph.sh ---> CREATES CSV w/ ALL OUTPUT TIMES FROM 1 to 64 PAGES 
