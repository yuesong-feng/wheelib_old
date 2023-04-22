#include "log.h"

void func1()
{
    LOG_ERROR("func1");
}
void func2()
{
    LOG_WARN("func2");
}
void func3()
{
    LOG_INFO("func3");
}
void func4()
{
    LOG_DEBUG("func4");
}
int main()
{
    LOG_SET_LEVEL(LOG_LEVEL_DEBUG);
    // LOG_SET_FILE("log.log");
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