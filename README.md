

 Multiplexer CD4051 ic for multiple analog sensors with ESP8266 / NODEMCU / and Arduino Boards

License: General Public (feel free to use it in your projects)

This program reads data from multiple analog inputs using a multiplexer ic CD4051 connected to the ESP8266/NODEMCU or Arduino development board.
It utilizes a digital multiplexer to select different sensor channels and reads data from each channel.
The sensor data can then be called separately for each specific sensor channel/pin or printed over serial communication.

Pinouts CD4051 IC:
         +--+--+--+
  IN0 -|13        16|- VCC
  IN1 -|14         6|- INH/EN
  IN2 -|15  4051   7|- VEE
  IN3 -|12         8|- VSS
  IN4 -|1          3|- COM (OUT/IN)
  IN5 -|5         11|- S0/A
  IN6 -|2         10|- S1/B
  IN7 -|4          9|- S2/C
         +--+--+--+

Here's how you can connect the CD4051 IC to the ESP8266/NODEMCU board pins:

- VCC (Pin 16): Connect to 3.3V or 5V power source from the ESP8266/NODEMCU board.
- VSS (Pin 8): Connect to GND of the ESP8266/NODEMCU board.
- VEE (Pin 7): Connect to GND of the ESP8266/NODEMCU board.
- INH/EN (Pin 6): Connect to GND of the ESP8266/NODEMCU board. You can also control the enable/disable state through MCU. Connect it to either VCC or GND based on whether you want to enable or disable the IC. If you want the IC to be always enabled, connect it to GND.
- COM (Pin 3): This is the output pin of the multiplexer. Connect it to the analog pin of the ESP8266/NODEMCU board where you want to read the multiplexed analog signal.
- S0, S1, S2 (Pins 11, 10, 9): These are the address selection pins. Connect them to digital pins of the ESP8266/NODEMCU board. 
                               You can configure these pins to select one of the 8 channels of the multiplexer.
-IN0...IN7: these are the pins conencted with the analog sensors/inputs.

Functionality:
- Define constants for the number of sensors and multiplexer pins
- Configure multiplexer channel settings
- Read data from sensors through the multiplexer
- Print sensor data over serial communication
- Implement a timer to read sensor data periodically
- Utilize a helper function to check if a second has elapsed
  
