# **ESP32 Sensor Pipeline**

## 🚀 About
**ESP32 sensor pipeline** is a project which uses the WiFi capability of the ESP32 to send sensor data via the internet using HTTP protocols. This project aims to simulate real-life systems where embedded microcontrollers are reading data from the environment and storing that data in a database somewhere on the internet, and using APIs to query that data within the database. 

## ⚙️ Tech Stack
Currently, this project has an ESP32 with a DHT11 sensor wired to it. In the main.cpp file, the ESP32 connects to my local WiFi network, and sends json data to a Flask server I have running locally using HTTP POST request. This json data consists of the temperature measured, the time of data production and the id of the sensor. 

The Flask server is connected to a MongoDB database running on my machine. Connection, writing and reading from this mongodb database is done using PyMongo. The POST method is used to write data to the mongodb database. A sample GET request has been written, however this GET request is merely a sample request and will be updated in the future, to retrieve more useful data to be used, for web applications, data science, and machine learning model purposes. These API methods are tested using [Postman API testing software](https://www.postman.com/downloads/)

Sample data in MongoDB database:

![image](https://github.com/user-attachments/assets/e47b5611-2400-4cd1-9cd8-dfa500859a99)
