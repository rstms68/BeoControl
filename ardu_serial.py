#!/usr/bin/env python3
import serial
import paho.mqtt.client as mqttClient
import time


def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to broker")
        global Connected                #Use global variable
        Connected = True                #Signal connection
    else:
        print("Connection failed")

def on_message(client, userdata, message):
    l1 = "isled\n" #command to find if a led is on
    time.sleep(1)
    mes = str(message.payload.decode("utf-8"))
    rcv = mes +"\n"
    #print(mes)
    if mes == "timer" or "play":
        ser.write(rcv.encode('utf-8')) #turn leds on or off using a toggle
    ser.write(l1.encode('utf-8')) # sending the isled command

if __name__ == '__main__':
    led1 = 0
    led2 = 0
    istimer = "isled"
    isplay = "isplay"
    l1 = istimer + "\n"
    l2 = isplay + "\n"
    Connected = False   #global variable for the state of the connection
    broker_address= "192.168.0.163" #your mqtt server
    port = 1883
    #user = NULL
    #password = NULL
    client = mqttClient.Client("beo_eye")               #create new instance
    #client.username_pw_set(user, password=password)

    client.on_connect= on_connect                      #attach function to callback
    client.on_message=on_message
    client.connect(broker_address, port=port)          #connect to broker
    ser = serial.Serial('/dev/ttyACM1', 9600, timeout=1) # might need to change the port
    ser.flush()
    client.loop_start()
    client.subscribe("beo_eye/led")
    while Connected != True:    #Wait for connection
    	time.sleep(0.1)
    try:
        while True:
            if ser.in_waiting > 0:
                line = ser.readline().decode('utf-8').rstrip()
                cmd = line
                txt = line.split()
                if txt[0] == "timer": #reading the led state and publishing it on mqtt
                    client.publish("beo_eye/led1",txt[1], retain=True)
                if txt[0] == "play":
                    client.publish("beo_eye/led2",txt[1], retain=True)
                if txt[0] != "timer" and txt[0] != "play": # publishing the IR command
                    client.publish("beo_eye/command",cmd)
                print(cmd)
    except KeyboardInterrupt:
        client.disconnect()
        client.loop_stop()	