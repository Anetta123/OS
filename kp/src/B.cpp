#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
using namespace std;

int quick_get(sem_t *semaphore){
    int s;
    sem_getvalue(semaphore, &s);
    return s;
}

void quick_set(sem_t *semaphore, int n){
    while (quick_get(semaphore) < n)
    {
        sem_post(semaphore);
    }
    while (quick_get(semaphore) > n)
    {
        sem_wait(semaphore);
    }
}

int main(int args, char* argv[]){
    int fdAB[1];
    fdAB[0] = atoi(argv[0]);
    int fdBC[1];
    fdBC[0] = atoi(argv[1]);
    sem_t* semA = sem_open("_semA", O_CREAT, 0751, 1);
    sem_t* semB = sem_open("_semB", O_CREAT, 0751, 0);
    sem_t* semC = sem_open("_semC", O_CREAT, 0751, 0);
    while (1){
        while(quick_get(semB) == 0){
            continue;
        }
        if (quick_get(semB) == 2){
            break;
        }
        int size;
        read(fdAB[0], &size, sizeof(int));
        cout << "Number of input symbols is " << size << endl;
        quick_set(semC, 1);
        quick_set(semB, 0);
        while (quick_get(semB) == 0){
            continue;
        }
        if (quick_get(semB) == 2){
            break;
        }
        read(fdBC[0], &size, sizeof(int));
        cout << "Number of output symbols is " << size << endl;
        quick_set(semA, 1);
        quick_set(semB, 0);
        while(quick_get(semB) == 0){
            continue;
        }
        if (quick_get(semB) == 2){
            break;
        }
    }
    sem_close(semA);
    sem_close(semB);
    sem_close(semC);
    close(fdAB[0]);
    close(fdBC[0]);
    return 0;
}
