#include <stdatomic.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

static atomic_int x = 0;

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *fn1(){
    for (int i = 0; i < 10000000; ++i) {
        x++;
    }
    return NULL;
}

void *fn2(){
    for (int i = 0; i < 10000000; ++i) {
        while(x <= 0) {}
        x--;
    }
    return NULL;
}

void *fn1_mtx() {
    for (int i = 0; i < 10000000; ++i) {
        pthread_mutex_lock(&mtx);
        x++;
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

void *fn2_mtx() {
    for (int i = 0; i < 10000000; ++i) {
        while(x <= 0) {}
        pthread_mutex_lock(&mtx);
        x--;
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

void *fn1_cnd() {
    for (int i = 0; i < 10000000; ++i) {
        pthread_mutex_lock(&mtx);
        x++;
        pthread_mutex_unlock(&mtx);
        pthread_cond_signal(&cond);
    }
    return NULL;
}

void *fn2_cnd() {
    for (int i = 0; i < 10000000; ++i) {
        pthread_mutex_lock(&mtx);
        while (x <= 0) {
            pthread_cond_wait(&cond, &mtx);
        }
        x--;
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

int main(){
    // test 1, raw
    clock_t start = clock();
    pthread_t th1 = NULL;
    pthread_t th2 = NULL;
    pthread_create(&th1, NULL, fn1, NULL);
    pthread_create(&th2, NULL, fn2, NULL);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    clock_t end = clock();
    double duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Raw: result %d, time %f seconds\n", x, duration);

    // test 2, mutex
    x = 0;
    start = clock();
    pthread_create(&th1, NULL, fn1_mtx, NULL);
    pthread_create(&th2, NULL, fn2_mtx, NULL);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Raw: result %d, time %f seconds\n", x, duration);

    // test 3, cond
    x = 0;
    start = clock();
    pthread_create(&th1, NULL, fn1_cnd, NULL);
    pthread_create(&th2, NULL, fn2_cnd, NULL);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Raw: result %d, time %f seconds\n", x, duration);

    return 0;
}