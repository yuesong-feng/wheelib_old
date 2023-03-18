#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

static char *shm_ptr = NULL;

int main()
{
  shm_ptr =
      mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
  if (shm_ptr == NULL)
  {
    perror("fail to mmap: ");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < 10; ++i)
  {
    shm_ptr[i] = 'a';
  }
  printf("%s\n", shm_ptr);

  if (munmap(shm_ptr, 4096) == -1)
  {
    perror("faile to munmap: ");
    exit(EXIT_FAILURE);
  }

  return 0;
}