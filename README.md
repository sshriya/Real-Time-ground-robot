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

### Break down into end to end tests

Explain what these tests test and why

```
Give an example
```

### And coding style tests

Explain what these tests test and why

```
Give an example
```

## Deployment

Add additional notes about how to deploy this on a live system

## Built With

* Dropwizard - Bla bla bla
* Maven - Maybe
* Atom - ergaerga

## Contributing

Please read [CONTRIBUTING.md](CONTRIBUTING.md) for details on our code of conduct, and the process for submitting pull requests to us.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/your/project/tags). 

## Authors

* **Billie Thompson** - *Initial work* - [PurpleBooth](https://github.com/PurpleBooth)

See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Hat tip to anyone who's code was used
* Inspiration
* etc

