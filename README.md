# Sensor Sys
<img src="images/Yunli.png"  width="64" />

Dankao Chen

## Common Pin Assignment Table for ESP8266 Development Boards

Below is a table of commonly used pin assignments for ESP8266 development boards (such as NodeMCU or similar), including their functions, GPIO numbers, and key considerations:

| Pin No. | GPIO      | Default Function         | Project Usage           | Common Usage          | Notes                                                                                         |
|---------|-----------|--------------------------|--------------------------|-----------------------|-----------------------------------------------------------------------------------------------|
| D0      | GPIO 16   | Deep Sleep Wake-Up       | NMOS (Fan) (TBD)         | General IO, Low-Frequency Signal | No PWM, I2C, or interrupt support; only supports digital input/output.                       |
| D1      | GPIO 5    | I2C (SCL)               | I2C (SCL) CCS811         | General IO, I2C Clock Signal  | Versatile IO, compatible with most functions.                                                |
| D2      | GPIO 4    | I2C (SDA)               | I2C (SDA) CCS811         | General IO, I2C Data Signal   | Versatile IO, compatible with most functions.                                                |
| D3      | GPIO 0    | Boot Mode Control, Flash Button | CCS811          | General IO (Low Current)     | Must stay HIGH during power-up; otherwise, enters programming mode. Avoid high-frequency or heavy loads. |
| D4      | GPIO 2    | Built-in LED, UART1 TX  | Serial1 Debug            | General IO, LED Control       | HIGH at power-up; use as output only to avoid false resets or boot issues.                   |
| D5      | GPIO 14   | SPI (SCLK)              | Encoder Button           | General IO, SPI Clock Signal | Suitable for high-speed signals.                                                             |
| D6      | GPIO 12   | SPI (MISO)              | Encoder Pin A            | General IO, SPI Data Input    | Suitable for high-speed signals.                                                             |
| D7      | GPIO 13   | SPI (MOSI)              | Encoder Pin B            | General IO, SPI Data Output   | Suitable for high-speed signals.                                                             |
| D8      | GPIO 15   | SPI (CS)                | Home Button (Pull-down Resistor Included) | General IO, SPI Chip Select Signal | Must stay LOW during power-up; not suitable for signals requiring sustained HIGH levels.      |
| RX      | GPIO 3    | UART0 RX                | UART RX PMS7003          | Serial Communication (Receiving Data) | Default USB UART connection for debugging; can be used as input, but conflicts with debugging. |
| TX      | GPIO 1    | UART0 TX                | UART TX PMS7003          | Serial Communication (Sending Data) | Default USB UART connection for debugging; can be used as output, but conflicts with debugging. |
| A0      | ADC0      | Analog Input (0~1V)     | MQ135 (A0)               | Reading Analog Signals (Sensors) | Voltage range limited to 0~1V; requires voltage divider or amplifier for higher voltages.    |

**Notes:**
- Ensure proper GPIO configuration to avoid boot or operational conflicts.
- Consider power-up states and default behaviors when selecting pins for specific tasks.
- Use external resistors or components as necessary to adjust voltage levels or signal characteristics.
