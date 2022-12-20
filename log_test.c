#include "log.h"

void func1 () {
    LOG_ERROR("func1");
}
void func2 () {
    LOG_WARN("func2");
}
void func3 () {
    LOG_INFO("func2");
}
void func4 () {
    LOG_DEBUG("func2");
}
int main() {
    LOG_LEVEL(LOG_INFO);
    LOG_FILE("log.log");
    LOG_DEBUG("main");
    func1();
    func2();
    func3();
    func4();
    int a = 123;
    const char *str = "test";
    LOG_WARN("log test %d", a);
    LOG_WARN("log %s %d", str, a);
    return 0;
}