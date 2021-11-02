# TikTokFlow
Array of leds that changes randomly as to create a different course pattern in between 3 sets of 3 led circles

![Alt text](248640171_10159488980759481_7952433724348510257_n.jpg?raw=true "Tik Tok Flow")


## Materials you need

> 1x Arduino Nano

> 5v OR 12v addresseable leds strip (not the GRGB type. Find the ones that have 5v,DIN,Ground or 12v,DIN,Ground connections).

> Lotsa cabling

> Ardunino IDE and FASTLED library (google these if you don't know what they are or how to install them)



## How to assemble it

1. Start by soldering ALL the WS2812 strip Ground cable (black) to Arduino ground, ALL WS2812 strip 5V cable (red) to Arduino 5V.
2. IF you are using 12v just solder the red cable from WS2812 strip 12V to Arduino VIN
3. Solder each of the 3 WS2812 strip din cable per unit to 
4. 1st unit: Arduino D2, D3, D4
5. 2st unit: Arduino D5, D6, D7
6. 3rd unit: Arduino D9, D10, D11
7. Upload the code to the arduino. Remember to change the NUM_LEDS if you have a different number led strips then the one in the code.




Original gate idea by Drone Junkie.
Visit them @ http://dronejunkie.co.uk
