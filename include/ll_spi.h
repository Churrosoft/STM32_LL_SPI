#ifndef LL_SPI_H
#define LL_SPI_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "spi.h"
#include <stdint.h>
#include <stdbool.h>

    // ----------------------------------------------------------------------------
    void spi_disable(void);
    void spi_enable(void);
    void spi_send_byte(uint8_t);
    uint8_t spi_read_byte(void);
    void spi_read_multiple(uint8_t *, uint32_t);
    void spi_send_multiple(uint8_t *, uint32_t);
// ----------------------------------------------------------------------------
#ifdef __cplusplus
}
#endif

#endif // LL_SPI_H
