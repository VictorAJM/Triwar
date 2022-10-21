#include <pthread.h>
#include <iostream>

using namespace std;

void *worker(void *arg){
    cout<<"This is the worker thread()"<<endl;
    pthread_exit((void*)500);
}


int main(){
    int i;
    cout<<"In main thread: running..."<<endl;
    pthread_t thread;
    pthread_create(&thread,NULL,worker,NULL);
    pthread_join(thread,(void**)&i);
    cout<<i<<endl;
    cout<<"In main thread: running..."<<endl;
    return 0;
}