#include <gps_read.hpp>
#include <ipaddress.hpp>
#include <regex>

int main(int argc, char** argv) {
    
    if(argc != 3) {
        std::cout << "Usage: " << argv[0] << " <host> <port>\n";
        return 0;
    }

    IPAddress ip;
    ip.setIp(argv[1]);
    ip.setPort(argv[2]);

    if(!ip.isValidIp()) {
        std::cerr << ip.getIp() << " is not a valid IP\n";
        return 1;
    }

    if(!ip.isValidIp()) {
        std::cerr << ip.getPort() << " is not a valid port\n";
        return 1;
    }

    GpsData gpsData;

    gpsData.openGpsPort(ip.getIp(), ip.getPort());

    if(!gpsData.isGpsPortOpen()) {
        std::cerr << "GPS port is not opened\n";
        return 1;
    }

    gpsData.readGpsData();

    std::cout << "Seconds=" << gpsData.getGpsTimeStampSecond() << std::endl;
    std::cout << "NanoSeconds=" << gpsData.getGpsTimeStempNanoSecond() << std::endl;

    gpsData.closeGpsPort();

    return 0;
}