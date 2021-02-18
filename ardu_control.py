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
    time.sleep(1)
    mes = str(message.payload.decode("utf-8"))
    snd = mes + "\n"
    #print(mes)
    if mes == "OFF" or mes == "off": ## the switch in home assistant takes needs ON or OFF
        l1 = "OFF" 
    else:
        l1 = "ON"
    client.publish("beo/state",l1, retain=True)
    print(mes)
    print(l1)
    ser.write(snd.encode('utf-8')) #send the command to arduino

if __name__ == '__main__':
    Connected = False   #global variable for the state of the connection
    broker_address= "192.168.0.163" #address to your mqtt server
    port = 1883
    #user = NULL
    #password = NULL
    client = mqttClient.Client("beo")               #create new instance
    #client.username_pw_set(user, password=password)

    client.on_connect= on_connect                      #attach function to callback
    client.on_message=on_message
    client.connect(broker_address, port=port)          #connect to broker
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1) #might meed to change the port
    ser.flush()
    client.loop_start()
    client.subscribe("beo/set")
    client.subscribe("beo/src")
    while Connected != True:    #Wait for connection
    	time.sleep(0.1)
    try:
        while True:
            #ser.write(l2.encode('utf-8'))
            #if ser.in_waiting > 0:
                #line = ser.readline().decode('utf-8').rstrip()
               # cmd = line
            time.sleep(2)
            #print("works")
    except KeyboardInterrupt:
        client.disconnect()
        client.loop_stop()	