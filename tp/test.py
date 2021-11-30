
import serial
import pandas as pd

df = pd.DataFrame({
    "r1": [],
    "r2": [],
    "p1": [],
    "p2": [],
    "gesture":[], 
})

# 'COM3' 부분에 환경에 맞는 포트 입력
ser = serial.Serial('/dev/cu.usbmodem1422201', 9600)

roll1 = None
pitch1 = None
roll2 = None
pitch2 = None


idx = 0

while True:
    if ser.readable():
        val = ser.readline()
        val = val.decode()[:len(val)-1]
        
        tmp = val.split("/")

        if int(tmp[0]) == 11:
            roll1 = int(float(tmp[1]))
        elif int(tmp[0]) == 12:
            pitch1 = int(float(tmp[1]))
        elif int(tmp[0]) == 21:
            roll2 = int(float(tmp[1]))
        elif int(tmp[0]) == 22:
            pitch2 = int(float(tmp[1]))
        
        if roll1 != None and roll2 != None and pitch1 != None and pitch2 != None:
            print(str(idx) + "===================")
            print("111: " + str(roll1) + " | " + str(pitch1))
            print("222: " + str(roll2) + " | " + str(pitch2))

            df = df.append({
                "r1": roll1,
                "r2": roll2,
                "p1": pitch1,
                "p2": pitch2,
                "gesture": 0, 
            }, ignore_index=True)
            df.to_csv("sample.csv")
            
            roll1 = None
            pitch1 = None
            roll2 = None
            pitch2 = None

            idx = idx + 1




# 1: 손가락 튕기기 
# 2: 주먹 쥐었다 펴기
# 4: 손바닥 하늘로 향한 뒤 엎어다 펴기