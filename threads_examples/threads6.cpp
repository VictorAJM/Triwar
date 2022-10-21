#include <pthread.h>
#include <iostream>

void *functionC(void *ptr);
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int  counter = 0;

int main()
{
   int rc1, rc2;
   pthread_t thread1, thread2;

   /* Create independent threads each of which will execute functionC */

   if( (rc1==pthread_create( &thread1, NULL, &functionC, NULL)) )
   {
     std::cout<<"Thread creation failed 1"<<std::endl;
   }

   if( (rc2==pthread_create( &thread2, NULL, &functionC, NULL)) )
   {
      std::cout<<"Thread creation failed 2"<<std::endl;
   }

   /* Wait till threads are complete before main continues. Unless we  */
   /* wait we run the risk of executing an exit which will terminate   */
   /* the process and all threads before the threads have completed.   */

   pthread_join( thread1, NULL);
   pthread_join( thread2, NULL); 

   return 0;
}

void *functionC( void *ptr)
{
   pthread_mutex_lock( &mutex1 );
   counter++;
   //printf("Counter value: %d\n",counter);
   std::cout<<"Counter value: "<<counter<<std::endl;
   pthread_mutex_unlock( &mutex1 );
}