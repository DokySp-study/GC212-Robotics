import asyncio
from bleak import BleakClient, cli, discover
import pandas as pd
import joblib
import collections
import copy
from pynput.keyboard import Key, Controller



# Device preset
device_name = "BLETEST"
device_service = "0000ffe0"
device_characteristic = "0000ffe1"

roll1 = None
pitch1 = None
roll2 = None
pitch2 = None

global df
df = pd.DataFrame({
    "r1": [],
    "r2": [],
    "p1": [],
    "p2": [],
})

global kbControl
kbControl = Controller()

global prevIdx
prevIdx = 0





# Main business logic
def notify_callback(sender: int, data: bytearray):

    # Receiving data
    received = data.decode()[:len(data)-2]

    tmp = received.split("/")

    roll1 = int(float(tmp[0]))
    pitch1 = int(float(tmp[1]))
    roll2 = int(float(tmp[2]))
    pitch2 = int(float(tmp[3]))
    
    if roll1 != None and roll2 != None and pitch1 != None and pitch2 != None:
        # print("===================")
        # print("111: " + str(roll1) + " | " + str(pitch1))
        # print("222: " + str(roll2) + " | " + str(pitch2))
        global df
        global kbControl
        global prevIdx

        # Build and manage dataframe for ML
        dft = []

        df = df.append({
            "r1": roll1,
            "r2": roll2,
            "p1": pitch1,
            "p2": pitch2,
        }, ignore_index=True)


        if len(df) == 20:
            dft = df.iloc[0:20, :]
        elif len(df) == 30:
            dft = df.iloc[10:30, :]
            dft.reset_index()
            df = dft
        
        roll1 = None
        pitch1 = None
        roll2 = None
        pitch2 = None
        

        # Detecting motion
        if len(dft) != 0:
            # res = collections.Counter(model.predict(dft))
            # res = max(res)
            # print(res)
            val =  (model.predict(dft)).sum() / 15 
            if 0.9 < val and val < 1.1:
                res = 1
            elif 1.9 < val and val < 2.1:
                res = 2
            else:
                res = 0
            print(res)

            if prevIdx != res:
                prevIdx = res

                if res == 1:
                    kbControl.press(Key.right)
                    kbControl.release(Key.right)
                elif res == 2:
                    kbControl.press(Key.left)
                    kbControl.release(Key.left)
                # elif res == 3:
                #     kbControl.press(Key.esc)
                #     kbControl.release(Key.esc)





# Async task to connect with device through BLE
async def run():

    # Find target device
    devices = await discover()

    target_device = None
    target_service = None
    target_characteristic = None

    for d in devices:
        tmp_name = str(d.name)
        if len(tmp_name) != 0:
            if tmp_name.count(device_name) > 0:
                target_device = d
    
    print(target_device)


    # Find target BLE service
    client = BleakClient(target_device.address)
    print(client)
    await client.connect()

    services = await client.get_services()
    for s in services:
        if str(s.uuid).count(device_service) > 0:
            target_service = s
            break
        
    print(target_service)


    # Find target characteristics
    for c in target_service.characteristics:
        if str(c.uuid).count(device_characteristic) > 0:
            target_characteristic = c
            break

    print(target_characteristic)


    # Start notify to communicate
    # await client.write_gatt_char(target_characteristic, bytes(b's'))
    await client.start_notify(target_characteristic, notify_callback)

    # Connection control
    if client.is_connected:
        # Connection time
        # await asyncio.sleep(120) 
        print('try to deactivate notify.')
        # 활성시켰단 notify를 중지 시킨다.
        await client.stop_notify(target_characteristic)

    # End async communication
    await client.disconnect()





# Main code
# Load trained ML model
model = joblib.load("./sample.pkl")
# Run async task for communicate with device
loop = asyncio.get_event_loop()
loop.run_until_complete(run())
