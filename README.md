# Real-Time-ground-robot

1. Get internet on BBB - Debian
USB - sharing: on BBB side
    1. ssh 192.168.7.2 -l root
    2. ifconfig usb0 192.168.7.2
    3. route add default gw 192.168.7.1

on Host Linux side
    1. sudo su \\
    #wlan0 is my internet facing interface, eth5 is the BeagleBone USB connection\\
    2. ifconfig eth5 192.168.7.1\\
    3. iptables --table nat --append POSTROUTING --out-interface wlan0 -j MASQUERADE\\
    4. iptables --append FORWARD --in-interface eth5 -j ACCEPT\\
    5. echo 1 > /proc/sys/net/ipv4/ip_forward\\
      \\
on BB : might be needed\\
    1. echo "nameserver 8.8.8.8" >> /etc/resolv.conf
    

2. Installing xenomai
http://syrianspock.github.io/embedded-linux/2015/08/03/xenomai-installation-on-a-beaglebone-black.html
