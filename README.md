thulog
======

Description: Temperature &amp; Humidity Usb Logger device based on DHT22 and attiny2313 mcu



*todo*
========
- [ ] Firmware
     - [ ] setup sleep mode 
     - [ ] setup watchdog to wake up the MCU each 4 seconds and blink the LED
     - [ ] read sensor functionality 
	 - [x] rename usb device name and vendor
	 - [ ] commit usb windows and linux drivers in sources
- [ ] PCB 
     - [ ] Add Kicad project into pbc folder
     - [ ] schema design
     - [ ] pcb layout 
- [ ] Test console consumer application
- [ ] Server side application
- [ ] Web interface emoji! :sparkles:


Repository Contents
========
* /docs - usefull documents related to attiny2313, dht22
* /src -  code folder
	- /firmare - attiny2313 firmware c code
	- /server  - server side consumer
* /hardware - Kicad project for pcb	

License Information
========

License is [beerware](http://en.wikipedia.org/wiki/Beerware)

Distributed as-is; no warranty is given.
