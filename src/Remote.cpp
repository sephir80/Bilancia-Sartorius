#include "Remote.h"

Remote::Remote(char* srv, int p) 
{
    server = srv;
    port = p;
}


bool Remote::Connect() {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
    }
   delay(1000);
   bool connected = client.connect(server, port);
   return connected;
}

String Remote::GetIPAddress() {
    return WiFi.localIP().toString();
}

void Remote::Disconnect() {
    WiFi.disconnect();
}

void Remote::SendMsg(const char* msg) {
    //  udp.beginPacket(server, port);
    //  udp.print(msg);
    //  udp.endPacket();   
    client.print(msg);
    client.flush();
}
