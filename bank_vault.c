#include <stdio.h>
#include <string.h>
#include <encrypt.h>
#include <checksum.h>

int main(int argc, char **argv) {
  char message[] = "Hello world\n";

  printf("Original: %s\n", message);
  encrypt(message);
  printf("Encrypted: %s\n", message);
  printf("Checksum: %i\n", checksum(message));
}

