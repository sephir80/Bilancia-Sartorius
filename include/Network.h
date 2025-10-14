#ifndef NETWORK_H
#define NETWORK_H

#include "arduino_secrets.h"
#include <WiFiS3.h>
#include <WiFiUdp.h>
#include <Arduino.h>
#include "NTPClient.h"

// WiFi parameters

// Server parameters

class Network{
    public:
        Network();
        Network(IPAddress local_IP, IPAddress gateway_IP, IPAddress subnet_Mask, IPAddress primary_DNS);
        bool Connect();
        unsigned long SyncTime();
        String getLocalIP();
        bool isConnected();
        bool sendData(const char* serverIP, uint16_t serverPort, const char* data, size_t length);
    private:
        const char* ssid     = SECRET_SSID;
        const char* password = SECRET_PASS;
        IPAddress localIP;
        IPAddress gateway;
        IPAddress subnet;
        IPAddress primaryDNS;
        String localIPAssigned;
        WiFiUDP udp;
        NTPClient *timeClient;  
};
#endif