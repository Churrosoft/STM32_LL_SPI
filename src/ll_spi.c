void send_byte(uint8_t byte)
{
    // Check if the SPI is enabled
    if ((SPI1->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
    {
        // If disabled, I enable it
        SET_BIT(SPI1->CR1, SPI_CR1_SPE);
    }

    while (!(SPI1->SR & SPI_SR_TXE))
        ;
    // Send bytes over the SPI
    LL_SPI_TransmitData8(SPI1, byte);
    // Wait until the transmission is complete
    while (SPI1->SR & SPI_SR_BSY)
        ;
    // Disable SPI
    CLEAR_BIT(SPI1->CR1, SPI_CR1_SPE);
}

void read_byte()
{
    if ((SPI1->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
        SET_BIT(SPI1->CR1, SPI_CR1_SPE);

    LL_SPI_TransmitData8(SPI1, 0);
    data = LL_SPI_ReceiveData8(SPI1);
    while (SPI1->SR & SPI_SR_BSY)
        ;
    CLEAR_BIT(SPI1->CR1, SPI_CR1_SPE);
}