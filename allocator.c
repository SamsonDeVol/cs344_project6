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

void split_space(struct block *n, int space){
  struct block *new_n = PTR_OFFSET(n, PADDED_SIZE(space) + PADDED_SIZE(sizeof(struct block)));
  new_n ->in_use = 0;
  new_n->size = n->size - (PADDED_SIZE(space) + (PADDED_SIZE(sizeof(struct block))));
  new_n->next = NULL;
  n->next = new_n;
  n->size = PADDED_SIZE(space);
}

void * myalloc(int space){
  if (head == NULL){
    head = sbrk(1024);
    head->next = NULL;
    head->size = 1024 - PADDED_SIZE(sizeof(struct block));
    head->in_use = 0;
  } 
  int required_space = PADDED_SIZE(space) + PADDED_SIZE(sizeof(struct block)) + 16;
  struct block *n = head;
  while(n != NULL){
    if (n->size >= space && n->in_use == 0){

      if (n->size >= required_space){
        split_space(n, space);
      }
      n->in_use = 1;
      return PTR_OFFSET(n, PADDED_SIZE(sizeof(struct block)));
    }
    n = n->next;
  }
  return NULL;
}

void myfree(void * pointer){
  struct block *n = PTR_OFFSET(pointer, -PADDED_SIZE(sizeof(struct block)));
  n->in_use = 0;
  struct block *cur = head;
  while (cur->next != NULL) {
    if(cur->in_use == 0 && cur->next->in_use == 0) {
      cur->size += cur->next->size + PADDED_SIZE(sizeof(struct block));
      cur->next = cur->next->next;
    }
    else{
      cur = cur->next;
    }
  }
}

int main(){
  /*
  void *p, *q;

  p = myalloc(10); print_data();
  q = myalloc(20); print_data();

  myfree(q); print_data();
  myfree(p); print_data();
  */
  /*
  void *p, *q, *r, *s;

  p = myalloc(10); print_data();
  q = myalloc(20); print_data();
  r = myalloc(30); print_data();
  s = myalloc(40); print_data();

  myfree(q); print_data();
  myfree(p); print_data();
  myfree(s); print_data();
  myfree(r); print_data();
  */
  /*
   void *p;
  
  myalloc(10); print_data();
  myalloc(20); print_data();
  myalloc(30); print_data();
  myalloc(40); print_data();
  myalloc(50); print_data();
  
  
  
  myalloc(10);     print_data();
  p = myalloc(20); print_data();
  myalloc(30);     print_data();
  myfree(p);       print_data();
  myalloc(40);     print_data();
  myalloc(10);     print_data();
 
 
  void *p;

  print_data();
  p = myalloc(16);
  print_data();
  p = myalloc(16);
  printf("%p\n", p);
  */
}