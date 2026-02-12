#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define LED0 (1)
#define LED1 (1 << 1) // 10
#define BP (1 << 2) // 100

int main() {
    int fd = open("/dev/driver_CD", O_RDWR);
    if(fd < 0) return 1;

    write(fd, "11", 2); // devrait allumer les 2 leds

    int values[3];
    read(fd, values, LED0 | LED1 | BP);
    printf("LED0 = %d, LED1 = %d, BP = %d\n", values[0], values[1], values[2]);

    write(fd, "00", 2); // devrait éteindre les 2 leds

    read(fd, values, LED0 | LED1 | BP);
    printf("LED0 = %d, LED1 = %d, BP = %d\n", values[0], values[1], values[2]);

    write(fd, "10", 2); // devrait allumer la led 0

    read(fd, values, LED0 | LED1 | BP);
    printf("LED0 = %d, LED1 = %d, BP = %d\n", values[0], values[1], values[2]);

    close(fd);
    return 0;
}