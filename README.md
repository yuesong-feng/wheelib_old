# wheelib
C wheel lib.

| file         | descrption  |
| ------------ | ----------- |
| src/dlist.h  | double list |
| src/queue.h  | queue       |
| src/thpool.h | thread pool |

### src/thpool.h
```C
// Initialize a thread pool with {size} threads
thpool *thpool_init(int size);

// Add an task to the thread pool
void thpool_add(thpool *tp, void *fn, void *args);

// Destroy the thread pool, all tasks added will be finished
void thpool_destroy(thpool *tp);
```

