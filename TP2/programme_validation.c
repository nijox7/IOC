#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define LED0 (1) // 0b1
#define LED1 (1 << 1) // 0b10
#define BP (1 << 2) // 0b100

void print(int fd, int *values) {
    read(fd, values, LED0 | LED1 | BP);
    printf("BP = %d, LED0 = %d, LED1 = %d\n", values[0], values[1], values[2]);
}

int main() {
    // ouverture
    int values[3];
    int fd = open("/dev/driver_CD", O_RDWR);
    if(fd < 0) return 1;

    // éteint les 2 leds
    write(fd, "00", 2);
    print(fd, values); // affichage des valeurs (2 leds allumées)
    sleep(2);

    // allume les 2 leds
    write(fd, "11", 2);
    print(fd, values); // affichage des valeurs (2 leds allumées)
    sleep(2);

    // éteint la led1
    write(fd, "10", 2);
    print(fd, values);
    sleep(2);

    // éteint led0, allume led1
    write(fd, "01", 2);
    print(fd, values);
    sleep(2);

    close(fd);
    return 0;
}