#include <pthread.h>
#include <iostream>

using namespace std;

void *worker(void *arg){
    cout<<"This is the worker thread()"<<endl;
    pthread_exit(NULL);
}

int main(){

    pthread_t my_thread;
    int res =0;

    cout<<"In main thread: running..."<<endl;
    res = pthread_create(&my_thread,NULL,&worker,NULL);
    cout<<res<<endl;
    if(res != 0){
        cout<<"Error: pthread_create() failed"<<endl;
        exit(EXIT_FAILURE);
    }
    cout<<"In main thread: running..."<<endl;
    pthread_exit(NULL);   
    
    return 0;
}
