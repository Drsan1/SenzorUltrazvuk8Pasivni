#include <Arduino.h> // do 60 cm meri +- 1 cm
#include <stdio.h>
// #include <fmt/core.h> //error: #error Module not supported.
// #include <format.h> 
// using fmt::print; // from https://github.com/MiroslavBurda/K2_Bratislava/blob/main/src/main.cpp
// #define echoPin 19 // pouzit fialova cisla z "Arduino Nano Pinout detailed.jpg"
// #define trigPin 4

//todo zprovoznit komunikaci s ESP - uart
// todo prumerovat vzdy poslednich 5 mereni -viz IR ve "vytlaceni ze ctverce"
//todo hlavicka 0x00, 0x80, 8 bytu dat, crc (bitovy soucet) 

const uint8_t countUson = 8; // count of Ultrasonics 
long duration[countUson] = { 0 }; // variable for the duration of sound wave travel
uint8_t distance[countUson] = { 0 };
uint8_t trigPin[countUson] = { 3, 4, 5, 6, 7, 8, 9, 10 };
uint8_t echoPin[countUson] = { 2, 19, 18, 17, 16, 15, 14, 13};


void setup() {
    for(int i = 0; i< countUson; i++) {
        pinMode(trigPin[i], OUTPUT);
        pinMode(echoPin[i], INPUT); 
    }
    Serial.begin(115200);
    Serial.println("Ultrasonic Sensor HC-SR04 Test");
    Serial.println("with Arduino Nano");
}
 
void loop() {
    for(int i = 0; i< countUson; i++) {
        // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
        digitalWrite(trigPin[i], HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin[i], LOW);
        // Reads the echoPin, returns the sound wave travel time in microseconds
        duration[i] = pulseIn(echoPin[i], HIGH);
        // Calculating the distance
        distance[i] = duration[i] * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
        // Displays the distance on the Serial Monitor
        Serial.print(i);
        Serial.print(" : "); // Serial.print(":  Distance: ");
        Serial.print(distance[i]);
        Serial.print(" : ");
        
    }
    Serial.println(" ");
    // Serial.read();
    delay(500);
    
}