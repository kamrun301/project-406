import serial
import json
import paho.mqtt.client as mqtt


ser = serial.Serial('COM15', 9600)


client = mqtt.Client()
client.username_pw_set("ekapzwpxa3q6tzk8o0qq") 
client.connect("127.0.0.1", 1883, 60)       

print("Starting MQTT Bridge...")

while True:
    line = ser.readline().decode('utf-8').strip()
    try:
       
        data = json.loads(line)
        client.publish("v1/devices/me/telemetry", json.dumps(data))
        print("Published:", data)
    except json.JSONDecodeError:
        
        continue

