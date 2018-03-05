#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <getopt.h>

int numOfThreads;

typedef struct sum_args
{
    int sum;
    
} Sum;

void *sumOfNums(void * arg)
{
    
    int sum = 0;
    int* randNum_ptr = (int*) arg;
    Sum *arg_struct = (Sum*) arg;
    
    printf("%d\n", *randNum_ptr);
    
    int i;
    for(i=0; i < numOfThreads; i++)
    {
        sum+=i;
    }
    
    arg_struct->sum = sum;
    
    pthread_exit(0);
}

int main(int argc, char *argv[])
{
    
    int opt, ret, i;
    Sum args;
    
    pthread_t threads[numOfThreads];
    
    
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
    
    unsigned int seed = (unsigned int)time(NULL);
    
    for(i=0;i<numOfThreads;i++){
        int randomNum = rand_r(&seed) % 201 + (-100);
        ret = pthread_create(&threads[i], NULL, sumOfNums, &randomNum);
        
        if (ret){
            printf("ERROR; return code from pthread_create() is %d\n", ret);
            exit(-1);
        }
    }
    
    for(i=0;i<numOfThreads;i++){
        pthread_join(threads[i], NULL);
    }
    
    printf("Sum: %d\n", args.sum);
    
    
    return 0;
}





