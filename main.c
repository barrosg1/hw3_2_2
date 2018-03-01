#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <getopt.h>

// sum of numbers from -100 to 100
void* sumOfNums(void* arg);

int numOfThreads;
int sum = 0;

int main(int argc, char *argv[]) {
    if(argc < 3)
    {
        puts("Insufficient arguments");
        return 0;
    }
    else
    {
        int opt;
        while((opt = getopt(argc, argv, "n:")) != -1) {
            switch(opt) {
                case 'n':
                    numOfThreads = atoi(optarg);
                    break;
                case ':':
                    printf("option needs a value\n"); break;
                case '?':
                    printf("unknown option: %c\n", optopt); break;
            }
            
        }
        
        // thread ID
        pthread_t tid;
        
        // create the thread
        pthread_create(&tid, NULL, sumOfNums, &numOfThreads);
        
        // wait until thread is finished
        pthread_join(tid, NULL);
        
        printf("Sum: %d\n", sum);
    }
    
    return 0;
}

void* sumOfNums(void* arg)
{
    
    int* numOfThreads = (int*) arg;
    int totalNumOfThreads = *numOfThreads;
    
    int i;
    for(i=0; i < totalNumOfThreads; i++)
        sum+=1;

    pthread_exit(0);
}





