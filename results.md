## Results

Vector size: 1048576
Number of runs per benchmark: 10

Running benchmark: Parallel Unsequenced Sort (10 runs)... Done.
Running benchmark: Parallel Sort (10 runs)... Done.
Running benchmark: Sequential Sort (10 runs)... Done.

--- Average Execution Times ---
Parallel Unsequenced: 21.319 ms
Parallel            : 21.160 ms
Sequential          : 92.281 ms

## Discussion

As expected, the parallel execution policies outperform the sequential one by about 4x.
This may indicate that my code is being run with 4 threads, although further confirmation
would be necessary to confirm this.

Interestingly, par_unseq is not faster than par — this may be because the complexity associated
with vectorizing sort outweighs the benefit provided by it.
