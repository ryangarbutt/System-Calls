# System-Calls-in-C++

A C++ program, that receives one argument, (i.e., argv[1]) upon its invocation and searches how many processes whosename is given in argv[1] are running on the system where the program has been invoked.

To Run Actual System Calls: 
ps -A | grep kworker | wc -l

To Run The Program's System Calls: 
./processes kworker
