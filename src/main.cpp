#include <Arduino.h>
#include <RichWave.h>
#include <AlfredoCRSF.h>

/// config
const int CS_PIN = PB7; // Define your CS pin
const int LED_PIN = PC13; // Built-in LED pin on Blue Pill
const int DATA_PIN = PA7; // Built-in LED pin on Blue Pill
const int SCK_PIN = PA5; // Built-in LED pin on Blue Pill

const int SPY_CHANNEL = 6; // Number of channel wich swich Vrx

const int CHANNEL_1_PPM = 1000; // Value of trig PPM
const int CHANNEL_2_PPM = 1188; // Value of trig PPM
const int CHANNEL_3_PPM = 1393; // Value of trig PPM

const int CHANNEL_1 = 5740; // Freq listen 
const int CHANNEL_2 = 5865; // Freq listen 
const int CHANNEL_3 = 5917; // Freq listen 

void printChannels();
int checkChannel(int input);

AlfredoCRSF crsf;
HardwareSerial crsfSerial(PA3, PA2); // RX, TX
RichWave rx5808(DATA_PIN,CS_PIN,SCK_PIN);

void setup() {
  // Initialize Serial for logging
  Serial.begin(115200);
  crsfSerial.begin(CRSF_BAUDRATE); 
  crsf.begin(crsfSerial);
}

void loop() {

    crsf.update();
    if(crsf.isLinkUp()){
      static int frq = checkChannel(crsf.getChannel(SPY_CHANNEL));
      
      if (frq != checkChannel(crsf.getChannel(SPY_CHANNEL))){
        frq = checkChannel(crsf.getChannel(SPY_CHANNEL));
        rx5808.setFrequency(frq);
        Serial.print("RX: ");
        Serial.print(frq);
        Serial.println(" ");
      }
      }else{
        Serial.println("Link down");
    }
    delay(200);  // Wait for 1 second
}


void printChannels()
{

  Serial.print(crsf.getChannel(SPY_CHANNEL));
  Serial.print(", ");

  Serial.println(" ");
}

int checkChannel(int input) {
    if (input >= CHANNEL_1_PPM - 50 && input <= CHANNEL_1_PPM + 50) {
        return CHANNEL_1; 
    } else if (input >= CHANNEL_2_PPM - 50 && input <= CHANNEL_2_PPM + 50) {
        return CHANNEL_2; 
    } else if (input >= CHANNEL_3_PPM - 50 && input <= CHANNEL_3_PPM + 50) {
        return CHANNEL_3; 
    } else {
        return CHANNEL_1; 
    }
}