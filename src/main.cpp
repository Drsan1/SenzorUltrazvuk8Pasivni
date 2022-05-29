#include <Arduino.h> // do 60 cm meri +- 1 cm
#include <stdio.h>
#include <NewPing.h> // https://bitbucket.org/teckel12/arduino-new-ping/wiki/browse/
// NewPing sonar(3, 2, 300);  // funguje, je to fajn, ale je to hodně pomalé, jedno měření 35 až 50 ms  

const bool TESTOVANI = false; // TESTOVANI = true - vypisuje do Serial testovací hlášky, čísla decimálně; TESTOVANI = false - do Serial pouze binarni data 
const uint8_t countUson = 8; // count of Ultrasonics 
const uint8_t countMeasure = 4; // count of measuring of every ultrasonic 
const uint8_t maxDist = 200; 
long duration[countUson] = { 0 }; // variable for the duration of sound wave travel
uint8_t distance[countUson] = { 0 };  

NewPing sonar[countUson] = {   // Sensor object array.
  NewPing(3, 2, maxDist), // Each sensor's trigger pin, echo pin, and max distance to ping. 
  NewPing(4, 19, maxDist), 
  NewPing(5, 18, maxDist),
  NewPing(6, 17, maxDist), 
  NewPing(7, 16, maxDist), 
  NewPing(8, 15, maxDist),
  NewPing(9, 14, maxDist), 
  NewPing(10, 12, maxDist)  // pin 13 nemeri spravne 
};

void averageUltrasonic();
long beginTime = millis();

void setup() {
    Serial.begin(115200);
    if (TESTOVANI) {
        Serial.println("Ultrasonic Sensor HC-SR04 Test");  
    }
}
 
long lastTime = millis();

void loop() {
    
    for(int i = 0; i< countUson; i++) { // measuring
        distance[i] = sonar[i].ping_cm();
        delay(30); // this MUST be here
    }

    if (TESTOVANI) { //testing 
        for(int i = 0; i< countUson; i++) {   
            Serial.print(i);             
            Serial.print(" : "); // Serial.print(":  Distance: ");
            Serial.print(distance[i]);
            Serial.print("cm,   ");
        }    
        Serial.print( millis() - lastTime);
        lastTime = millis();
        Serial.println(" ");   
    }
    else { // sending data
        for(int k = 1; k<4; k++) {
            Serial.write(250);      // header 1. byte
            Serial.write(250 + k);  // header 2. byte
            for(int i = 0; i< countUson; i++) {   
                Serial.write(distance[i]);
            }   
        }
    }   
}  // end of loop() ****************************************************
