# IoT Sensor Data Monitoring System

## Description
This project implements an IoT Sensor Data Monitoring System using an ESP32 microcontroller to gather data from multiple sensors, including a GPS module, MPU6050 accelerometer, and an ultrasonic sensor. The ESP32 sends the collected data to a Flask server for storage and visualization on a web interface. The system is designed for real-time monitoring and data analysis in various applications.

## Features
- **GPS Data Collection**: Captures longitude and latitude coordinates.
- **MPU6050 Sensor Integration**: Measures acceleration along X, Y, and Z axes.
- **Ultrasonic Sensor Measurement**: Calculates distance using sound waves.
- **Wi-Fi Connectivity**: Transfers sensor data to a server via HTTP POST requests.
- **Flask Backend**: Stores and displays data using a web-based interface.

## Hardware Requirements
- ESP32 microcontroller
- GPS module (e.g., NEO-6M)
- Adafruit MPU6050 accelerometer sensor
- Ultrasonic sensor (e.g., HC-SR04)
- Access to a Wi-Fi network

## Software Requirements
- Arduino IDE
- Libraries:
  - Adafruit_MPU6050
  - Adafruit_Sensor
  - TinyGPS++
- Python 3.x
- Flask for backend development
- SQLite (or another database) for data storage
- HTML/CSS for front-end

## Project Structure
![Screenshot 2025-01-22 234711](https://github.com/user-attachments/assets/cc5378f3-3cb2-4a41-9b9e-330517e33f86)

## Usage
- Power on the ESP32 to begin collecting sensor data.
- Ensure the Flask server is running and accessible on the same network.
- Monitor the collected data on the web interface.

## Contributing
Contributions are welcome! If you'd like to contribute, please fork the repository and create a pull request.

