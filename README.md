# IoT Sensor Data Monitoring System
## Description
This project implements an IoT Sensor Data Monitoring System using an ESP32 microcontroller to gather data from multiple sensors, including a GPS module, MPU6050 accelerometer, and an ultrasonic sensor. The ESP32 sends the collected data to a Flask server for storage and visualization on a web interface. The system is designed for real-time monitoring and data analysis in various applications.

Features
- GPS Data Collection: Captures longitude and latitude coordinates.
- MPU6050 Sensor Integration: Measures acceleration along X, Y, and Z axes.
- Ultrasonic Sensor Measurement: Calculates distance using sound waves.
- Wi-Fi Connectivity: Transfers sensor data to a server via HTTP POST requests.
- Flask Backend: Stores and displays data using a web-based interface.

Hardware Requirements
- ESP32 microcontroller
- GPS module (e.g., NEO-6M)
- Adafruit MPU6050 accelerometer sensor
- Ultrasonic sensor (e.g., HC-SR04)
- Access to a Wi-Fi network

Software Requirements
- Arduino IDE
- Libraries:
- Adafruit_MPU6050
- Adafruit_Sensor
- TinyGPS++
  
Python 3.x
- Flask for backend development
- SQLite (or another database) for data storage
- HTML/CSS for front-end

iot-sensor-data-monitoring/
│
├── arduino/                   
│   └── main.ino               # ESP32 Arduino code
│
├── flask-server/              
│   ├── app.py                 # Flask backend
│   ├── templates/             # HTML files for front-end
│   │   └── index.html         # Web interface
│   └── static/                # Static files (CSS, JS)
│       ├── style.css          # Styling for the web interface
│       └── script.js          # JavaScript for interactivity
│
├── requirements.txt           # Python dependencies
├── README.md                  # Project documentation
└── LICENSE                    # License information

Usage
- Power on the ESP32 to begin collecting sensor data.
- Ensure the Flask server is running and accessible on the same network.
- Monitor the collected data on the web interface.

Contributing
Contributions are welcome! If you'd like to contribute, please fork the repository and create a pull request.

