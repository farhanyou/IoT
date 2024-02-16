
/*
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
 Multiplexer CD4051 ic for multiple analog sensors
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
Author: Ferhan Y. (fehaan@hotmail.com)
License: General Public (feel free to use it in your projects)

This example program reads data from multiple analog inputs using a multiplexer ic CD4051 connected to the ESP8266/NODEMCU or Arduino development board.
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
---------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

// Define the number of sensors attached to the board
#define NUM_SENSORS 8

// Define multiplexer control pins
#define MUX_CONTROL_PINS_SZ 3
#define MUX_A D4  // S0 pin of 4051 connected to D4 pin of the board
#define MUX_B D5  // S1 pin of 4051 connected to D4 pin of the board
#define MUX_C D6  // S2 pin of 4051 connected to D4 pin of the board

//Macro to convert temperature value into C/F units
#define TEMP_C(X) ((X * (5000 / 1024)) / 10)
#define TEMP_F(X) ((TEMP_C(X) * 1.8) + 32)

// Array to hold multiplexer channel control pins
int mux_control_pins[3] = { MUX_A, MUX_B, MUX_C };

// Set size of the multiplexer control pins for use in the sketch
int mux_control_pins_sz = MUX_CONTROL_PINS_SZ;

// Multiplexer channel selection configuration
int mux_channels[NUM_SENSORS][3] = {
  { 0, 0, 0 },  //channel 0
  { 1, 0, 0 },  //channel 1
  { 0, 1, 0 },  //channel 2
  { 1, 1, 0 },  //channel 3
  { 0, 0, 1 },  //channel 4
  { 1, 0, 1 },  //channel 5
  { 0, 1, 1 },  //channel 6
  { 1, 1, 1 }   //channel 7
};

// Define multiplexer data pin
#define MUX_DATA_PIN A0

// Define sensors connected to the ic pin. You can use your own set of sensors or analo input devices.
#define AMBIENT_SENSE_PIN 0
#define BATT_VOLT_SENSE_PIN 1
#define TEMP_SENSE_PIN 2

// Assign pins
int mux_data_pin = MUX_DATA_PIN;
int batt_volt_sense_pin = BATT_VOLT_SENSE_PIN;
int ambient_sense_pin = AMBIENT_SENSE_PIN;
int temp_sense_pin = TEMP_SENSE_PIN;

// Multiplexer read timer variables used to read data at an interval
int sensors_read_timer;
int sensors_read_time = 5;  // in seconds

// Setup function
void setup() {
  //Serial port initialization
  Serial.begin(115200);

  // Initialize multiplexer control pins
  for (int i = 0; i < mux_control_pins_sz; i++) {  // loop through multiplexer channel select pins
    pinMode(mux_control_pins[i], OUTPUT);          // set pin mode
    digitalWrite(mux_control_pins[i], LOW);        // set channel control pin state to OFF
  }
  Serial.println("initialized.");
}

// Loop function
void loop() {
  if (EverySecond()) {
    sensors_read_timer++;                                                                          // increment sensor read timer value every second
    if (sensors_read_timer >= sensors_read_time) {                                                 // if sensor read timer reaches read interval value
      Serial.printf("Ambient light: %d.\n", read(ambient_sense_pin) * (5 / 1024));                 // read sensor value for ambient light sensor value
      Serial.printf("Battery voltage: %.1f.\n", (float)(read(batt_volt_sense_pin) * (5 / 1024)));  // read battery voltage divider value
      Serial.printf("Temperature: %.1f\n", (float)(TEMP_C(read(temp_sense_pin))));                 // read temperature sensor value in Celcius
      sensors_read_timer = 0;                                                                      // reset sensor read timer
    }
  }
}

// Function to read from a specific channel
int read(int channel) {
  for (int i = 0; i < mux_control_pins_sz; i++) {
    digitalWrite(mux_control_pins[i], mux_channels[channel][i]);
  }
  return analogRead(mux_data_pin);
}

// Function to check if a second has elapsed
bool EverySecond() {
  int interval = 1000;
  static int timer = millis();
  if (millis() - timer >= interval) {
    timer += interval;
    return true;
  }
  return false;
}
