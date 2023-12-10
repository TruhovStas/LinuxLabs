#include <iostream>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <sys/wait.h>

#define FILENAME "shared_file"
#define MESSAGE_SIZE 256

struct SharedData {
    int serverId;
    char message[MESSAGE_SIZE];
};

void serverProcess(int id) {
    int fd = open(FILENAME, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        std::cerr << "Failed to open the file" << std::endl;
        return;
    }

    ftruncate(fd, sizeof(SharedData));
    SharedData* sharedData = static_cast<SharedData*>(mmap(NULL, sizeof(SharedData), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));

    close(fd);

    int counter = 0;

    while (counter < 5) {
        sharedData->serverId = id;
        snprintf(sharedData->message, sizeof(sharedData->message), "Message from Server %d", id);

        std::cout << "Server " << id << ": Data written" << std::endl;
        sleep(2);
        counter++;
    }

    munmap(sharedData, sizeof(SharedData));
}

void clientProcess() {
    int fd = open(FILENAME, O_RDONLY);
    if (fd == -1) {
        std::cerr << "Failed to open the file" << std::endl;
        return;
    }

    SharedData* sharedData = static_cast<SharedData*>(mmap(NULL, sizeof(SharedData), PROT_READ, MAP_SHARED, fd, 0));

    close(fd);

    for (int i = 0; i < 10; ++i) {
        std::cout << "Client: Received from Server " << sharedData->serverId << ": " << sharedData->message << std::endl;
        sleep(1);
    }

    munmap(sharedData, sizeof(SharedData));
}

int main() {
    // Create two server processes
    if (fork() == 0) {
        serverProcess(1);
        exit(0);
    }

    if (fork() == 0) {
        serverProcess(2);
        exit(0);
    }

    // Create one client process
    if (fork() == 0) {
        clientProcess();
        exit(0);
    }

    // Wait for all child processes to complete
    for (int i = 0; i < 3; ++i) {
        wait(NULL);
    }

    return 0;
}
