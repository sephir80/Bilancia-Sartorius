#include "Network.h"


Network::Network(String server_IP, unsigned int server_Port)
{
    this->serverIP = server_IP;
    this->localIP = "";
    this->serverPort = server_Port;
}


bool Network::Connect()
{
    WiFi.begin(ssid, password);
    int retries = 0;
    while (WiFi.status() != WL_CONNECTED && retries < 20) {
        delay(500);
        retries++;
    }
    if (WiFi.status() == WL_CONNECTED) {
        while (WiFi.localIP().toString() == "0.0.0.0")
        {
            delay(500);
        }
        localIP = WiFi.localIP().toString();
        return true;
    } else {
        return false;
    }
}

bool Network::isConnected() 
{
    if (WiFi.status() == WL_CONNECTED) {
        return true;
    }
    return false;
}

bool Network::sendData(const char* data, unsigned int length)
{
    if (!isConnected()) {
        return false;
    }

    WiFiUDP udp;
    udp.beginPacket(serverIP.c_str(), serverPort);
    udp.write((const uint8_t*)data, length);
    udp.endPacket();
    return true;
}