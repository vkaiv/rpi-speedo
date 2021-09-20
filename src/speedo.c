#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include "speedo.h"

FILE* RX_bytes_file;
FILE* TX_bytes_file;

void getNetworkSpeed(float* dl, float* ul) {
    static unsigned long RX_bytes_count = 0;
    static unsigned long TX_bytes_count = 0;

    static struct timeval tval_current = { 0, 0 };
    struct timeval tval_last, tval_result;
    
    unsigned long RX_bytes_last;
    unsigned long TX_bytes_last;

    // save the previous reading
    RX_bytes_last = RX_bytes_count;
    TX_bytes_last = TX_bytes_count;
    tval_last = tval_current;

    // received bytes
    if ((RX_bytes_file = fopen("/sys/class/net/wlan0/statistics/rx_bytes", "r")) == NULL) {
        printf("Error opening rx_bytes\n");
        exit(1);
    }
    // transmitted bytes
    if ((TX_bytes_file = fopen("/sys/class/net/wlan0/statistics/tx_bytes", "r")) == NULL) {
        printf("Error opening tx_bytes\n");
        exit(1);
    }

    // time of reading the rx & tx data saved to tval_current
    gettimeofday(&tval_current, NULL);

    // read the number of transferred bytes
    fscanf(RX_bytes_file, "%lu", &RX_bytes_count);
    fscanf(TX_bytes_file, "%lu", &TX_bytes_count);

    fclose(RX_bytes_file);
    fclose(TX_bytes_file);

    // subtract tval_current from tval_last
    timersub(&tval_current, &tval_last, &tval_result);
    // elapsed time in seconds
    float elapsed_time = tval_result.tv_sec + (tval_result.tv_usec / 1000000.0);

    // the amount of bytes transferred since last reading
    long diff_RX_bytes = RX_bytes_count - RX_bytes_last;
    long diff_TX_bytes = TX_bytes_count - TX_bytes_last;


    if ( diff_RX_bytes == 0 ) {
        *dl = 0.0;
    } else {
        *dl = diff_RX_bytes / elapsed_time;
    }

    if ( diff_TX_bytes == 0) {
        *ul = 0.0;
    } else {
        *ul = diff_TX_bytes / elapsed_time;
    }

}