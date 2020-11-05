# Moonlight

Got some time in the electronics shop this past weekend, so I worked on my wifi-connected Moon Light. This started life as a nightlight for my daughter when she was young.

<img src="https://cdn.zappy.app/f3b2f2df8dd4d5ebd1dbe57d7378a53a.png" width="400">

It's been in storage for a while, and so I decided I wanted to make it wifi-connected in order for it to automatically set the phase of the moon. I also wanted to make it brighter so it can be seen in the daytime. 

Step 1 was to use my favorite little wifi board with Wemos D1 mini. These things are [super cheap](https://www.amazon.com/Organizer-ESP8266-Internet-Development-Compatible/dp/B081PX9YFV), and you can write quick programs with using the Arduino environment. Because I was planning to drive a string of LEDs per moon segment, I needed to use a transistor to switch the extra current. Here's a quick breadboard test.

<img src="https://cdn.zappy.app/c4f5035c910a8b6c0bbeffeda61ce23f.jpeg" width="400">

Next, I cut up some [LED strip lights](https://www.amazon.com/gp/product/B07SN3M8VW) that are 5V powered (the same voltage as the Wemos board) into strips for each phase of the moon. These replaced the single LED that lit each phase in the original nightlight.

<img src="https://cdn.zappy.app/2dbff8f3bb4d0968bb82710a51eda9f4.jpeg" width="350"><img src="https://cdn.zappy.app/5b11b988c91e33908bc003ed8d63afaf.jpeg" width="350">

Next was to populate a board. Nothing fancy on this job. A quick one-off project isn't really worth laying out and spinning a board. So I just used an old project board with traces made from solder.

<img src="https://cdn.zappy.app/a751c72ff9f99ccded1669ae34d663dc.jpeg" width="350"><img src="https://cdn.zappy.app/0e4fedb29f6fcadf4e5065c54e60c37f.jpeg" width="350">

Then, final reassembly

<img src="https://cdn.zappy.app/7c72ed0e6cd24bacf0d791397594534f.jpeg" width="400"><img src="https://cdn.zappy.app/bb37c7279700b9967f8316f76af937b3.jpeg" width="400">

I wrote a [quick program](https://github.com/dgaff/moonlight/blob/main/moonlight.ino) to sweep through the phases. I still need to write the wifi connected part, and I want to put a simple web api on it so I can remotely control. 

![](https://cdn.zappy.app/37674c8e7b085b6c3a1376db1462dc4e.gif)

**There are no new ideas, of course.**

Unsurprisingly, everything in code has already been solved and there's a [moon phase](https://www.arduino.cc/reference/en/libraries/moonphase/) library already for Arduino. So the rest of this project is mostly cut-and-paste code. Also unsurprisingly, after I embarked on this project, I found out that someone on Instructables [also had this idea](https://www.instructables.com/Arduino-Controlled-Model-Moon-synchronizes-phase-c/), too. They took a different approach, though, favoring a real time clock and keeping it more as a night-light on battery power.

No big plans for this weekend. Will get some more time in the shop to decompress.
