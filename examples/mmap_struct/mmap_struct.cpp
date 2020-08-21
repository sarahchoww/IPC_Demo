#include <iostream>
#include <string>

#include <sys/mman.h>
#include <sys/stat.h>     /* For mode constants */
#include <sys/types.h>
#include <fcntl.h>        /* For O_* constants */
#include <unistd.h>

enum types {
    MSG1,
    MSG2,
    MSG3
};

struct msg {
    enum types type;
    int data;
};

int main() {
    int shmid;
    const char *shmn = "/test";
    unsigned int size = sizeof(struct msg);
    struct msg *message;

    shmid = shm_open(shmn, O_RDWR | O_CREAT, S_IRWXU | S_IRWXG);

    ftruncate(shmid, size);

    message = (struct msg *)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, shmid, 0);

    std::cout << "sizof struct msg " << sizeof(struct msg) << std::endl;
    std::cout << "sizof enum types " << sizeof(enum types) << std::endl;
    std::cout << "sizof int        " << sizeof(int) << std::endl;

    std::string test;
    std::cin >> test;

    message->type = types::MSG3;
    message->data = 100;

    std::cout << "setting data: " << std::dec << message->data << " 0x" << std::hex << message->data << std::endl;

    std::cin >> test;

    message->type = types::MSG2;
    message->data = 0xFABCD;

    std::cout << "setting data: " << std::dec << message->data << " 0x" << std::hex << message->data << std::endl;

    int val = 0;
    while (val != -1) {
        std::cin >> val;
        message->data = val;

        std::cout << "setting data: " << std::dec << message->data << " 0x" << std::hex << message->data << std::endl;
    }

    munmap(message, size);

    shm_unlink(shmn);

    return 0;
}