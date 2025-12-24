import serial
import json
import paho.mqtt.client as mqtt

# Serial connection
ser = serial.Serial('COM9', 9600)

# MQTT setup
client = mqtt.Client()
client.username_pw_set("fgfjjm2qipnpk997dyfo")
client.connect("127.0.0.1", 1884, 60)

print("Starting MQTT Bridge...")

# Buzzer thresholds
SOUND_THRESHOLD = 100
WATER_THRESHOLD = 10

while True:
    try:
        # Decode serial line safely
        line = ser.readline().decode('utf-8', errors='ignore').strip()
        if not line:
            continue

        # Parse JSON from Arduino
        data = json.loads(line)

        # Compute buzzer state if not sent by Arduino
        buzzer_state = 0
        if data['sound'] > SOUND_THRESHOLD and data['water'] > WATER_THRESHOLD:
            buzzer_state = 1
        data['buzzer'] = buzzer_state

        # Publish telemetry to ThingsBoard
        client.publish("v1/devices/me/telemetry", json.dumps(data))
        print("Published:", data)

    except json.JSONDecodeError:
        # Skip lines that are not JSON
        continue
    except serial.SerialException:
        print("Serial error! Check Arduino connection.")
        break
