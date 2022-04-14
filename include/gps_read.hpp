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
#ifndef _INCLUDE_GPS_READ_HPP_
#define _INCLUDE_GPS_READ_HPP_
#include <gps.h>
#include <unistd.h>
#include <iostream>
#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <string>

class GpsData {
    struct gps_data_t gpsdata;
    int isOpen{false};
    enum class GPS_STATUS { CGPS_QUIT, GPS_GONE, GPS_ERROR, GPS_TIMEOUT };
    void die(const GPS_STATUS& gps_status);
public:
    GpsData() = default;
    ~GpsData();
    void openGpsPort(const std::string& host, const std::string& port);
    void closeGpsPort();
    void readGpsData();
    bool isGpsPortOpen() const {
        return isOpen;
    };

    long getGpsTimeStampSecond() const;
    long getGpsTimeStempNanoSecond() const;

    /* Deleted functions */
    GpsData(const GpsData&) = delete;
    GpsData(const GpsData&&) = delete;
    GpsData& operator=(const GpsData&) = delete;
    GpsData& operator=(const GpsData&&) = delete;

    static constexpr int TIMEOUT_SECONDS = 1000000; /* gps_waiting timeout is defined in microseconds */
    static constexpr int NO_OF_ITERATION = 10; /* Number of times the counter should wait */
};
#endif // _INCLUDE_GPS_READ_HPP_