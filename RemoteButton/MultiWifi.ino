#include "MultiWiFi.h"

 int MultiWiFi::run(unsigned long connectTimeout) 
 {
        uint8_t status = WiFi.status();

        if (status == WL_CONNECTED) {
            Serial.write("already connected\n");
            return status;
        }
        
        auto scanResult = WiFi.scanNetworks();
        if (scanResult < 0) {
            return -1;
        }

        for (const auto & network : this->networks) {
            for (size_t i = 0; i < scanResult; i++) {
                Serial.write("Searching for ");
                Serial.write(network.ssid.c_str());
                Serial.write("\n");

                // SSID() is implemented with different return types so we wrap
                // it into String()
                if (String(WiFi.SSID(i)) == network.ssid) {
                    WiFi.begin(network.ssid.c_str(), network.pass.c_str());
                    status = WiFi.status();

                    auto startTime = millis();
                    while (status == WL_IDLE_STATUS && (millis() - startTime) <= connectTimeout) {
                        delay(100);
                        status = WiFi.status();
                    }
                    
                    if (status == WL_CONNECTED)
                        break;
                }
            }
            if (status == WL_CONNECTED)
                break;
        }

        if( status != WL_CONNECTED ) {          
          Serial.write("Wifi not found\n");
        }

        return status;
    };