#ifndef __LoRa_H
#define __LoRa_H

#include "mbed.h"
#include "sx1276-mbed-hal.h"
#include "rtos/ThisThread.h"
#include "PinMap2.h"

uint32_t RX_TIMEOUT = 100;

enum event_t
{
    EV_NONE,
    EV_TX_DONE,
    EV_TX_TIMEOUT,
    EV_RX_DONE,
    EV_RX_TIMEOUT,
    EV_RX_ERROR,
};
static volatile event_t received_event;

static void tx_done(void *radio, void *userThisPtr, void *userData)
{
    received_event = EV_TX_DONE;
}

static void tx_timeout(void *radio, void *userThisPtr, void *userData)
{
    received_event = EV_TX_TIMEOUT;
}

static void rx_done(void *radio, void *userThisPtr, void *userData, uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr)
{
    received_event = EV_RX_DONE;
}

static void rx_timeout(void *radio, void *userThisPtr, void *userData)
{
    received_event = EV_RX_TIMEOUT;
}

static void rx_error(void *radio, void *userThisPtr, void *userData)
{
    received_event = EV_RX_ERROR;
}

    template <class RadioClass>
    class ChannelLoRa
{
public:
    ChannelLoRa() : radio(&radio_callbacks, SX1276MB1MAS,
                          LORA_SPI_MOSI, LORA_SPI_MISO, LORA_SPI_SCLK, LORA_CS, LORA_RESET,
                          LORA_DIO0, LORA_DIO1, LORA_DIO2, LORA_DIO3, LORA_DIO4, LORA_DIO5,
                          LORA_ANT_RX, LORA_ANT_TX, LORA_ANT_BOOST, LORA_TCXO) {}

    void set_tx_config()
    {
        uint8_t buffer[] = {0};

        radio.SetTxConfig(MODEM_LORA, 13, 0, 0, 7, 1, 8, false, true, false, 0, false, 100);
        radio.Send(buffer, sizeof(buffer));

        received_event = EV_NONE;
    }

    void set_rx_config()
    {
        radio.SetRxConfig(MODEM_LORA, 13, 0, 7, 1, 8, 24, false, 0, false, false, 0, true, false);
        radio.Rx(RX_TIMEOUT);

        received_event = EV_NONE;
    }

    void setup()
    {
        radio.Sleep(); //Put the RF module in sleep mode
    }

private:
    RadioClass radio;

    RadioEvents_t radio_callbacks = {
        .TxDone = tx_done,
        .TxTimeout = tx_timeout,
        .RxDone = rx_done,
        .RxTimeout = rx_timeout,
        .RxError = rx_error
    };
};

#endif