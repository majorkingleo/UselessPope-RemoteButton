#ifndef MULTIWIFI_H_
#define MULTIWIFI_H_

// copied and modified from:
// https://github.com/arduino-libraries/Arduino_MultiWiFi
// Mozilla Public License 2.0
// See MultiWifi.LICENSE.txt for Details

#include <vector>

class MultiWiFi {
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
    struct Network_t {
        String ssid;
        String pass;
    };
    std::vector<Network_t> networks;
};

#endif
