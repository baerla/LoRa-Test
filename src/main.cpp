#include "mbed.h"
#include "PinMap2.h"
#include "LoRa.h"

int main() { 
    printf("Starting LoRa\n");

    LoRa loRa = LoRa();
    loRa.LoRaSend();
}
