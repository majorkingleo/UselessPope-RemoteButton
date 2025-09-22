#include "MultiWiFi.h"
#include <WiFi.h>

/**
 * I had to made some modifications, since the status handling seems
 * to be differtent on my esp32 WROOM device.
 */

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

                // SSID() is implemented with different return types so we wrap
                // it into String()
                if (String(WiFi.SSID(i)) == network.ssid) {    
                
                    WiFi.begin(network.ssid.c_str(), network.pass.c_str());
                    status = WiFi.status();

                    auto startTime = millis();

                    while (is_connection_in_progress(status) && (millis() - startTime) <= connectTimeout) {                                                
                        status = WiFi.status();
                    }
                    
                    if (status == WL_CONNECTED) {
                        break;
                    }
                }
            }
            if (status == WL_CONNECTED) {
                break;
            }
        }

        return status;
    }


    bool MultiWiFi::is_connection_in_progress( uint8_t status ) const
    {
        switch( status )
        {
            case WL_NO_SHIELD:          return false;
            case WL_STOPPED:            return false;
            case WL_IDLE_STATUS:        return true;
            case WL_NO_SSID_AVAIL:      return false;
            case WL_SCAN_COMPLETED:     return false;
            case WL_CONNECTED:          return false;
            case WL_CONNECT_FAILED:     return false;
            case WL_CONNECTION_LOST:    return false;
            case WL_DISCONNECTED:       return true;
            default:
                return false;
        }

        return false;
    }