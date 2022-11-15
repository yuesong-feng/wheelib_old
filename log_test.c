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
    LOG_DEBUG("main");
    LOG_LEVEL(LOG_DEBUG);
    func1();
    func2();
    func3();
    func4();
    return 0;
}