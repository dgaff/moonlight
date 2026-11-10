# How the auto-reset circuit works
(Claude explanation)

U2 is a pair of NPN transistors with built-in resistors, driven by the CH340C's RTS# and DTR# pins:

One transistor connects to RST. It pulls RST low when RTS is asserted and DTR isn't. The other connects to GPIO0 (U2 pin 3). It pulls GPIO0 low when DTR is asserted and RTS isn't. Each transistor's base is driven by one signal and its emitter by the other, so it only turns on when the two lines are in opposite states. esptool uses this to put the board into flash mode: it holds GPIO0 low while pulsing RST. So D3 connects to the CH340C through U2.

There can be a risk of driving GPIO0 as an output. The GPIO0 transistor only turns on while DTR and RTS are in opposite states. In normal running, with the port closed or a monitor holding both lines the same, it's off and your output on D3 conflicts with nothing. If a monitor does leave the lines split, the transistor pulls against the ESP's output pin. That limits how high the pin can drive, but it isn't likely to damage anything.

The concern that could apply is boot strapping.

GPIO0 has a 12k pull-up resistor (R10) and must read high when the chip powers up or resets, or the board boots into flash mode instead of running your sketch. Whether that's a problem depends on what your LED segment on D3 looks like to the pin while the ESP is starting up:

Driven through a transistor or MOSFET gate, or an LED wired to 3.3 V (the pin pulls it low to light it): GPIO0 stays high at boot. That's fine. An LED plus resistor from D3 to GND, or an NPN base resistor to GND: this can pull GPIO0 below the high threshold against the 12k pull-up, and the board will sometimes boot into flash mode. A silicon LED usually conducts too little at 3.3 V through 12k to cause this, but a low-forward-voltage LED or a base resistor to ground can. The same reasoning applies to D4 (GPIO2, which must be high at boot, with pull-up R11) and D8 (GPIO15, which must be low at boot, with pull-down R5).

If the board always boots straight into your sketch, including after a power cycle with the LEDs connected, your wiring is fine. If you tell me how the segments are driven, I can say for sure.

(I noted that I'm driving the LED segments through a transistor.)

That's fine if the transistors are MOSFETs. If they're NPN transistors with the emitter to ground, D3 (GPIO0) and D4 (GPIO2) could cause trouble at boot.

Why an NPN base matters here

While the ESP is starting up, its pins aren't driven, so GPIO0 sits wherever the 12k pull-up and the transistor's base circuit leave it. The base-emitter junction clamps at about 0.7 V, so the pin settles at:

V(GPIO0) ≈ 0.7 V + (2.6 V × R_base) / (12k + R_base)

| Base resistor | GPIO0 at boot | Result |
| :---: | :---: | :---: |
| 1k | about 0.9 V | reads low, boots into flash mode |
| 4.7k | about 1.4 V | in the undefined zone, unreliable |
| 10k | about 1.9 V | marginal |
|47k or more | about 2.8 V | reads high, boots normally |

The ESP needs roughly 2.5 V or more to read a pin as high.

What applies to your setup

MOSFETs: the gate draws no current, so the pull-up holds GPIO0 high. You're fine on all pins.
NPN transistors: D3 and D4 need a base resistor of 47k or more. That limits the LED current to about 5 mA per transistor, which may be enough for your segments. Alternatively, move those two segments to safe pins: D0 (GPIO16) is free, and RX (GPIO3) works if you give up serial input. D8 (GPIO15) is fine either way, because it needs to be low at boot and an NPN base helps hold it there.

A quick check

Hold down the board's reset button and measure D3 to GND with a meter. While RST is held low, the ESP leaves its pins un-driven, so you'll read exactly the voltage it sees at boot. If it reads above about 2.5 V, you're fine. Do the same on D4.
