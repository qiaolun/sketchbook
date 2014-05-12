#include <dht11.h>



dht11 DHT11;

#define DHT11PIN 2

#define VOpin4 8 // Vout 1 , > 2.5
#define VOpin2 9 // Vout 2 , > 1.0

#define sampletime_ms 30000

unsigned long duration;
unsigned long starttime;

unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;

int mode = VOpin4;

void setup() {
  Serial.begin(115200);
  pinMode(VOpin2,INPUT);
  pinMode(VOpin4,INPUT);
  starttime = millis();
}

void loop() {
  
  if(mode == VOpin4) {
    duration = pulseIn(VOpin4, LOW);
    lowpulseoccupancy = lowpulseoccupancy+duration;
  } else {
    duration = pulseIn(VOpin2, LOW);
    lowpulseoccupancy = lowpulseoccupancy+duration; 
  }
  
  if ((millis()-starttime) > sampletime_ms)
  {
    
    // check ratio
    
    ratio = lowpulseoccupancy/(sampletime_ms*10.0);  // Integer percentage 0=>100
    concentration = 0.30473 * pow(ratio, 3) - 2.63943 * pow(ratio, 2) + 102.60291 * ratio - 3.49616;
    Serial.print("pmdata,");
    Serial.print(mode);
    Serial.print(",");
    Serial.print(lowpulseoccupancy);
    Serial.print(",");
    Serial.print(ratio);
    Serial.print(",");
    Serial.println(concentration);
    lowpulseoccupancy = 0;
    starttime = millis();
    if(mode == VOpin4) {
      mode = VOpin2; 
    } else {
      mode = VOpin4;
    }
    
    // read dht11
    
    int chk = DHT11.read(DHT11PIN);

    Serial.print("Read sensor: ");
    switch (chk)
    {
      case DHTLIB_OK: 
        Serial.println("OK"); 
          break;
      case DHTLIB_ERROR_CHECKSUM:
        Serial.println("Checksum error"); 
          break;
      case DHTLIB_ERROR_TIMEOUT: 
        Serial.println("Time out error"); 
          break;
      default: 
        Serial.println("Unknown error"); 
          break;
    }
  
    Serial.print("Humidity (%): ");
    Serial.println((float)DHT11.humidity, 2);
  
    Serial.print("Temperature (C): ");
    Serial.println((float)DHT11.temperature, 2);
  
    Serial.print("data,");
    Serial.print((float)DHT11.temperature, 2);
    Serial.print(",");
    Serial.println((float)DHT11.humidity, 2);
    
  }
}
