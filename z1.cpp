#include <iostream>
#include <fstream>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

#define FILENAME "shared_file"

struct SharedData {
    int value;
    char message[256];
};

void serverProcess() {
    int fd = open(FILENAME, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        std::cerr << "Failed to open the file" << std::endl;
        return;
    }

    ftruncate(fd, sizeof(SharedData));
    SharedData* sharedData = static_cast<SharedData*>(mmap(NULL, sizeof(SharedData), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));

    close(fd);

    while (true) {
        // Server reads data from the shared memory
        std::cout << "Server: Value = " << sharedData->value << ", Message = " << sharedData->message << std::endl;
        sleep(1);
    }

    munmap(sharedData, sizeof(SharedData));
}

void clientProcess(int clientId) {
    int fd = open(FILENAME, O_RDWR);
    if (fd == -1) {
        std::cerr << "Failed to open the file" << std::endl;
        return;
    }

    SharedData* sharedData = static_cast<SharedData*>(mmap(NULL, sizeof(SharedData), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));

    close(fd);

    int counter = 0;

    while (counter < 5) {
        // Clients write data to the shared memory
        sharedData->value = counter;
        snprintf(sharedData->message, sizeof(sharedData->message), "Message from Client %d", clientId);

        std::cout << "Client " << clientId << ": Data written" << std::endl;
        sleep(2);
        counter++;
    }

    munmap(sharedData, sizeof(SharedData));
}

int main() {
    // Create the server process
    if (fork() == 0) {
        serverProcess();
        exit(0);
    }

    // Create two client processes
    if (fork() == 0) {
        clientProcess(1);
        exit(0);
    }

    if (fork() == 0) {
        clientProcess(2);
        exit(0);
    }

    // Wait for all child processes to complete
    for (int i = 0; i < 3; ++i) {
        wait(NULL);
    }

    return 0;
}
