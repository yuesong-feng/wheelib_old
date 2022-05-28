#include "log.h"
#include "Timer.h"

void test_function(){
  Timer tm(__func__);
}

int main() {
  Timer tm(__func__);
  LOG("test log");
  
  test_function();
  tm.time();
  tm.time();
  return 0;
}
