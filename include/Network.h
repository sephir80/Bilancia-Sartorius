#ifndef NETWORK_H
#define NETWORK_H

#include "arduino_secrets.h"
#include <WiFiS3.h>
#include <WiFiUdp.h>
#include <Arduino.h>

// WiFi parameters

// Server parameters

class Network{
    public:
        Network(String server_IP, unsigned int server_Port);
        bool Connect();
        String getLocalIP() const { return this->localIP; }
        bool isConnected();
        bool sendData(const char* data, unsigned int length);
    private:
        const char* ssid     = SECRET_SSID;
        const char* password = SECRET_PASS;
        String serverIP;
        unsigned int serverPort;
        String localIP;
        WiFiUDP udp;
};
#endif