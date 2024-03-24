Project Name:  Blot Motor Controller Board
Project date:  2024-01-21


In Shenzhen Leo and I discussed trying out a new version of the Blot controller PCB that uses normal USB-C (non-PD) with a boost circuit to generate the required 9V to run the two stepper motors.  This is my go at it.

Ideally it would all operate from one USB connector if the current is low enough.



PCB Versions:
-------------

Version 2.2b1:
Production:  JLCPCB, 1.6mm, 4 Layer, Green
Date: TBD

* create a dedicated ESP32-C3-WROOM (Mini?) version.  Gives more GPIO and less soldering


Version 2.1b2:
Production:  JLCPCB, 1.6mm, 4 Layer, Green
Date: TBD

* are R9/R17 (motor decay rate) really needed? If Open, it's set to 16uSec Smart Tune
* test out laser cut plastic solder paste stencil
Done: Fix L2 inductor footprint.  Needs to be bigger?
Done: move L2 1mm away from U3
Done: purchase correct 1A polyfuse
Done: purchase backup 1.5A and 2A + 2.5A 0805 polyfuses
Done: was PWM Vref ok to work with?  Yes and cheapest option.
Done: was DAC Vref ok to work with? (increase 3v3 trace width).  Removed. PWM ok.
Done: delete Vref Pots if not needed, otherwise just use 1 Pot to feed both from 3V3
Done: measure power draw: 5V @ 1.1A for two small motors at 9V.
Done: could add a Fuse LED to indicate when it's activated
Done: could add a programmable LED on A3.  It looks to be available
Done: write pinout data on backside of PCB
Done: change R12 to 33K to allow up to 1.4A output at 9V
Done: Add a XC6227 LDO, to power MCU module when running from 2nd USB connector!
Done: add a 22uF to the Servo power line
Done: swap Blot_PCB_Back_v2.1b1out B5819W (1A) dioes for SS24 (2A)
Done: purchase correct 100uF Caps
Done: change M1 from DVDD to 3V3
Done: on backside, label Motor outputs:  A1/A2, B1/B2
Done: add 3V3, both USB 5V inputs as testpoints and label
Done: connect nSleep to 3V3 instead of DVDD
Done: fix R4/R5 labels
No: could add a Fault LED (pullup to 3V3). Space?


Version 2.1b1:
Production:  JLCPCB, 1.6mm, 4 Layer, Green, 5 PCBs
Date: 2024-02-20

* Initial version.

0  IO2 PWM Dac
1  IO3 Motor Enable
2  IO4
3  IO5
4  IO6
5  IO7
6  IO21
7  IO20
8  IO8
9  IO9
10 IO10
11 3V3
12 GND
13 5V
