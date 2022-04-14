#include<ipaddress.hpp>

void IPAddress::setIp(const char* ip) {
    this->ip = ip;
}

void IPAddress::setPort(const char* port) {
    this->port = port;
}

bool IPAddress::isValidIp() const {
    if(ip == "localhost") return true;

    std::regex ipv4("(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])");
    std::regex ipv6("((([0-9a-fA-F]){1,4})\\:){7}([0-9a-fA-F]){1,4}");

    if (std::regex_match(ip, ipv4)) return true;

    if (std::regex_match(ip, ipv6)) return true;

    return false;
}

bool IPAddress::isValidPort() const {
    std::regex validPort("^((6553[0-5])|(655[0-2][0-9])|(65[0-4][0-9]{2})|(6[0-4][0-9]{3})|([1-5][0-9]{4})|([0-5]{0,5})|([0-9]{1,4}))$");

    if (std::regex_match(port, validPort)) return true;

    return false;
}

std::string IPAddress::getIp() const {
    return ip;
}

std::string IPAddress::getPort() const {
    return port;
}