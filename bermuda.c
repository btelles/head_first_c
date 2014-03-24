#include <stdio.h>

int main()
{
  float latitude;
  float longitude;
  char info[80];
  while (scanf("%f,%f,%79[^\n]", &latitude, &longitude, info) == 3) {
    if (longitude > -76 && longitude < -64) {
      if (latitude > 26 && latitude < 34)
        printf("%f,%f,%s\n", latitude, longitude, info);
    }
  }
  return 0;
}
