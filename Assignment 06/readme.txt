Raymond Lin
304937942
Lab 2

Homework Report
The following data was obtained from the tests that were run on my parallelized version of the SRT implementation:
time ./srt 1-test.ppm >1-test.ppm.tmp
real    0m47.904s
user    1m35.611s
sys     0m0.004s

time ./srt 2-test.ppm >2-test.ppm.tmp
real    0m24.359s
user    1m12.820s
sys     0m0.002s

time ./srt 4-test.ppm >4-test.ppm.tmp
real    0m12.489s
user    1m1.705s
sys     0m0.002s

time ./srt 8-test.ppm >8-test.ppm.tmp
real    0m7.485s
user    1m1.587s
sys     0m0.004s

It seems that the parallization of the program worked as expected. According to the data, the general trend follows the fact that if there are more threads available, the program will take a shorter amount of time, because more work can be allocated to additional threads and work can be done simultaneously. We can see that the runtime of the program is inversely proportional to the number of threads available. If we double the number of threads available, the runtime will be divided by 2. 

This is because I parallelized the code by modifying the loops that occurred in the main function. Each thread can operate on a portion of the loop - a form of data decomposition. I divided the number of iterations in the outermost loop up by the numebr of threads that was passed in. This is why runtime and number of threads are inversely proportional.

Because the pthread_create function requires a function name, I knew that I had to place the loops into a different function and move local variables in main to global variables. I ran into problems, such as figuring out how to use the pthread_create nd pthread_join functions and passing in the correct parameters so that the program would work correctly. 