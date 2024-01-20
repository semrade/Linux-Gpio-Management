#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>

const int gpioPin = 17; // GPIO pin 17

void exportGPIO() {
    std::ofstream exportFile("/sys/class/gpio/export");
    exportFile << gpioPin;
    exportFile.close();
}

void unexportGPIO() {
    std::ofstream unexportFile("/sys/class/gpio/unexport");
    unexportFile << gpioPin;
    unexportFile.close();
}

void setDirection(bool isOutput) {
    std::string directionPath = "/sys/class/gpio/gpio" + std::to_string(gpioPin) + "/direction";
    std::ofstream directionFile(directionPath);
    directionFile << (isOutput ? "out" : "in");
    directionFile.close();
}

void writeGPIO(bool value) {
    std::string valuePath = "/sys/class/gpio/gpio" + std::to_string(gpioPin) + "/value";
    std::ofstream valueFile(valuePath);
    valueFile << value;
    valueFile.close();
}

int main() {
    // Export GPIO pin
    exportGPIO();

    // Set GPIO pin as output
    setDirection(true);

    while (true) {
        // Turn ON the LED
        writeGPIO(true);
        usleep(500000); // Sleep for 0.5 seconds

        // Turn OFF the LED
        writeGPIO(false);
        usleep(500000); // Sleep for 0.5 seconds
    }

    // Unexport GPIO pin
    unexportGPIO();

    return 0;
}

