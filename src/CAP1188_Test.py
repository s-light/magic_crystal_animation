"""CAP1188 minimal example."""

import board
import busio

# I2C setup
# from adafruit_cap1188.i2c import CAP1188_I2C
# print("CAP1188 I2C test.")
# i2c = busio.I2C(board.SCL, board.SDA)
# cap = CAP1188_I2C(i2c)

# SPI setup
from digitalio import DigitalInOut, Direction
from adafruit_cap1188.spi import CAP1188_SPI
print("CAP1188 SPI test.")
spi = busio.SPI(board.SCK, board.MOSI, board.MISO)

# https://learn.adafruit.com/using-atsamd21-sercom-to-add-more-spi-i2c-serial-ports/creating-a-new-spi#how-spi-is-created-now-3-2

# on SAMD51 SCK can only be on PIN1
# file:///home/stefan/mydata/arduino_infos/atmel/SAM-D5xE5x-Family-Datasheet-01507B.pdf#page=1014&zoom=180,-6,22

# PA16 = D0 = Sercom 3.1 = SCK = RX
# PA17 = D1 = Sercom 3.0 = MOSI = TX
# PA18 = D7 = Sercom 3.2 = MISO
# PA19 = D9 = Sercom 3.3 = -
# SPI_PAD_0_SCK_3
# SERCOM_RX_PAD_1
# SPIClass SPI1 (&sercom1, MISO, SCK, MOSI, SPI_PAD_xxx, SERCOM_RX_PAD_n);
# SPIClass SPI1 (&sercom3, 0, 9, 1, SPI_PAD_0_SCK_3, SERCOM_RX_PAD_1);
spi = busio.SPI(board.D0, board.D1, board.D7)

# PA20 = D10 = Sercom 5.2 = MISO
# PA21 = D11 = Sercom 5.3 = MOSI
# PA23 = D12 = Sercom 5.0 =
# PA22 = D13 = Sercom 5.1 = SCK
# spi = busio.SPI(board.D13, board.D11, board.D10)

# could we double use this as UART?
# PA20 = D10 = Sercom 5.2 = RX
# PA21 = D11 = Sercom 5.3 = -
# PA23 = D12 = Sercom 5.0 = TX
# PA22 = D13 = Sercom 5.1 = -

cs = DigitalInOut(board.D9)
cap = CAP1188_SPI(spi, cs)

cap.sensitivity = 128
print("sensitivity: ", cap.sensitivity)

touched_old = 0

print("loop:")

while True:
    touched = cap.touched()
    if touched != touched_old:
        touched_old = touched
        print("{:08b}".format(touched))
    # for i in range(1, 9):
    #     if cap[i].value:
    #         print("Pin {} touched!".format(i))
