/*
 * Copyright (c) 2018 HELIOS Software GmbH
 * 30826 Garbsen (Hannover) Germany
 * Licensed under the Apache License, Version 2.0);
 */
 #include "main.h"


DigitalOut led(LED);


int main() { 
    /*
     * inits the Serial or USBSerial when available (230400 baud).
     * If the serial uart is not is not connected it swiches to USB Serial
     * blinking LED means USBSerial detected, waiting for a connect.
     * It waits up to 30 seconds for a USB terminal connections 
     */
    InitSerial(30*1000, &led);
    dprintf("Welcome to the SX1276GenericLib");
  
    dprintf("Starting a simple LoRa PingPong");

    LoRa();
}
