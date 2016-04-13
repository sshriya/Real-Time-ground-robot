# Real-Time-ground-robot

1. Get internet on BBB - Debian
USB - sharing: on BBB side
    ssh 192.168.7.2 -l root
    ifconfig usb0 192.168.7.2
    route add default gw 192.168.7.1

on Host Linux side
    sudo su
    #wlan0 is my internet facing interface, eth5 is the BeagleBone USB connection
    ifconfig eth5 192.168.7.1
    iptables --table nat --append POSTROUTING --out-interface wlan0 -j MASQUERADE
    iptables --append FORWARD --in-interface eth5 -j ACCEPT
    echo 1 > /proc/sys/net/ipv4/ip_forward
      
on BB : might be needed
    echo "nameserver 8.8.8.8" >> /etc/resolv.conf
    

2. Installing xenomai
http://syrianspock.github.io/embedded-linux/2015/08/03/xenomai-installation-on-a-beaglebone-black.html
