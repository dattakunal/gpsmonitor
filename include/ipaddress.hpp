#include <string>
#include <regex>

class IPAddress {
    std::string ip{"0.0.0.0"};
    std::string port{"0"};

public:
    IPAddress() = default;
    void setIp(const char* ip);
    void setPort(const char* port);
    bool isValidIp() const;
    bool isValidPort() const;
    std::string getIp() const;
    std::string getPort() const;
};