#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int count = 5;
void* agentfn(void *arg);
void* smokerfn(void *arg);

sem_t myagent;
sem_t sems[3];

const char* item_names[3] = {"Tobacco", "Paper", "Matches"};

void* agentfn(void *arg){
    while(count > 0){
        // main orchestration
        sem_wait(&myagent);
        int r = rand() % 3;
        int a = (r+1)%3; 
        int b = (r+2)%3; 
        printf("Agent placing items %s and %s for the [smoker %d] which has [%s]\n", item_names[a], item_names[b], r, item_names[r]);
        // let the smoker smoke
        sem_post(&sems[r]);
        sleep(1);
        count--;
    }
    for(int i=0; i<3; i++) sem_post(&sems[i]);
    return NULL;
}

void* smokerfn(void *arg){
    int id = *(int *)arg;
    while(1){
        // get into the smoking room
        sem_wait(&sems[id]);
        // if count 0 cancel the smoker
        if(count == 0) {
            printf("Smoker %i is cancelling...\n", id);
            break;
        };
        printf("Smoker %i is smoking...\n", id);
        sleep(1);
        // get out of the smoking room
        sem_post(&myagent);
    }
    return NULL;
}

int main(){ 
    pthread_t agentthread, smokerthread[3];
    // ids for the smokers 
    int ids[3] = {0,1,2};

    // initiailzing the sems
    sem_init(&myagent, 0, 1);
    for(int i=0; i<3; i++) sem_init(&sems[i], 0, 0);
    
    // creating the threads..........
    pthread_create(&agentthread, NULL, agentfn, NULL);
    for(int i=0; i<3; i++) pthread_create(&smokerthread[i], NULL, smokerfn, &ids[i]);
    
    // Make main wait for threads :)
    pthread_join(agentthread, NULL);
    for(int i=0; i<3; i++) pthread_join(smokerthread[i], NULL);
    return 0;
}