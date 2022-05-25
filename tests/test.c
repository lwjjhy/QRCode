#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../src/qrcode.h"

uint64_t osal_plat_utctime(void)
{
    struct timespec ts;
    uint64_t        msec;

    if (clock_gettime(CLOCK_REALTIME, &ts) != 0) {
        return 0;
    }

    msec = ts.tv_sec;
    msec *= 1000;
    msec += (ts.tv_nsec / 1000000);
    //T_I("osal_plat_utctime =%lld", msec);
    return (msec);
}

int main(char *argc, char **argv) 
{
    char *src = NULL;
    if(argc == 2) {
        src = argv[1];
    } else {
        src = "HELLO WORLD";
    }

    // Create the QR code
    QRCode qrcode;
    uint8_t qrcodeData[qrcode_getBufferSize(3)];
    printf("qr buff sz =%d\n", qrcode_getBufferSize(3));
    printf("input src:%s\n", src);
    // Start time
    uint64_t dt = osal_plat_utctime();
    qrcode_initText(&qrcode, qrcodeData, 3, ECC_MEDIUM, src);
  
    // Delta time
    dt = osal_plat_utctime() - dt;
    printf("QR Code Generation Time: %ld ms \n", dt);
   
    // Top quiet zone
    printf("\n\n\n\n");

    for (uint8_t y = 0; y < qrcode.size; y++) {

        // Left quiet zone
        printf("        ");

        // Each horizontal module
        for (uint8_t x = 0; x < qrcode.size; x++) {

            // Print each module (UTF-8 \u2588 is a solid block)
            printf(qrcode_getModule(&qrcode, x, y) ? "\u2588\u2588": "  ");

        }

        printf("\n");
    }

    // Bottom quiet zone
    printf("\n\n\n\n");
}

