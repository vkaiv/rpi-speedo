#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "speedo.h"
#include "display.h"

int main() {
    float dl_speed = 0.0;
    float ul_speed = 0.0;
    initSSD1306();

    while(1) {
        getNetworkSpeed(&dl_speed, &ul_speed);
        
        if (dl_speed >= 1000 && dl_speed <= 1000000) {
            dl_speed /= 1000;
            writeDownload(dl_speed);
            writeUnit(true, true);
            
        } else if (dl_speed > 1000000){
            dl_speed /= 1000000;
            writeDownload(dl_speed);
            writeUnit(false, true);
        } else {
            dl_speed /= 1000;
            writeDownload(dl_speed);
            writeUnit(true, true);
        }

        if (ul_speed >= 1000 && ul_speed <= 1000000) {
            ul_speed /= 1000;
            writeUpload(ul_speed);
            writeUnit(true, false);
            
        } else if (ul_speed > 1000000) {
            ul_speed /= 1000000;
            writeUpload(ul_speed);
            writeUnit(false, false);
        } else {
            ul_speed /= 1000;
            writeUnit(true, false);
            writeUpload(ul_speed);
        }
        
        // printf("\rDL: %.1f UL: %.1f", dl_speed, ul_speed);
        // fflush(stdout);
        sleep(2);
    }

    return 0;
}