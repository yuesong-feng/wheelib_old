# wheelib
C wheel lib.

| file         | descrption  |
| ------------ | ----------- |
| src/dlist.h  | double list |
| src/queue.h  | queue       |
| src/thpool.h | thread pool |
| src/log.h    | log system  |
| src/Timer.h  | timer       |


### src/thpool.h
```C
// Initialize a thread pool with {size} threads
thpool *thpool_init(int size);

// Add an task to the thread pool
void thpool_add(thpool *tp, void *fn, void *args);

// Destroy the thread pool, all tasks added will be finished
void thpool_destroy(thpool *tp);
```
### src/log.h
```C
// output log, defult to stdout
LOG(fmt, ...)   //example: LOG("int: %d, Hello %c!", a, str)

// set log output target
SET_LOG_TARGET(log_file)    //example: SET_LOG_TARGET("./log.txt")
```
### src/Timer.h
```cpp
// Register a timer in a scope and set a name. 
// When scope ends, time spent will be printed.
Timer tm("scope");

// Print time spent from last checkpoint.
ti.time();
```