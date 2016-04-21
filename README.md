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


