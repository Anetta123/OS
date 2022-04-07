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
    while (quick_get(semaphore) < n){
        sem_post(semaphore);
    }
    while (quick_get(semaphore) > n){
        sem_wait(semaphore);
    }
}

int main(int args, char* argv[]){
    int fdAC[1];
    fdAC[0] = atoi(argv[0]);
    int fdBC[2];
    fdBC[1] = atoi(argv[1]);
    sem_t* semA = sem_open("_semA", O_CREAT, 0751, 1);
    sem_t* semB = sem_open("_semB", O_CREAT, 0751, 0);
    sem_t* semC = sem_open("_semC", O_CREAT, 0751, 0);
    while(1){
        while(quick_get(semC) == 0){
            continue;
        }
        if (quick_get(semC) == 2){
            break;
        }
        int size;
        string str;
        read(fdAC[0], &size, sizeof(int));
        int t = 0;
        for (int i = 0; i < size; ++i){
            char c;
            read(fdAC[0], &c, sizeof(char));
            str.push_back(c);
            t = i;
        }
        ++t;
        cout << str << endl;
        write(fdBC[1], &t, sizeof(int));
        quick_set(semB, 1);
        quick_set(semC, 0);
    }
    sem_close(semA);
    sem_close(semB);
    sem_close(semC);
    close(fdAC[0]);
    close(fdBC[1]);
    return 0;
} 
