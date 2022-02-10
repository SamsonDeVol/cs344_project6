// Samson Devol, cs 344 project6, 2/8/2022

#include "allocator.h"

struct block *head = NULL;

void print_data(void)
{
    struct block *b = head;

    if (b == NULL) {
        printf("[empty]\n");
        return;
    }

    while (b != NULL) {
        // Uncomment the following line if you want to see the pointer values
        //printf("[%p:%d,%s]", b, b->size, b->in_use? "used": "free");
        printf("[%d,%s]", b->size, b->in_use? "used": "free");
        if (b->next != NULL) {
            printf(" -> ");
        }

        b = b->next;
    }

    printf("\n");
}

int myalloc(int space){
  if (head == NULL){
    head = sbrk(1024);
    head->next = NULL;
    head->size = 1024 - PADDED_SIZE(sizeof(struct block));
    head->in_use = 0;
  } 
  struct block *n = head;

  while(n != NULL){

    if (n->size > space){
      n->in_use = 1;
      printf("Here mothafucka: %d", n);
      return &n;
      
    }
  }

  return NULL;
}
int main(){
  void *heap = sbrk(1024);
  
  void *p;

  //print_data();
  //p = myalloc(64);
  //printf("head after alloc: %d", head->size);
  //p = myalloc(64);
  //print_data();


    print_data();
    p = myalloc(16);
    print_data();
    p = myalloc(16);
    printf("%p\n", p);
}