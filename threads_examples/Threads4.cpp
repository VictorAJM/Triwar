#include <pthread.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;

char thread_msg[] = "Hello thread!!";

void *thread_fnc(void *arg){
    cout<<"This is a thread function, ags is "<<(char*)thread_msg<<endl;
    strcpy(thread_msg,"Bye!");
}

int main(){
    int res;
    pthread_t my_thread;
    void *ret_join;
    res = pthread_create(&my_thread,NULL,thread_fnc,(void*) thread_msg);
    if(res != 0){
        cout<<"Error: pthread_create() failed"<<endl;
        exit(EXIT_FAILURE);
    }
    cout<<"Running in main thread"<<endl;
    res = pthread_join(my_thread,&ret_join);
    if(res != 0){
        cout<<"Error: pthread_join() failed"<<endl;
        exit(EXIT_FAILURE);
    }
    cout<<"Thread joined, it returned: "<< (char *) ret_join <<endl;
    cout<<"New thread message "<<thread_msg<<endl;
    
    return 0;
}
