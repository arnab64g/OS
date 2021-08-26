#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>

void *process_t(void*);
pthread_mutex_t mutex[5];
int main() {
    for (int i = 0; i < 5; i++)
        pthread_mutex_init(&mutex[i], NULL);
    pthread_t id[3];
    char *j[15] = {"Red", "Green", "Blue"};
    for (int i = 0; i < 3; i++){
        printf("\nProcess Created: %s\n", j[i]);
        pthread_create(&id[i], NULL, process_t,  j[i]);
    }
    sleep(6);
    for (int i = 0; i < 3; i++){
        void *ptr;
        pthread_join(id[i], NULL);
    }
    
    printf("Threads joined\n");
}
void *process_t(void* p) {
    int inst;
    for (int i = 0; i < 5; i++){
        inst = i;
        pthread_mutex_lock(&mutex[inst]);
        printf("Locked(%5s, R%d) ",  p, inst+1);
        sleep(0.2);
        pthread_mutex_unlock(&mutex[inst]);
        printf("unlocked(%5s, R%d)\n", p, inst+1);
    }
}
