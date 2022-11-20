#include "thpool.h"
#include "log.h"
#include <stdio.h>
#include <unistd.h>

void thfunc(int *a) {
	LOG_INFO("Hello %d", *a);
}

struct args {
	int a;
	char *str;
};
void thfunc2(struct args* arg) {
	LOG_DEBUG("Hello %d %s", arg->a, arg->str);
}

int main() {
	LOG_LEVEL(LOG_DEBUG);
	thpool *tp = thpool_init(8);
	int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	for (int i = 1; i < 10; ++i) {
		thpool_add(tp, thfunc, a + i - 1);
	}

	struct args arg;
	arg.a = 3;
	arg.str = "hello";
	for (int i = 0; i < 5; ++i) {
		thpool_add(tp, thfunc2, &arg);
	}

	thpool_destroy(tp);
	return 0;
}
