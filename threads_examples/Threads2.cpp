#include <pthread.h>
#include <iostream>

#define N 5

using namespace std;

void *worker(void *arg){
    cout<<"This is the worker thread()"<< (long)arg <<endl;
    pthread_exit(NULL);
}

int main(){

    pthread_t my_thread[N];
    long id;


    for( int id = 1; id<5; id++){
         int res = pthread_create(&my_thread[id],NULL,&worker,(void*)id);
         if(res != 0){
            cout<<"Error: pthread_create() failed"<<endl;
            exit(EXIT_FAILURE);
         }
    }

    /*
    cout<<"In main thread: running..."<<endl;
    res = pthread_create(&my_thread,NULL,&worker,NULL);
    if(res != 0){
        cout<<"Error: pthread_create() failed"<<endl;
        exit(EXIT_FAILURE);
    }
    cout<<"In main thread: running..."<<endl;
    pthread_exit(NULL);
    */   
   
    pthread_exit(NULL);
    return 0;
}
