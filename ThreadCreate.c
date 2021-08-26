#include <stdio.h>
#include <pthread.h>
void* print_value(void*);

int main(){
  	pthread_t id;
  	int j = 1;
  	pthread_create(&id, NULL, print_value, &j);
  	int *ptr;
  	pthread_join(id, (void**)&ptr);
  	printf("\nExit Status of the Thread: %d\n", *ptr);
  	j = *ptr;
  	int ul = j+10;
  	for ( ; j < ul; j++)
		printf("%d ", j);
	printf("\n\n");
}
void* print_value(void* p){
  	int i = * (int*)p;
  	int ul = i+10;
	printf("\nNew Thread received: %d\n", i);
  	for ( ; i < ul; i++)
      	printf("%d ", i);
  	printf("\n");
  	*(int*)p= i;
}