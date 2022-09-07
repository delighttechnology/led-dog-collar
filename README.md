# LED Dog Collar
<img src="./images/main.jpg" width="700">

Here it is the 𝗗𝗲𝗹𝗶𝗴𝗵𝘁 𝗗𝗼𝗴 𝗖𝗼𝗹𝗹𝗮𝗿 **v1.0**. There are 10 colorfull patterns which can be switched by a press of a button, 11th mode cycle through each pattern every 30 sec. This project was created especially for my friend's dog called Duch (eng. Ghost).<br /><br />
Inside of the enclosure there is a custom made PCB which is a WS2812B LED controller. Powered by 3.7v LiPo battery, ATTiny85 MCU with battery charging LED indicators and one button to controll them all. One click start the MCU, then you can switch animations by single click and long press turns off the controller. I reached out the limits of the memory of ATTiny85 so there is only 10 animations. <br />
The box was created in Fusion360. It took dozens ideas to make it work as it is now with this bending and blurring tube. At the end I decided to create a collar that is put over the dog's head as the material that diffuse leds is really stiff and unfold itself to the straight line. In general any clip fastening is marking collar shape not round. I would definitely look for another diffusing material for version 2.0.


## Table of contents
* [Features](#Features)
* [PCB](#PCB)
	* [Schematics](#Schematics)
* [Setup](#setup)
* [License](#License)

## Features
- ATTiny85 microcontroller
- TP4056 LiPo Battery Charger with LEDs indicators
- Simple One-Button user interface
- WS2812b LEDs
	
## PCB
<p float="left">
  <img src="./images/pcb1.png" width="350" />
  <img src="./images/pcb2.png" width="350" /> 
</p>



 <img src="./images/pcb_photo1.jpg" width="350" />


### Schematics

The chellange was to create the circut that could be turned ON and OFF without using the microcontroler (which would need to be powered all the time) but just with the usage of electronics. I managed to find below schematic which seems to be doing the job.
 <img src="./images/onoffcircut.png" width="350" />

More details [here](https://forum.arduino.cc/t/enhanced-mode-mosfet-to-connect-reset-to-button-when-in-deep-sleep/691669/5)

## Setup
To run this project, install it locally using npm:

```
$ cd ../lorem
$ npm install
$ npm start
```

# header H1
## header H2
### header H3
#### header H4

## License

Copyright © 2022, [Andrzej Strzala](https://www.linkedin.com/in/andrzejstrzala/).


