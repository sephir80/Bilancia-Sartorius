#include "Network.h"
#include <RTC.h>


Network::Network( IPAddress local_IP, IPAddress gateway_IP, IPAddress subnet_Mask, IPAddress primary_DNS)
{
    this->localIP = local_IP;
    this->gateway = gateway_IP;
    this->subnet = subnet_Mask;
    this->primaryDNS = primary_DNS;
    WiFi.config(this->localIP,this->primaryDNS,this->gateway,this->subnet);
}

Network::Network()
{
    this->localIP = IPAddress(0,0,0,0);
    this->gateway = IPAddress(0,0,0,0);
    this->subnet = IPAddress(0,0,0,0);
    this->primaryDNS = IPAddress(0,0,0,0);
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
        localIPAssigned = WiFi.localIP().toString();
        udp.begin(5050);
        return true;
    } else {
        return false;
    }
}

unsigned long Network::SyncTime()
{
    timeClient=new NTPClient(udp, "ntp1.inrim.it", 3600, 60000);
    timeClient->begin();
    timeClient->update();
    unsigned long epochTime = timeClient->getEpochTime();
    return epochTime;
}

bool Network::isConnected() 
{
    if (WiFi.status() == WL_CONNECTED) {
        return true;
    }
    return false;
}

bool Network::sendData(const char* serverIP,unsigned int serverPort,const char* data, unsigned int length)
{
    if (!isConnected()) {
        return false;
    }

    udp.beginPacket(serverIP, serverPort);
    udp.write((const uint8_t*)data, length);
    udp.endPacket();
    return true;
}

String Network::getLocalIP()
{
    return localIPAssigned;
}