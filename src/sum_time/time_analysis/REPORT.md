## Time Analysis Observations
After tinkering with the array sizings and thread count,
I believe that large arrays and 2 threads are the sweet
spot on my machine where a multithreaded sum function runs
faster. However, on average the faster program is the serial
adder. I suspect the compiler is optimizing something to
make it more performant.

Here's some sample output from running the time analysis program.

| Array Size | Thread Count | Time ST (sec) | Time MT (sec) |
|------------|--------------|---------------|---------------|
| 10000      | 2            | 0.000025      | 0.000064      |
| 100000000  | 2            | 0.217308      | 0.201694      |
| 10000      | 8            | 0.000021      | 0.000278      |
| 100000000  | 8            | 0.210521      | 0.301716      |
