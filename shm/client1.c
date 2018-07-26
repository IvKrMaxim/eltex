#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main() {
    key_t key;
    char *path = "../test/test.c";
    int ascii = 't';
    if ((key = ftok(path, ascii)) < 0) {
	printf("Can\'t generate key\n");
        return -1;
    }
    int id;
    printf("%d\n", key);
    if ((id = shmget(key, sizeof(char) * 32, IPC_EXCL | IPC_CREAT | 0666)) < 0) {
        printf("Can\'t create shared memory\n");
        return -1;
    }
    char *str = (char *)shmat(id, NULL, 0);
    char send[] = "Hello!";
    strcpy(str, send);
    char resv[] = "Hello, too!";
    while (strcmp(str, resv));
    printf("%s\n", str);
    shmdt(str);
    shmctl(id, IPC_RMID, 0);
    return 0;
}
