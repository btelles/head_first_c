#include <stdio.h>

typedef struct island {
  char *name;
  char *opens;
  char *closes;
  struct island *next;
} island;


int main(int argc, char **argv) {

  island amity = { "Amity", "09:00", "17:00", NULL};
  island craggy = { "Craggy", "09:00", "17:00", NULL};
  island isla_nublar = { "Isla Nublar", "09:00", "17:00", NULL};
  island skull = { "Skull", "09:00", "17:00", NULL};
  island shutter = { "Shutter", "09:00", "17:00", NULL};

  amity.next = &craggy;
  craggy.next = &isla_nublar;
  isla_nublar.next = &shutter;

  skull.next = isla_nublar.next;
  isla_nublar.next = &skull;

  island *current_island = &amity;

  printf("Starting at %s.\n", current_island->name);

  while(current_island->next) {
    current_island = current_island->next;
    printf("Then stopping at %s.\n", current_island->name);
  }
}
