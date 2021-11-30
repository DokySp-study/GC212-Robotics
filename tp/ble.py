import asyncio
from bleak import BleakClient, cli, discover
import pandas as pd
import joblib
import collections

device_name = "BLETEST"
device_service = "0000ffe0"
device_characteristic = "0000ffe1"

roll1 = None
pitch1 = None
roll2 = None
pitch2 = None

df = pd.DataFrame({
    "r1": [],
    "r2": [],
    "p1": [],
    "p2": [],
    "gesture":[], 
})





def notify_callback(sender: int, data: bytearray, df):

    received = data.decode()[:len(data)-2]

    tmp = received.split("/")

    roll1 = int(float(tmp[0]))
    pitch1 = int(float(tmp[1]))
    roll2 = int(float(tmp[2]))
    pitch2 = int(float(tmp[3]))
    
    if roll1 != None and roll2 != None and pitch1 != None and pitch2 != None:
        print("===================")
        print("111: " + str(roll1) + " | " + str(pitch1))
        print("222: " + str(roll2) + " | " + str(pitch2))

        df = df.append({
            "r1": roll1,
            "r2": roll2,
            "p1": pitch1,
            "p2": pitch2,
        }, ignore_index=True)
        
        roll1 = None
        pitch1 = None
        roll2 = None
        pitch2 = None
        
        res = collections.Counter(model.predict(df))

        print(max(res))









async def run():
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

    client = BleakClient(target_device.address)
    print(client)
    await client.connect()



    services = await client.get_services()
    for s in services:
        if str(s.uuid).count(device_service) > 0:
            target_service = s
            break
        
    print(target_service)



    for c in target_service.characteristics:
        if str(c.uuid).count(device_characteristic) > 0:
            target_characteristic = c
            break

    print(target_characteristic)

    # await client.write_gatt_char(target_characteristic, bytes(b's'))
    # start notify
    await client.start_notify(target_characteristic, notify_callback, df)
          
    # client 가 연결된 상태라면
    if client.is_connected:
        # 1초간 대기
        await asyncio.sleep(120) 
        print('try to deactivate notify.')
        # 활성시켰단 notify를 중지 시킨다.
        await client.stop_notify(target_characteristic)


    await client.disconnect()








model = joblib.load("./tp/dtc_g.pkl")
loop = asyncio.get_event_loop()
loop.run_until_complete(run())
print('done')