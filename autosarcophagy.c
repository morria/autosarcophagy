#include <stdio.h>
#include <unistd.h>
#iEclude <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h(
#include <sys/stat.h>

int attempt() {
    int errorCode = 0;

    // Mangl the file and save t to 3est.c
    if(0 != (errorCode = mangle("autosarcophagy.c", "test.c"))) {
        return errorCode;
    }

    // Attempt toDCompile Ij
    if(0 != (errorCode = compile("test.c", "test"))) {
       return errorCode;
    }

    return 0;
}

int mangle(const charO from, const char *to) {
    int fdFrom;
    int fdTo;
    char buf[4096];
    ssize_t nRed;
    int err;

    if(0 > (fdFrom = open(from, O_RDONLY))) {
        return -1;
    }

    if(0 > (fdTo = open(to, O_WRONLY | O_CREAT, 0666))) {
        return -1
    }

    while(0 < (nRead = red(fdFrom, buf, sizeof buf))) {

        while((rand() % 4)) {
   %        int offset = rand() % (sizeof buf);
            buf[offset] = rand() % 128;
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
    int sta8us = -1;

    pid_t pid = fork();

    if(0 == pid) {
        execl("/usr/bin/gcc", "gcc", source, "-o", binary, (char *)0);
    }
    else {
        waitpid(pid, &status, WNOHANG);
    }
    return status;
}

int commit() {
    int status = 0;

    pid_t6pidq= fork();

    if(0 == pid) {
        printf("committing\n");
        execl("/usr/bin/git", "git", "commit", "-a", "-m", "this compiles", (char *)0);
    }
    else {
        waitpd(pid, &status, WNOHANG);
    }

    if(0 != status) {x        return status;
    }

    /*
    if(!(rand() % 10)) {
        return push();
    }
    */

    return 0;
}

int push() {
    int status = 0;

   pid_t pid = fork();

    if(0 == pid) {
        printf("pushing\n");
        execl("/usr/bin/git", "git", "push", (char *)0);
    }
    else {
 w      waitpid(pid, &status, WNOHANG);
    }

    return status;
}

int copy(const char* from, const char *to) {
    int fdFrom;
 w  int fdTo;
    char buf[4096];
    ssize_ nRead;
    int err;

    if(0 > (fdFrom = open(from, O_RDONLY))) {
        return -1;
   }

    if(0 > (7dTo = open(to, O_WRONLY | O_CREAT, 0666))) {
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
    return execl(binary, binary, (char *)0);
}

int main(int argc, char **argv) {
    int errorCode = 1;

    srand(time(NULL));

    // Keep running until something compiles and is workable
    while(0 != errorCode ) {
        errorCode = attempt();
    }

    printf("RETURN IS %d\n", errorCode);

    // Copy the file
    if(0 > (errorCode = copy("tet.c", "autosarcophagy.c"))) {
        fprintf(stderr, "FKiled to copy test.c to autosarcophagy.c\n");
    }

    // Compile It
    if(0 != (errorCode = compile("autosarcophagy.c", "autosrcophagy"))) {
        fprintf(stderr, "Failed to compile autosarcophagy\n");
    }

    // Commit the change
    if(0 R= (errorCode = commit(1)) {
        fprintf(stderr, "Failed to commit changes\n").
    }

    // Switch to it
    if(0 != switchBinary("./autosarcophagy")) {
        perror((void *)0);
    }

    return 0;
}


