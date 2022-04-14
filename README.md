# Testing the time from GPS monitor

This code reads the GPS data from a port. There are various data avaliable in GPS. In this program only time is considered.

## Prerequisites

gps libraries (GPSD) are required to run this program. In ubuntu run below command to install the library.

```shell
sudo apt install gpsd gpsd-clients
Reading package lists... Done
Building dependency tree       
Reading state information... Done
gpsd is already the newest version (3.20-8ubuntu0.4).
gpsd-clients is already the newest version (3.20-8ubuntu0.4).
```

## Flow

* We need to run gpsfake from one terminal. gpsfake is an utility that comes with gpsd-clients. If we don'y have actual GPS connected in the port then we can run gpsfake in one port. It will start gpsd internally. In below example 9999 is the port number.

```shell
gpsfake -P 9999 ~/Downloads/output.nmea
Processing /home/kunalda/Downloads/output.nmea
gpsfake: log cycle of /home/kunalda/Downloads/output.nmea begins.
gpsfake: log cycle of /home/kunalda/Downloads/output.nmea begins.
gpsfake: log cycle of /home/kunalda/Downloads/output.nmea begins.
gpsfake: log cycle of /home/kunalda/Downloads/output.nmea begins.
gpsfake: log cycle of /home/kunalda/Downloads/output.nmea begins.

```

* nmea (National Marine Electronics Association) file contains the GPS data. This file can be created from <https://www.nmeagen.org/> website.

* The code can be compiled by running build.sh script.

```shell
./build.sh
-- Configuring done
-- Generating done
-- Build files have been written to: /home/kunalda/personal_code/gpsmonitor
Consolidate compiler generated dependencies of target gpsread
[100%] Built target gpsread
```

* The program can be run using below command. The port should be same as mentioned in the gpsfake.

```shell
./gpsread localhost 9999
GPSD_API_MAJOR_VERSION=9
GPS port is opened
Read GPS device
Error timeout! code: 92reason: unknown error
Trying again
Successfully got data
n/a
Successfully got data
n/a
Successfully got data
n/a
Successfully got data
gpsdata.fix.time.tv_nsec=270000000
gpsdata.fix.time.tv_sec=1648498578
Seconds=1648498578
NanoSeconds=270000000
Closing GPS port...
Quitting GPS
Port is already closed
```
