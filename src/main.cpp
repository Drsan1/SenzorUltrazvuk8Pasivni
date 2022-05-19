#include <Arduino.h> // do 60 cm meri +- 1 cm
#include <stdio.h>
// #include <thread>
// #include <fmt/core.h> //error: #error Module not supported.
// #include <format.h> 
// using fmt::print; // from https://github.com/MiroslavBurda/K2_Bratislava/blob/main/src/main.cpp
// #define echoPin 19 // pouzit fialova cisla z "Arduino Nano Pinout detailed.jpg"
// #define trigPin 4

//todo zprovoznit komunikaci s ESP - uart
// todo prumerovat vzdy poslednich 5 mereni -viz IR ve "vytlaceni ze ctverce"
//todo hlavicka 0x00, 0x80, 8 bytu dat, crc (bitovy soucet) 

const uint8_t countUson = 7; // count of Ultrasonics 
const uint8_t countMeasure = 4; // count of measuring of every ultrasonic 
long duration[countUson] = { 0 }; // variable for the duration of sound wave travel
uint8_t distance[countUson] = { 0 };  
uint8_t trigPin[countUson] = { 3, 4, 5, 6, 7, 8, 9 }; //10
uint8_t echoPin[countUson] = { 2, 19, 18, 17, 16, 15, 14};  //13
uint8_t dist[countUson][countMeasure] = {{ 0 }, { 0 }} ; 
int k = 0; // counter for averageUltrasonic()

void averageUltrasonic();
long beginTime = millis();

uint8_t readUson(uint8_t numUson){
    digitalWrite(trigPin[numUson], HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin[numUson], LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration[numUson] = pulseIn(echoPin[numUson], HIGH);
    // Calculating the distance
    return duration[numUson] * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
}

void setup() {
    for(int i = 0; i< countUson; i++) {
        pinMode(trigPin[i], OUTPUT);
        pinMode(echoPin[i], INPUT); 
    }

    // std::thread t2(averageUltrasonic); // prumerne hodnoty z IR

    Serial.begin(115200);
    Serial.println("Ultrasonic Sensor HC-SR04 Test");
    long beginTime = millis();
}
 
void loop() {
    averageUltrasonic();
    for(int i = 0; i< countUson; i++) {
        Serial.print(i);
        Serial.print(" : "); // Serial.print(":  Distance: ");
        Serial.print(distance[i]);
        Serial.print("cm,   ");
    }
    Serial.print( millis() - beginTime);
    Serial.println(" ");
    // Serial.read();
    delay(10);
    
}  // end of loop() ****************************************************

void averageUltrasonic() { // Ultrasonic averaging 

    // while (true) {
        k++;
        if (k == 30000)
            k = 0;
        byte N = k % countMeasure;
        for(int i = 0; i< countUson; i++)
            dist[i][N] =  readUson(i);

        for(int i = 0; i< countUson; i++)  {
            byte a = 0; 
            while (a < countMeasure) {
                distance[i] += dist[i][a];
                a++;
            }
            distance[i] /= countMeasure;
        } 
        delay(10);
    // }
}