/**
 * CONFIDENTIAL - FORD MOTOR COMPANY
 * This is an unpublished work, which is a trade secret, created in
 * 2022. Ford Motor Company owns all rights to this work and intends
 * to maintain it in confidence to preserve its trade secret status.
 * Ford Motor Company reserves the right to protect this work as an
 * unpublished copyrighted work in the event of an inadvertent or
 * deliberate unauthorized publication. Ford Motor Company also
 * reserves its rights under the copyright laws to protect this work
 * as a published work. Those having access to this work may not copy
 * it, use it, or disclose the information contained in it without
 * the written authorization of Ford Motor Company.
 */
#include <gps_read.hpp>

void GpsData::openGpsPort(const std::string& host, const std::string& port) {
    auto res = gps_open(host.c_str(), port.c_str(), &gpsdata);

    std::cout << "GPSD_API_MAJOR_VERSION=" << GPSD_API_MAJOR_VERSION << std::endl;
    
    if(res != 0) {
        std::cerr << "Cannot port! code: " << errno << "reason: " << gps_errstr(errno) << std::endl;
        die(GPS_STATUS::GPS_ERROR);
        return;
    }

    gps_stream(&gpsdata, WATCH_ENABLE, nullptr);

    std::cerr << "GPS port is opened\n";
    isOpen = true;
}

void GpsData::closeGpsPort() {
    std::cout << "Closing GPS port...\n";
    die(GPS_STATUS::CGPS_QUIT);
}

void GpsData::readGpsData() {
    std::cout << "Read GPS device\n";
    if(!isGpsPortOpen()) {
        std::cerr << "GPS port is not opened\n";
        return;
    }

    for(int i = 0; i < GpsData::NO_OF_ITERATION; ++i) {
        int res;

        res = gps_waiting(&gpsdata, GpsData::TIMEOUT_SECONDS);

        if(res == 0) {
            std::cerr << "Error timeout! code: " << errno << "reason: " << gps_errstr(errno) << std::endl;
            std::cout << "Trying again\n";

            if(!isGpsPortOpen()) {
                std::cout << "Port is already closed\n";
                return;
            }
            
            continue;
        }
        else {
            std::cout << "Successfully got data\n";
        }

#if GPSD_API_MAJOR_VERSION >= 7
        res = gps_read(&gpsdata, nullptr, 0);
#else
        res = gps_read(&gpsdata);
#endif

        if(res == -1) {
            std::cerr << "error occured reading gps data. code: " << errno << "reason: " << gps_errstr(errno) << std::endl;
            die(GPS_STATUS::GPS_ERROR);
            continue;
        }

        if (TIME_SET == (TIME_SET & gpsdata.set)) {
#if GPSD_API_MAJOR_VERSION >= 7
            std::cout << "gpsdata.fix.time.tv_nsec=" << gpsdata.fix.time.tv_nsec << std::endl;
            std::cout << "gpsdata.fix.time.tv_sec=" << gpsdata.fix.time.tv_sec << std::endl;
#else
            std::cout << "gpsdata.fix.time=" << gpsdata.fix.time << std::endl;
#endif
            return;
        }

        std::cout << "n/a\n";
    }

    std::cout << "No GPS data available\n";
    die(GPS_STATUS::GPS_TIMEOUT);
}

long GpsData::getGpsTimeStampSecond() const {
#if GPSD_API_MAJOR_VERSION >= 7
    return gpsdata.fix.time.tv_sec;
#else
    return static_cast<long>(gpsdata.fix.time);
#endif
}

long GpsData::getGpsTimeStempNanoSecond() const {
#if GPSD_API_MAJOR_VERSION >= 7
    return gpsdata.fix.time.tv_nsec;
#else
    return 0;
#endif  
}

void GpsData::die(const GPS_STATUS& gps_status) {
    if(isGpsPortOpen()){
        isOpen = false;
    }
    else {
        std::cout << "Port is already closed\n";
        return;
    }

    switch (gps_status)
    {
        case GPS_STATUS::CGPS_QUIT:
            std::cout << "Quitting GPS\n";
            break;

        case GPS_STATUS::GPS_GONE:
            std::cerr << "GPS hung up.\n";
            break;

        case GPS_STATUS::GPS_ERROR:
            std::cerr << "GPS read returned error.\n";
            break;

        case GPS_STATUS::GPS_TIMEOUT:
            std::cerr << "GPS timeout.\n";
            break;
    }

    gps_close(&gpsdata);
}

GpsData::~GpsData() {
    if(!isGpsPortOpen()) {
        die(GPS_STATUS::CGPS_QUIT);
    }
}