#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    int errorCode = 0;

    // Keep running until something compiles
    while(0 > attempt());

    // Copy the file
    if(0 > (errorCode = copy("test.c", "autosarcophagy.c"))) {
        fprintf(stderr, "Failed to copy test.c to autosarcophagy.c\n");
    }

    // Attempt to Compile It
    if(0 != (errorCode = compile("autosarcophagy.c", "autosarcophagy"))) {
        fprintf(stderr, "Failed to compile autosarcophagy\n");
    }

    // Switch to it
    if(0 != switchBinary("./autosarcophagy")) {
        perror((void *)0);
    }

    return 0;
}

int attempt() {
    int errorCode = 0;

    // Mangle the file and save it to test.c
    if(0 > (errorCode = mangle("autosarcophagy.c", "test.c"))) {
        return errorCode;
    }

    // Attempt to Compile It
    if(0 != (errorCode = compile("test.c", "test"))) {
        return errorCode;
    }

    return 0;
}

int mangle(const char* from, const char *to) {
    int fdFrom;
    int fdTo;
    char buf[4096];
    ssize_t nRead;
    int err;

    if(0 > (fdFrom = open(from, O_RDONLY))) {
        return -1;
    }

    if(0 > (fdTo = open(to, O_WRONLY | O_CREAT, 0666))) {
        return -1;
    }

    while(0 < (nRead = read(fdFrom, buf, sizeof buf))) {

        while((rand() % 3)) {
            int offset = rand() % (sizeof buf);
            buf[offset] = rand() % 128;
            printf("Set %d to %c\n", offset, buf[offset]);
        }

        write(fdTo, &buf, nRead);
    }

    if(0 > close(fdTo)) {
        return -1;
    }

    if(0 > close(fdFrom)) {
        return -1;
    }

    return 0;
}

int compile(const char *source, const char *binary) {
    int status = 0;

    pid_t pid = fork();

    if(0 == pid) {
        execl("/usr/bin/gcc", "gcc", source, "-o", binary, (char *)0);
    }
    else {
        waitpid(pid, &status, WNOHANG);
    }

    return status;
}

int copy(const char* from, const char *to) {
    int fdFrom;
    int fdTo;
    char buf[4096];
    ssize_t nRead;
    int err;

    if(0 > (fdFrom = open(from, O_RDONLY))) {
        return -1;
    }

    if(0 > (fdTo = open(to, O_WRONLY | O_CREAT, 0666))) {
        return -1;
    }

    while(0 < (nRead = read(fdFrom, buf, sizeof buf))) {
        write(fdTo, &buf, nRead);
    }

    if(0 > close(fdTo)) {
        return -1;
    }

    if(0 > close(fdFrom)) {
        return -1;
    }

    return 0;
}

int switchBinary(const char *binary) {
    fprintf(stderr, "Switching to new binary\n");
    return execl(binary, binary, (char *)0);
}
