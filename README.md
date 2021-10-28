# TikTokFlow
Array of leds that changes randomly as to create a different course pattern in between 3 sets of 3 led circles

![Alt text](248640171_10159488980759481_7952433724348510257_n.jpg?raw=true "Tik Tok Flow")


## Materials you need

> 1x Arduino Nano PER SLAVE UNIT (3 in this case) (or an uno if you have one should also work)

> 1x Arduino Nano for the MASTER that controls all slave units (or an uno if you have one should also work)

> 1 DIODE (  >|  ) per slave unit.   

> 5v addresseable leds (not the GRGB type. Find the ones that have 5v,DIN,Ground connections).



> Lotsa cabling



## How to assemble it ( per slave unit )

1. Start by soldering ALL the WS2812 strip Ground cable (black) to Arduino ground, ALL WS2812 strip 5V cable (red) to Arduino 5V.
2. Solder each of the 3 WS2812 strip din cable to Arduino D2, D3, D4 respectfully.
3. Make as many slave units as you'd like.
4. Upload the slave code to each slave unit. Remember to change the TIKTOKNAME at the start of the code for each of the slave units.
  - and NUM_LEDS if you have a different number led strips then the one in the code.


## How to assemble it ( the master unit )

1. Solder the Ground from the MASTER to ALL the slave Arduino ground and the 5V and to ALL the slave Arduino 5V.
2. Solder 3 diodes to the TX pin of the MASTER ARDUINO. (  >|  )
3. Each of the Diodes will be connected to each RX pin of the slave arduinos.
4. Upload the master code to the MASTER unit. You can change FULLTIME, FLASHTIME and even add more sequences.






Original gate idea by Drone Junkie.
Visit them @ http://dronejunkie.co.uk
