# Real Time ground Robot

This project implements as autonomous behavious on a differential drive robot as a real time systems. BeagleBone Black rev c with Debian, patched withXenomai has been used. The hardware is a land rover 5. 

## Getting Started

These instructions will help setting up the beaglebone black with debian and xenomai. 

### Getting internet

For USB internet sharing between host computer and Beaglebone, do the following on Beaglebone side:

```
ssh 192.168.7.2 -l root
ifconfig usb0 192.168.7.2
route add default gw 192.168.7.1
```
On the host computer, do the following:

```
 sudo su
```
wlan0 is my internet facing interface, eth5 is the BeagleBone USB connection
```
    ifconfig eth5 192.168.7.1
    iptables --table nat --append POSTROUTING --out-interface wlan0 -j MASQUERADE
    iptables --append FORWARD --in-interface eth5 -j ACCEPT
    echo 1 > /proc/sys/net/ipv4/ip_forward
```
    
might be needed:
```
echo "nameserver 8.8.8.8" >> /etc/resolv.conf
```


### Installing

To install Xenomai, the following blog post was followed: http://syrianspock.github.io/embedded-linux/2015/08/03/xenomai-installation-on-a-beaglebone-black.html

Building the user space:
git clone the xenomai folder (2.6.x) or get it from another repo:
```
wget http://download.gna.org/xenomai/stable/xenomai-2.6.3.tar.bz2
tar xvjf xenomai-2.6.3.tar.bz2
```
Build and install
```
./configure
make
sudo make install
```
## Running the tests - xenomai

To test system latencies
```
/usr/xenomai/bin/latency
```
##Folder structure
The rts_rover folder contains rt_scripts that saves all the pin control / example scripts to use xenomai. The cScripts on the other had, contains codes written in C and uses memory based GPIO access to control the robot. The scripts in rt_script can be build by including the name of the file in Makefile and running:

```
make
```

The c files can be build as follows:
```
gcc testScripts.c -o testScripts
```

## Common issues
While trying to use GPIO0,2,3 using nmap, bus error poppoed up. This is because clock to these gpio is not configured by default. A simple solution is to do the following:

```
echo 5 > /sys/class/gpio/export
echo 65 > /sys/class/gpio/export
echo 105 > /sys/class/gpio/export
```
Server certficate verification failed:
```
export GIT_SSL_NO_VERIFY=1
```
## Getting qep to work
```
git clone https://github.com/Teknoman117/beaglebot
```
Copy the qep-*.dtbo to /lib/firmware
```
cd /lib/firmware
echo bone-qep2b > $SLOTS
find /sys |grep eqep
```
cat ../position to display tick counts.

Pins: 
```
eqep 1B P8_33
eqep 1A P8_35

eqep 2A P8_41
eqep 2B P8_42
```
The paths for the sysfs entries on the beaglebones are

/sys/devices/ocp.*/{epwmss_addr}.epwmss/{eqep_addr}.eqep/
```
For eQEP0, the epwmss address is 48300000 and the eqep address is 48300180

For eQEP1, the epwmss address is 48302000 and the eqep address is 48302180

For eQEP2, the epwmss address is 48304000 and the eqep address is 48304180
```


## Flashing a new image on BBB
1. Get the lastest flasher image from http://elinux.org/Beagleboard:BeagleBoneBlack_Debian#Flasher:_.28console.29_.28BeagleBone_Black.2FGreen_eMMC.29

Currently it was:

## ADC 
Check for the available Device tree overlay, load overlay and the read adc value on cmd
```
1. ls /lib/firmware/ | grep ADC
2. echo PyBBIO-ADC > $SLOTS
3. cat /sys/bus/iio/devices/iio\:device0/in_voltage0_raw

```
cScripts contains adcRead.c which can be used to read adc values. 
ADC pins:
ADC0     P9_39
ADC1     P9_40  
ADC2     P9_37
ADC3     P9_38
ADC4     P9_35
ADC5     P9_39
ADC6     P9_33

The device tree can be loaded on boot by :
```
nano /etc/default/capemgr
CAPE=PyBBIO-ADC
CAPE=bone_eqep1
```





