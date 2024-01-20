#include <iostream>
#include <wiringPi.h>

const int ledPin = 0; // GPIO pin 17

int main() {
    if (wiringPiSetup() == -1) {
        std::cerr << "Error initializing WiringPi." << std::endl;
        return 1;
    }

    pinMode(ledPin, OUTPUT);

    while (true) {
        digitalWrite(ledPin, HIGH);     // Turn ON the LED
        delay(1000);                    // Wait for 1 second
        digitalWrite(ledPin, LOW);      // Turn OFF the LED
        delay(1000);                    // Wait for 1 second
    }

    return 0;
}
