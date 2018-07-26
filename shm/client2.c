#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>

int main() {
    key_t key;
    char path[] = "../test/test.c";
    int ascii = 't';
    if((key = ftok(path, ascii)) < 0){
        printf("Can\'t generate key\n");
        return -1;
    }
    printf("%d\n", key);
    int id;
    if ((id = shmget(key, sizeof(char) * 32, 0)) < 0) {
	printf("Can\'t find shared memory\n");
        return -1;
    }
    char *str = (char *)shmat(id, NULL, 0);
    char send[] = "Hello, too!";
    char resv[] = "Hello!";
    while (strcmp(str, resv));
    strcpy(str, send);
    shmdt(str);
    return 0;
}
