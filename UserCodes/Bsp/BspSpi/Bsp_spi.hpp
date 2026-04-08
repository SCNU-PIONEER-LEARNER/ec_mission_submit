#pragma once

#include "stm32f4xx_hal.h"

class Spi {
public:
    void transmit(SPI_HandleTypeDef _spi, uint8_t *_txData,
                  uint16_t _dataLength, uint16_t _timeout);

    void transmitIT(SPI_HandleTypeDef _spi, uint8_t *_txData,
                    uint16_t _dataLength);

    void transmitDMA(SPI_HandleTypeDef _spi, uint8_t *_txData,
                     uint16_t _dataLength);

    void receive(SPI_HandleTypeDef _spi, uint8_t *_rxData, uint16_t _dataLength,
                 uint16_t _timeout);

    void receiveIT(SPI_HandleTypeDef _spi, uint8_t *_rxData,
                   uint16_t _dataLength);

    void receiveDMA(SPI_HandleTypeDef _spi, uint8_t *_rxData,
                    uint16_t _dataLength);

    void transmitReceive(SPI_HandleTypeDef _spi, uint8_t *_txData,
                         uint8_t *_rxData, uint16_t _dataLength,
                         uint16_t _timeout);

    void transmitReceiveIT(SPI_HandleTypeDef _spi, uint8_t *_txData,
                           uint8_t *_rxData, uint16_t _dataLength);

    void transmitReceiveDMA(SPI_HandleTypeDef _spi, uint8_t *_txData,
                            uint8_t *_rxData, uint16_t _dataLength);

    static Spi &instance()
    {
        static Spi instance;
        return instance;
    }

private:
    Spi(const Spi &);
    Spi &operator=(const Spi &);
    Spi() = default;
};
