#include <iostream>
#include <deque>
#include <pthread.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 4

typedef struct shared {
  pthread_mutex_t lock;
  unsigned int front;
  unsigned int size;
  int buffer[BUFFER_SIZE];
} shared_t;

void print_buffer(shared *sh) {
  //std::cout << sh->front << " " << sh->size << " ";
  for (unsigned int i = 0; i < BUFFER_SIZE; i++) {
    unsigned int j = (sh->front + i) % BUFFER_SIZE;
    std::cout << "[";
    if (sh->buffer[j] == 0) {
      std::cout << " ";
    } else {
      std::cout << sh->buffer[j];
    }
    std::cout << "]";
  }

  std::cout << std::endl;
}

void *receive(void *s) {
  shared_t *sh = (shared_t *)s;
  pthread_mutex_t *lock = &(sh->lock);

  while(1) {
      pthread_mutex_lock(lock);
      if (sh->size > 0) {
          sh->size--;
          sh->buffer[sh->front] = 0;
          sh->front = (sh->front + 1) % BUFFER_SIZE;

          std::cout << "Receiving ";
          print_buffer(sh);
        pthread_mutex_unlock(lock);
      } else {
        std::cout << "Receiving [Empty]" << std::endl;
        pthread_mutex_unlock(lock);
        sleep(10);
      }


    sleep(rand() % 2 * 3 + 1);
  }
}

int main() {
  std::cout << "Size: struct " << sizeof(shared_t) << ", mutex " << sizeof(pthread_mutex_t) << ", front/size " << sizeof(unsigned int) << ", buffer " << sizeof(int) * BUFFER_SIZE <<  std::endl;

  pthread_t receiver;

  int fd = shm_open("/buffer", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
  ftruncate(fd, sizeof(shared_t));
  shared_t *sh = (shared_t *)mmap(NULL, sizeof(shared_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  sh->front = 0;
  sh->size = 0;
  for (unsigned int i = 0; i < BUFFER_SIZE; ++i) {
    sh->buffer[i] = 0;
  }

  pthread_mutex_t *lock = &(sh->lock);
  pthread_mutex_init(lock, NULL);
  pthread_create(&receiver, NULL, receive, (void *)sh);

  while(1) {
    pthread_mutex_lock(lock);
      sleep(1); // Some blocking processing time
      if (sh->size == BUFFER_SIZE) {
        std::cout << "Buffer is full" << std::endl;
        exit(1);
      }

      unsigned int i = (sh->front + sh->size) % BUFFER_SIZE;
      sh->size++;
      sh->buffer[i] = rand() % 9 + 1;

      std::cout << "Sending   ";
      print_buffer(sh);

    pthread_mutex_unlock(lock);

    sleep(rand() % 3 * 3 + 1);
  }

  return 1;
}