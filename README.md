# Linux-Gpio-Management using WiringPi:

## 1. Enable GPIO on Raspberry Pi:
Ensure that the GPIO interface is enabled on your Raspberry Pi.

You can do this using the raspi-config command.

Open a terminal and run:

```
sudo raspi-config
```
Navigate to Interfacing Options -> GPIO and enable it.
<img width="941" alt="image" src="https://github.com/semrade/Linux-Gpio-Management/assets/17770194/b2aafc67-5be1-4c27-a3fa-3408d078bde1">


## 2. Install WiringPi library:
WiringPi is a C library that allows easy access to the GPIO pins on the Raspberry Pi. 

Install it using the following commands:

```
sudo apt-get update
sudo apt-get install wiringpi
```
You might not be able to install the WiringPi package on your Raspberry Pi using the below command. In that case, you can opt for manual installation by cloning and building the package.

```
git clone https://github.com/WiringPi/WiringPi.git
cd WiringPi
./build
```

The last command `./build`  will compile and install the necessary resources into the system. You can delete the cloned package if you wish.

To verify that the package is installed on your system, you can use the following command

```
gpio -v
```

## 3. Connect the LED:

Connect your LED to one of the GPIO pins on the Raspberry Pi. For example, connect it to GPIO pin 17. 
Connect the anode (longer leg) of the LED to the GPIO pin and the cathode (shorter leg) to the ground (GND) pin.

Use a resistance of 300 Ohms or 200 Ohms depending on the led you are using.

## 4. Write the C++ Code:

Create a new C++ file, for example, led_toggle.cpp, and use the following code:
```C++
#include <iostream>
#include <wiringPi.h>

const int ledPin = 17; // GPIO pin 17

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

```
This code initializes WiringPi, sets the GPIO pin as an output, and then toggles the LED state in a loop.

## 5. Compile and Run:

Compile the code using g++ and run the executable:
```
g++ -o led_toggle led_toggle.cpp -lwiringPi
./led_toggle
```
The LED connected to GPIO pin 17 should start toggling on and off.

## 6. Create a systemd Service File:
## Notes:
-Make sure to adjust the ledPin variable in the code according to the GPIO pin you have connected the LED to.

-You can stop the program by pressing Ctrl+C in the terminal where the program is running.

# Linux-Gpio-Management using Linux files management

## 1. Create a systemd Service File:

## 2. Enable and Start the Service:

## 3. Check the Status:

## 4. Reboot and Test:

## 5. 
