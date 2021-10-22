#include "../include/ll_spi.h"

void spi_enable()
{
    // Check if the SPI is enabled
    if ((SPI2->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
    {
        // If disabled, I enable it
        SET_BIT(SPI2->CR1, SPI_CR1_SPE);
    }
}

void spi_disable()
{
    CLEAR_BIT(SPI2->CR1, SPI_CR1_SPE);
}

void spi_send_byte(uint8_t byte)
{

    if ((SPI2->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
    {
        SET_BIT(SPI2->CR1, SPI_CR1_SPE);
    }

    while (!(SPI2->SR & SPI_SR_TXE))
        ;
    // Send bytes over the SPI
    LL_SPI_TransmitData8(SPI2, byte);
    // Wait until the transmission is complete
    while (SPI2->SR & SPI_SR_BSY)
        ;
    // Disable SPI
}

uint8_t spi_read_byte()
{
    volatile uint8_t data;
    if ((SPI2->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
    {
        SET_BIT(SPI2->CR1, SPI_CR1_SPE);
    }
    while (!(SPI2->SR & SPI_SR_TXE))
        ;

    //purge all the shit
    while (LL_SPI_IsActiveFlag_RXNE(SPI2))
        LL_SPI_ReceiveData8(SPI2);

    LL_SPI_TransmitData8(SPI2, 0);
    data = LL_SPI_ReceiveData8(SPI2);
    while (SPI2->SR & SPI_SR_BSY)
        ;
    return data;
}

void spi_read_multiple(uint8_t *rx_buffer, uint32_t bytes_to_receive)
{

    //BUG: first byte is always garbage
    spi_read_byte();
    for (uint32_t index = 0; index < bytes_to_receive; index++)
    {
        rx_buffer[index] = spi_read_byte();
    }
}

void spi_send_multiple(uint8_t *tx_buffer, uint32_t bytes_to_send)
{

    for (uint32_t index = 0; index < bytes_to_send; index++)
    {
        //TODO: en caso de que la data sea divisible por 16, se puede utilizar LL_SPI_TransmitData16 para tardar la mitad de tiempo
        spi_send_byte(tx_buffer[index]);
    }
}
