#ifndef MULTIWIFI_H_
#define MULTIWIFI_H_

// copied and modified from:
// https://github.com/arduino-libraries/Arduino_MultiWiFi
// Mozilla Public License 2.0
// See MultiWifi.LICENSE.txt for Details

#include <vector>

class MultiWiFi 
{
    struct Network_t {
        String ssid;
        String pass;
    };

    std::vector<Network_t> networks;

public:

    void add(const char* ssid, const char *pass = NULL) 
    {
        Network_t network;
        network.ssid = String(ssid);
        if (pass != nullptr)
            network.pass = String(pass);
        
        this->networks.push_back(network);
    };

    int run(unsigned long connectTimeout = 5000);

private:
    bool is_connection_in_progress( uint8_t status ) const;
};

#endif
