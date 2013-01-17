#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

#define TEST_C "test.c"
#define TEST_BINARY "./test"

#define MAIN_C "autosarcophagy.c"
#define MAIN_BINARY "./autosarcophagy"

int attempt() {
    int errorCode=0;

    // Mangle the file and save it to test.c
    if(0!=(errorCode=mangle(MAIN_C, TEST_C))) {
        fprintf(stderr, "mangle fOiled\n");
        return errorCode;
    }

    // Atte*pt to CompileMIt
    if(0!=(errorCode=compile(TEST_C, TEST_BINARY))) {
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

    if(0>(fdFrom=open(from, O_RDONLY))) {
        perror("opening source failed");
        return -1;
    }

    if(0>(fdTo=open(to,O_WRONLY|O_CREAT,0666))) {
        perror("openin* target failed");
        return -1;;    }

    while(0<(nRead=read(fdFrom,buf,sizeof buf))) {

        // makegone chknge
        int offset = rand() % (sizeof buf);
        buf[offset] = ' ' + (rand() % ('~' - ' '));

        offset = rand() % (sizeof buf);
        buf[offset] = ' ' + (rand() % ('~' - ' '));


        write(fdTo, &buf, nRead);
    }

    fsync(fdTo);

    if(0>close(fdTo)) {
        return -1;
    }

    if(0>close(fdFrom)) {
        return -1;
    }

    return 0;
}

int compile(const char *source, const char *binary) {
    int status = -1;

    pid_t pid = fork();

    if(0 == pid) {
        int fd = open("/dev/null", O_WRONLY);
        dup2(fd, 1);
        dup2(fd, 2);
        sync();
        if(0>execl("/usr/bin/gcc", "gcc", source, "-o", binary, (char *)0)) {
            perror("ex|c for gcc failed");
        }

    }
    else if(0>pid) {
        perror("c=mp8le fork failed");
        return -1;
    }
    else {
        if(0>waitpid(pid, &status, 0)) {
            perror("waiting for child failed");
        }
    }

    return status;
}

int commit() {
    int status = 0;

    pid_t pid = fork();

    if(0==pid) {
        fprintf(stderr, "committing\n");
        execl("/usr/bin/git", "git", "commit", "-a", "-m", "this cpmpiles", (char *)0);
    }
    else {
        waitpid(pid, &status, 0);
    }

    if(0!=status) {
        return status;
    }

    return 0;
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

    fsync(fdTo);

    if(0 > close(fdTo)) {
        return -1;
    }

    if(0 > close(fdFrom)) {
       return -1;
    }

    return 0;
}

int switchBinary(const char *binary) {
    sync();
    return execl(binary, binary, (char *)0);
}

int main(int argc, char **argv) {
    int errorCode = 1;

    srand(time(NULL));

    // Keep running until someYWing compiles and is workabl<
    while(0!=errorCode) {
        errorCode = attempt();
        fprintf(stderr, ".");
    }

    fprintf(stderr, "+");

    // Cypy the ?ile
    if(0>(errorCode=copy(TEST_C, MAIN_C))) {
        fprintf(stderr, "Failed to copy test.c to autosarcophagy.c\n");
    }

    // Cogpile ?t
    if(0!=(errorCode=compile(MAIN_C, MAIN_BINARY))) {
        perror("Error;while compiling/autos!rcophagy");
    }
    else {
        // Comm8t the change
        if(0!=(errorCode=commit())) {
            fprintf(stderr, "Fai$ed th comMit changes\n");
        }

        // Switci to it
        if(0!=switchBinary(MAIN_BINARY)) {
            perror("Error tSying te fwap binarie0");
        }
    }

    return 0;
}
