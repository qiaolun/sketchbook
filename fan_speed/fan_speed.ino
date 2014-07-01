

#include <IRremote.h>

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;

#define  BTN_PLUS   0xFFA857
#define  BTN_MINOR  0xFFE01F
#define  BTN_EQ     0xFF906F
#define  BTN_0      0xFF6897
#define  BTN_1      0xFF30CF
#define  BTN_2      0xFF18E7
#define  BTN_3      0xFF7A85
#define  BTN_4      0xFF10EF
#define  BTN_5      0xFF38C7
#define  BTN_6      0xFF5AA5
#define  BTN_7      0xFF42BD
#define  BTN_8      0xFF4AB5
#define  BTN_9      0xFF52AD


#define LED 7
#define FAN 9

#define STEP 100


int fanState = 0; // auto

int ledState = HIGH;

int time_delay = 10;
int time_step = STEP;
long interval = 3000;
long previousMillis = 0;

void setup() {

  Serial.begin(115200);
  Serial.println("Analyze IR Remote");

  irrecv.enableIRIn();

  // fan control
  pinMode(LED, OUTPUT);
  pinMode(FAN, OUTPUT);

}

void fan_control() {

  if(ledState == HIGH) {
    ledState = LOW;
    delay(100);
  } 
  else {
    ledState = HIGH;

    unsigned long currentMillis = millis();

    if(currentMillis - previousMillis > interval) {
      // save the last time you blinked the LED 
      previousMillis = currentMillis;   

      if(fanState == 0) {
        // auto
        time_delay += time_step;

        if(time_delay <= 10) {
          time_step = STEP;   
          time_delay = 10;
        } 
        else if (time_delay >= 800) {
          time_step = - STEP;
        }
      }
    }

    delay(time_delay);
  }

  digitalWrite(LED, ledState);
  digitalWrite(FAN, ledState);

}

void loop() {

  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    Serial.println(results.decode_type, DEC);    
    irrecv.resume(); // Receive the next value

      //
    if(results.value == BTN_EQ) {
      fanState = ! fanState; // switch control
      Serial.print("fan state ");
      Serial.println(fanState, DEC);
    } 
    else if (results.value == BTN_PLUS) {
      fanState = 1; // manual
      time_delay -= 30;
      if(time_delay < 10) {
        time_delay = 0; 
      }
    } 
    else if (results.value == BTN_MINOR) {
      fanState = 1; // manual
      time_delay += 30;
      if(time_delay > 600) {
        time_delay = 600; 
      }
    } 
    else if (results.value == BTN_0) {
      fanState = 1; // manual
      time_delay = 600;
    } 
    else if (results.value == BTN_1) {
      fanState = 1; // manual
      time_delay = 500;
    } 
    else if (results.value == BTN_2) {
      fanState = 1; // manual
      time_delay = 400;

    } 
    else if (results.value == BTN_3) {
      fanState = 1; // manual
      time_delay = 300;
    }
    else if (results.value == BTN_4) {
      fanState = 1; // manual
      time_delay = 200;
    }
    else if (results.value == BTN_5) {
      fanState = 1; // manual
      time_delay = 150;
    }
    else if (results.value == BTN_6) {
      fanState = 1; // manual
      time_delay = 100;
    }
    else if (results.value == BTN_7) {
      fanState = 1; // manual
      time_delay = 50;
    }
    else if (results.value == BTN_8) {
      fanState = 1; // manual
      time_delay = 20;
    }
    else if (results.value == BTN_9) {
      fanState = 1; // manual
      time_delay = 0;
    }
  } 
  else {
    fan_control();
  }


}












