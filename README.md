# BeoControl
This project is made for Bang & Olufsen IR eye and Beosound Century radio. It is a combination of [BeoButton](https://github.com/styppen/BeoButton) and [Beomote](https://github.com/christianlykke9/Beomote) libraries.

A Sparkfun Pro micro is fitted in the chassis of IR eye and the Century. In the IR eye, it is receiving IR commands, button presses and controls the leds, as opposed to the century, where 4 buttons are controlled. This is made to be able to control the Century via MQTT, HomeAssistant or HomeKit. 

Both microcontrollers are connected to a RaspberryPi. It can be used as a Airplay speaker using [Shairport-sync](https://github.com/mikebrady/shairport-sync) and then you can Play/pause or skip a song using your Bang & Olufsen remote instead of looking for your phone. 

**Beo IR eye**

I have used the pro micro because of it small size. If you also want to fit a backplate on the IR eye, use a pro micro without headers, so solder only the pins you are going to use. Also choose a micro USB with a small head, so it can fit inside the chassis. I got a hold of an IR eye without the backplate, so I designed my own. 

You can also use an ESP8266 directly like in [BeoButton](https://github.com/styppen/BeoButton), but you still need to supply power to it. I have it connected to a RaspberryPi and then I communicate with them via serial using a Python script, which runs as a service. When configuring the service, I used [these](https://gist.github.com/emxsys/a507f3cad928e66f6410e7ac28e2990f) instructions.

You can these remotes:
- Beolink 1000
- Beo4

**Beo Control**

I wanted to control the Century, but i still wanted to be able to use the remote. Therefore I added a microcontroller inside the Century. I found connections for 4 buttons, which I wanted to control.
- Radio
- Tape
- Aux
- Standby

I have achieved this by soldering onto the control panel. The microcontroller switches the buttons using Sharp PC817 Optocoupler. You can also use relays, but there is not too much space inside the Century, and they are noisy. Supposedly you can remove the Tape module as [pinter75](https://forum.beoworld.org/forums/t/15622.aspx), but I wanted to keep the tape module. I have included a picture where to place it, you have to remote the circuit board to access it and cut a hole in the bottom of the casing for the USB cable. I have also included a schematic from the service manual, so you can control other buttons if you want to.

***The glas door will however open with  each simulated button press!***

**MQTT**

In order to receive th commands from the IR eye and to control the Century, you will need an MQTT server. I have included a file you can import into NodeRed, so you have all the nodes. You might have to change the IP address on all the MQTT publish and subscribe nodes.

**Home Assistant**

The Century is made to work with home assistant as well. You can turn it off and on and also select the source. You can also use the commands from the IR eye as a trigger in Home Assistant. I have set up the leds on the IR eye as well, so you can use them as lights. 

I am running Raspbian on my Raspberry and I performed a [manual](https://www.home-assistant.io/installation/raspberrypi) installation of HomeAssistant Core.

The media player part is a bit tricky, but it works. You can control the Century via media_player or using the input_select. The input_select has to be there for correct operation. That means you have to include contents of all configuration, automations, scripts and customize.yaml. It is made in a way, that if you turn the radio using the Remote, the state in Home Assistant is also updated. **However you need to have the IR eye in the same room as the century.**

**HomeKit**

I have included a homekit configuration to the configuration.yaml. Home Assistant might create two HomeKit insatances, add the one called Home Assistant. The Century can be controlled and the source can be changed. The state and the source updates, if you control the Century via the remote or HomeAssistant. 

**AirPlay speaker**

You can connect the RaspberryPi audio output to the Century's AUX port and make it into an AirPlay speaker. **Note it is AirPlay 1, so you cannot group it with other speakers.** 

Follow the steps from [Shairport-sync](https://github.com/mikebrady/shairport-sync). 

When configuring, use this configuration:
`./configure --sysconfdir=/etc --with-configfiles 
    --with-alsa --with-avahi
    --with-ssl=openssl
    --with-systemd
    --with-metadata --with-mqtt-client`
	
I supplied my configuration file for Shairport. You can now use your Bang & Olufsen remote to control your music stream. 
