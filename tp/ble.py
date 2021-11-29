import asyncio
from bleak import BleakClient, cli, discover

device_name = "BLETEST"
device_service = "0000ffe0"
device_characteristic = "0000ffe1"



def notify_callback(sender: int, data: bytearray):
    # print('sender: ', sender, 'data: ', data)
    received = data.decode()
    print(received)


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
    await client.start_notify(target_characteristic, notify_callback)
          
    # client 가 연결된 상태라면
    if client.is_connected:
        # 1초간 대기
        await asyncio.sleep(120) 
        print('try to deactivate notify.')
        # 활성시켰단 notify를 중지 시킨다.
        await client.stop_notify(target_characteristic)


    await client.disconnect()


loop = asyncio.get_event_loop()
loop.run_until_complete(run())
print('done')