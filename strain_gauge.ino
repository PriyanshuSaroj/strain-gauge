#include <HX711.h>

const int HX711_DOUT_PIN = 4;
const int HX711_CLK_PIN = 7;
long int t1;
HX711 scale;

void setup() {
  Serial.begin(9600);
  scale.begin(HX711_DOUT_PIN, HX711_CLK_PIN, 'B');
  scale.set_gain(32); // Set the gain to 128 (assuming GAIN pin is connected to GND)
  t1 = millis();
  Serial.print("time ");
}

void loop() {
  // Read the amplified voltage from the HX711
  long rawValue = scale.read();
  float amplified_vo = (rawValue * 5.0 / 8388608.0);
  float Vo = amplified_vo ;
  float GF = 2 ;
  float VEX = 3.79 ;
  // Display the raw value and converted voltage on the Serial Monitor
  Serial.print("Raw Value: ");
  Serial.print(rawValue);
  Serial.print(", Amplified Voltage: ");
  Serial.print(amplified_vo,4); // Convert the raw value to voltage (5V reference, 24-bit ADC)
  Serial.print(" V");
  Serial.print("   Strain: ");
  Serial.print(-4*Vo/(2*Vo + VEX*GF), 4);
  long int t2 = millis();
  Serial.print(", Time "); Serial.print(t2-t1); Serial.println(" milliseconds");


  delay(250); // Wait for a second before reading again
}