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

Create a new file named `led_toggle.service` in the /etc/systemd/system/ directory:

```
sudo nano /etc/systemd/system/led_toggle.service
```

Add the following content to the file:

```
[Unit]
Description=LED Toggle Service
After=network.target

[Service]
ExecStart=/path/to/your/compiled/executable  # Update with the actual path to your compiled executable
Restart=always
User=pi  # Update with your Raspberry Pi username

[Install]
WantedBy=multi-user.target
```

## 2. Enable and Start the Service:

Now, enable the service to start at boot and start it:

```
sudo systemctl enable led_toggle.service
sudo systemctl start led_toggle.service
```


## 3. Check the Status:

You can check the status of your service to ensure it's running without any errors:

```
sudo systemctl status led_toggle.service
```
If there are any issues, the status command will provide information about what went wrong.

## 4. Reboot and Test:

Reboot your Raspberry Pi to ensure the service starts automatically:

```
sudo reboot
```

After the reboot, the LED should start blinking as the service gets automatically started.
## 5. Note

-    Make sure to replace /path/to/your/compiled/executable with the actual path to your compiled led_toggle executable.

-    Ensure that the User field in the service file matches your Raspberry Pi username.

If you make changes to the service file, reload the systemd manager:

```
sudo systemctl daemon-reload
```

Now, your LED toggle program should run as a service and blink the LED continuously on Raspberry Pi startup.


# Interact with GPIO pins on a Raspberry Pi without using a library like WiringPi
If you want to interact with GPIO pins on a Raspberry Pi without using a library like WiringPi, you can directly access the /sys/class/gpio interface provided by the Linux kernel. 

This involves writing to and reading from files in this directory to control GPIO pins. 

Below is a simple example using system calls and file I/O to toggle a GPIO pin.



```C++
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

```

In this example:

*   `exportGPIO` writes the GPIO pin number to the `/sys/class/gpio/export` file to make it accessible.
*   `unexportGPIO` writes the GPIO pin number to the `/sys/class/gpio/unexport` file to release it.
*   `setDirection` writes "out" or "in" to the `/sys/class/gpio/gpio<Pin>/direction` file to set the pin as an output or input.
*   `writeGPIO` writes 0 or 1 to the `/sys/class/gpio/gpio<Pin>/value` file to set the pin's output state.

Compile and run this program similarly to the previous steps. Note that this method involves more manual handling of GPIO compared to using a library like WiringPi, but it gives you more direct control over the hardware.
