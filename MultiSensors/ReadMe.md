---------------------------------------------------------------------------------------------------------------------------------------------------------------------
 <h1>Multiplexer CD4051 ic for multiple analog sensors</h1>
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
<b>Author:</b> Ferhan Y. (fehaan@hotmail.com)
<b>License:</b> General Public (feel free to use it in your projects)

This example program reads data from multiple analog inputs using a multiplexer ic CD4051 connected to the ESP8266/NODEMCU or Arduino development board.
It utilizes a digital multiplexer to select different sensor channels and reads data from each channel.
The sensor data can then be called separately for each specific sensor channel/pin or printed over serial communication.
<p>
 <b>Pinouts CD4051 IC:</b>
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
</p>

<h3>Here's how you can connect the CD4051 IC to the ESP8266/NODEMCU board pins:</h3>

- <b>VCC (Pin 16):</b> Connect to 3.3V or 5V power source from the ESP8266/NODEMCU board.
- <b>VSS (Pin 8):</b> Connect to GND of the ESP8266/NODEMCU board.
- <b>VEE (Pin 7):</b> Connect to GND of the ESP8266/NODEMCU board.
- <b>INH/EN (Pin 6):</b> Connect to GND of the ESP8266/NODEMCU board. You can also control the enable/disable state through MCU. Connect it to either VCC or GND based on whether you want to enable or disable the IC. If you want the IC to be always enabled, connect it to GND.
- <b>COM (Pin 3):</b> This is the output pin of the multiplexer. Connect it to the analog pin of the ESP8266/NODEMCU board where you want to read the multiplexed analog signal.
- <b>S0, S1, S2 (Pins 11, 10, 9):</b> These are the channel/address selection pins. Connect them to digital pins of the ESP8266/NODEMCU board. 
                               You can configure these pins to select one of the 8 channels of the multiplexer.
- <b>IN0...IN7:</b> these are the pins conencted with the analog sensors/inputs.

<h3>Functionality:</h3>

<b>Instantiate the MultiSense Library:</b>
<code><p>multiSensor MySensor(S0,S1,S2,AnalaogPin, numSensors); </p></code>
