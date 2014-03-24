#include <stdio.h>

struct meal {
  const char *ingredients;
  float weight;
};

struct exercise {
  const char *description;
  float duration;
};

struct preferences {
  struct meal food;
  struct exercise exercise;
};

struct fish {
  const char *name;
  const char *species;
  int teeth;
  int age;
  struct preferences care;
};

void catalog_line(const char *property, const char *value) {
  printf("Catalog %s: %s\n", property, value);
}

void catalog(struct fish f) {
  catalog_line("Name", f.name);
  catalog_line("Species", f.species);
  catalog_line("Food ingredients", f.care.food.ingredients);
  catalog_line("Exercise description", f.care.exercise.description);
  printf("\n");
}

int main(int argc, char **argv) {
  struct fish snappy = { "Snappy", "Piranha", 69, 4,
      {
          { "Other fish", 5},
          { "Chewing vigorously", 30}
      }
  };

  catalog(snappy);
  printf("\n");
  return 0;

}

