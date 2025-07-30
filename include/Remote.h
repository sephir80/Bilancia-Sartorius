#include <WiFiS3.h>
#include <WiFiUdp.h>
#include "privateData.h"

class Remote {
    private:
    char* server;
    int port;
    WiFiClient client;
    WiFiUDP udp;
public:
    Remote(char* srv= nullptr, int p = 5000);

    bool Connect();
    String GetIPAddress();
    void Disconnect();
    void SendMsg(const char* msg);
};