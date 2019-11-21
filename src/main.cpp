#include "mbed.h"
#include "PinMap2.h"
#include "LoRa.h"

int main() { 
    Serial pcSerial(USBTX, USBRX);

    pcSerial.printf("Starting LoRa");

    LoRa loRa = LoRa();
    loRa.LoRaSend();
}
