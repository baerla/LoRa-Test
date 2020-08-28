#include "mbed.h"
#include "LoRa.h"

ChannelLoRa<SX1276Generic> loraInstance;

int main()
{
    printf("Starting LoRa\n");
    loraInstance.setup();

    return 0;
}
