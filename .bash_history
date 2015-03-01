cd /sys/devices/
ls
cd ocp.3/
ls
cd pwm_test_P9_22.16/
ls -l
sudo su
ping 8.8.8.8
ifconfig usb0 192.168.7.2
route add default gw 192.168.7.1
ping 8.8.8.8
echo "nameserver 8.8.8.8" >> /etc/resolv.conf
ping 8.8.8.8
ping 8.8.8.8
/sbin/route add default gw 192.168.7.1
ping 8.8.8.8
sudo apt-get update
sudo apt-get install linux-image-3.8.13-xenomai-r72 linux-headers-3.8.13-xenomai-r72 linux-firmware-image-3.8.13-xenomai-r72
sudo reboot
ping 8.8.8.8
ifconfig usb0 192.168.7.2
route add default gw 192.168.7.1
ping 8.8.8.8
wget http://download.gna.org/xenomai/stable/xenomai-2.6.3.tar.bz2
tar xvjf xenomai-2.6.3.tar.bz2
cd xenomai-2.6.3
./configure 
make
sudo make install
cd
/usr/xenomai/bin/latency 
sudo reboot
ls
cd exploringBB/
ls
cd chp06
ls
cd API
ls
cd gpio
ls
nano PWM.
nano PWM.cpp
cd ..
ls
cd ..
ls
cd flash_script/
ls
nano flash.sh
cp flash.sh ~/rtBBB/testRT
cp flash.sh /rtBBB/testRT
cd
mkdir rtBBB/testRT
mkdir rtBBB
cd rtBBB/
mkdir testRT
cp ~/exploringBB/chp06/flash_script/flash.sh pwd
ls
cd testRT/
cp ~/exploringBB/chp06/flash_script/flash.sh togggleLED.sh
ls
more togggleLED.sh 
./togggleLED.sh 
nano togggleLED.sh 
./togggleLED.sh 
echo 49 > /sys/class/gpio/unexport
./togggleLED.sh 
./togggleLED.sh 
./togggleLED.sh 
./togggleLED.sh 
cd
cd exploringBB/chp06/
ls
cd GPIO/
ls
more simple
more simple.cpp 
cp simple.cpp toggleLED_test.cpp
nano toggleLED_test.cpp 
g++ toggleLED_test.cpp GPIO.cpp -o toggleLED_test -pthread
sudo ./toggleLED_test
sudo ./toggleLED_test
sudo ./toggleLED_test
sudo ./toggleLED_test
sudo ./toggleLED_test
sudo ./toggleLED_test
nano toggleLED_test.cpp 
g++ toggleLED_test.cpp GPIO.cpp -o toggleLED_test -pthread
sudo ./toggleLED_test
sudo ./toggleLED_test
sudo ./toggleLED_test
sudo ./toggleLED_test
sudo ./toggleLED_test
sudo ./toggleLED_test
nano toggleLED_test.cpp 
g++ toggleLED_test.cpp GPIO.cpp -o toggleLED_test -pthread
sudo ./toggleLED_test
nano toggleLED_test.cpp 
g++ toggleLED_test.cpp GPIO.cpp -o toggleLED_test -pthread
sudo ./toggleLED_test
sudo ./toggleLED_test
nano toggleLED_test.cpp 
g++ toggleLED_test.cpp GPIO.cpp -o toggleLED_test -pthread
sudo ./toggleLED_test
nano toggleLED_test.cpp 
g++ toggleLED_test.cpp GPIO.cpp -o toggleLED_test -pthread
sudo ./toggleLED_test
sudo reboot
cd /usr/xenomai/
sbin/version
cd sbin/
ls
cd ..
cd bin/
ls
xeno-config --info|grep -i build
./xeno-config --info|grep -i build
xeno-config --info|grep -i build
ls
./xeno-config 
./xeno-config --skin=native --version
pkg-config --cflags libxenomai_rtdm libxenomai_native -D_GNU_SOURCE -D_REENTRANT -D__XENO__ -I/usr/include/xenomai
cd ~/rtBBB/
g++ toggleLED_test.cpp GPIO.cpp -o toggleLED_test -pthread --includedir=/usr/include/xenomai
cd /usr/
ls
cd xenomai/
cd ..
cd include/
ls
cd ..
cd xenomai/
ls
cd bin/
cd ..
mkdir examples && cd examples
ls
cp ~/rtBBB/helloWorld.c helloWorld.c
cd ..
ls
nano ~./profile
nano ~/.profile
cd lib/
ls
cd ..
cd bin/
cd ..
cd examples/
ls
./xeno-config
sudo reboot
ifconfig usb0 192.168.7.2
route add default gw 192.168.7.1
ping 8.8.8.8
sudo apt-get update
/usr/xenomai/bin/latency 
wget http://download.gna.org/xenomai/stable/xenomai-2.6.3.tar.bz2
tar xvjf xenomai-2.6.3.tar.bz2
ls
cd xenomai-2.6.3
./config
./configure 
make
sudo make install
ls
cd scripts/
ls
cd ..
cd examples/
ls
cd native/
ls
nano rtprint.c 
nano Makefile 
xeno-config --xeno-cflags
cd ..
make
make install
ls
cd native/
ls
xeno-load rtprint
cd ..
cd ..
xeno-load rtprint
ls
cd examples/
ls
cd native/
make
./rtprint 
cd
wget http://disi.unitn.it/~abeni/RTOS/Xenomai/
ls
wget disi.unitn.it/~abeni/RTOS/Xenomai/xenotest-1.tgz
ls
rm index.html 
tar xvzf xenotest-1.tgz 
ls
cd RTTest/
ls
make -f Makefile.userspace 
cd 
ls
cd xenomai-2.6.3/examples/
ls
cd native/
ls
cd ..
cp native testScripts
ls
cd native/
ls
cp Makefile ../../testScripts
cp rtprint.c ../../testScripts 
cd ..
cd ..
ls
cd testScripts 
ls
rm testScripts 
mkdir testScripts
ls
cd examples/native/
cp Makefile ../../testScripts
cp rtprint.c ../../testScripts 
cd ..
cd ..
cd testScripts/
ls
nano Makefile 
make
make rtprint.c 
nano Makefile 
make
./rtprint 
sudo reboot
echo EBB-GPIO-Example > $SLOTS
cat $SLOTS
cat $PINS |more
cd /sys/class/gpio/
ls
echo 30 > export
ls
cd gpio30
ls
cat direction 
echo 31 > export
cd ..
echo 31 > export
ls
cd gpio31
cat direction 
echo 1 > value 
echo out > direction
echo 1 > value 
cat $SLOTS
echo -7 > $SLOTS
cat $SLOTS
echo 0 > value 
echo 1 > value 
echo 0 > value 
cd /lib/firmware/
ls bone_pwm*
ls
sudo sh -c "echo bone_pwm_P9_22 > $SLOTS"
sudo sh -c "echo am33xx_pwm > $SLOTS"
cat $SLOTS
cd /sys/devices/ocp.3/pwm_test_P9_22.16/
ls -l
echo 5000 > duty
echo 10000 > period
echo 1 > run
echo 1000 > duty
echo 1 > run
echo 10000 > duty
echo 10 > duty
echo 1 > duty
echo 5000 > duty
echo 10000 > duty
cd
cd exploringBB/chp06/pwm/
ls
more pwm_test.cpp 
nano pwm_test.cpp 
g++ -o pwm_test PWM.cpp util.cpp pwm_test.cpp 
./pwm_test 
cat $SLOTS
cd /sys/devices/ocp.3/
ls -ld pwm*
cd ~/exploringBB/chp06/pwm/
nano pwm_test.cpp 
g++ -o pwm_test PWM.cpp util.cpp pwm_test.cpp 
./pwm_test 
ls
ls
more build
cd ..
ls
cd GPIO
ls
cd ..
ls
mkdir ~/landRover
cp GPIO/.  ~/landRover
cp GPIO/.  ~/landRover/
ls
cd GPIO/
ls
cd ~/landRover/
ls
cd ~/exploringBB/chp06
ls
cp -r GPIO/. ~/landRover/
cd ~/landRover/
ls
rm simple
g++ simple.cpp GPIO.cpp -o simple -pthread
./simple 
cp ~/exploringBB/chp06/pwm/. ~/landRover/
cp -r ~/exploringBB/chp06/pwm/. ~/landRover/
ls
rm pwm_test
more pwm_test.cpp 
cat $SLOTS
g++ -o pwm_test PWM.cpp util.cpp pwm_test.cpp 
./pwm_test 
nano pwm_test.cpp 
g++ -o pwm_test PWM.cpp util.cpp pwm_test.cpp 
./pwm_test 
nano pwm_test.cpp 
g++ -o pwm_test PWM.cpp util.cpp pwm_test.cpp 
./pwm_test 
echo bone_pwm_P9_42 > $SLOTS
echo am33xx_pwm > $SLOTS
cat $SLOTS
echo bone_pwm_P9_14 > $SLOTS
echo bone_pwm_P9_16 > $SLOTS
cat $SLOTS
cd /sys/devices/ocp.3/
la -ld pwm*
ls -ld pwm*
cd ~/landRover/
ls
nano pwm_test.cpp 
g++ -o pwm_test PWM.cpp util.cpp pwm_test.cpp 
./pwm_test 
nano pwm_test.cpp 
nano motorControl.cpp 
nano motorControl.cpp 
nano pwm_test.cpp 
nano motorControl.cpp 
g++ -o motorControl PWM.cpp util.cpp GPIO.cpp motorControl.cpp 
nano motorControl.cpp 
g++ -o motorControl PWM.cpp util.cpp GPIO.cpp motorControl.cpp 
nano motorControl.cpp 
g++ -o motorControl PWM.cpp util.cpp GPIO.cpp motorControl.cpp 
nano motorControl.cpp 
g++ -o motorControl PWM.cpp util.cpp GPIO.cpp motorControl.cpp 
ls
./sim
./simple 
./simple 
more GPIO.h
nano motorControl.cpp 
g++ -o motorControl GPIO.cpp PWM.cpp util.cpp motorControl.cpp 
g++ motorControl.cpp GPIO.cpp PWM.cpp util.cpp -o motorControl -pthread
g++ motorControl.cpp GPIO.cpp PWM.cpp util.cpp -o motorControl -pthread
ls
rm motorControl
g++ motorControl.cpp GPIO.cpp PWM.cpp util.cpp -o motorControl -pthread
cp motorControl.cpp motorControl_2.cpp 
nano motorControl_2.cpp 
g++ motorControl_2.cpp GPIO.cpp -o motorControl_2 -pthread
ls
g++ simple.cpp GPIO.cpp -o motorControl_2 -pthread
rm util.*
ls
g++ simple.cpp GPIO.cpp -o motorControl_2 -pthread
g++ simple.cpp GPIO.cpp -o simple -pthread
nano simple.cpp 
sudo reboot
ls
cd /sys/class/gpio/
ls
echo 49 > export
caat direction
cat direction
cd gpio49
cat direction
echo out >  direction
echo 1 > value
echo 0 > value
cd
cd exploringBB/library/
ls
cd gpio/
ls
cd ../../
ls
cd chp06
ls
cd GPIO/
ls
cp simple.cpp motorControl.cpp
vim motorControl.cpp 
g++ motorControl.cpp GPIO.cpp -o motorControl -pthread 
sudo ./motorControl
vim motorControl.cpp 
g++ motorControl.cpp GPIO.cpp -o motorControl -pthread 
sudo ./motorControl
sudo ./motorControl
vim motorControl.cpp 
g++ motorControl.cpp GPIO.cpp -o motorControl -pthread 
sudo ./motorControl
vim motorControl.cpp 
g++ motorControl.cpp GPIO.cpp -o motorControl -pthread 
sudo ./motorControl
vim motorControl.cpp 
g++ motorControl.cpp GPIO.cpp -o motorControl -pthread 
sudo ./motorControl
vim motorControl.cpp 
g++ motorControl.cpp GPIO.cpp -o motorControl -pthread 
sudo ./motorControl
vim motorControl.cpp 
g++ motorControl.cpp GPIO.cpp -o motorControl -pthread 
sudo ./motorControl
cd
cd exploringBB/chp06/deviceTree/DTSource3.8.13/
ls
cd /boot/uboot/dtbs
cd /boot/uboot/
ls
ls am*
uname -a
cd
cd exploringBB/chp06/overlay/
ls
rm EBB-GPIO-Example-00A0.dtbo 
ls
dtc -0 dtb -o EBB-GPIO-Example-00A0.dtbo -b 0 -@ EBB-GPIO-Example.dts 
dtc -O dtb -o EBB-GPIO-Example-00A0.dtbo -b O -@ EBB-GPIO-Example.dts 
ls
cd build 
more build 
sudo cp EBB-GPIO-Example-00A0.dtbo /lib/firmware/
cd /lib/firmware/
ls
export SLOTS=/sys/devices/bone_capemgr.9/slots
export PINS=/sys/kernel/debug/pinctrl/44e10800.pinmux/pins
sudo nano ~/.profile 
source ~/.profile 
cat $SLOTS
sudo cat $PINS
visudo
sudo su
ls
rm xenomai-2.6.3.tar.bz2 
cd xenomai-2.6.3/
ls
cd examples/
ls
cd native/
ls
cd ../..
ls
cd testScripts/
ls
nano rtprint.c 
./rtprint 
cp rtprint.c ex01.c
nano ex01.c 
ls
nano Makefile 
make
make all
gcc $CFLAGS $LDFLAGS -lnative -lrtdk ex01.c -o ex01
ls
make 
cd ..
cd examples/
ls
cd native/
ls
nano Makefile 
cd ..
cd ..
cd testScripts/
nano Makefile 
make
nano ex01.c 
make
nano ex01.c 
make
./ex01 
sudo reboot
ls
ping 8.8.8.8
ifconfig usb0 192.168.7.1
