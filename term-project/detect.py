
import serial
import pandas as pd
import joblib
import math
import collections



df = pd.DataFrame({
    "r1": [],
    "r2": [],
    "p1": [],
    "p2": [],
})

# 'COM3' 부분에 환경에 맞는 포트 입력
ser = serial.Serial('/dev/cu.usbmodem14101', 9600)

roll1 = None
pitch1 = None
roll2 = None
pitch2 = None

model = joblib.load("sample.pkl")



while True:
    if ser.readable():
        val = ser.readline()
        val = val.decode()[:len(val)-1]
        
        tmp = val.split("/")

        roll1 = int(float(tmp[0]))
        pitch1 = int(float(tmp[1]))
        roll2 = int(float(tmp[2]))
        pitch2 = int(float(tmp[3]))
        
        if roll1 != None and roll2 != None and pitch1 != None and pitch2 != None:
            # print("111: " + str(roll1) + " | " + str(pitch1))
            # print("222: " + str(roll2) + " | " + str(pitch2))

            dft = []

            df = df.append({
                "r1": roll1,
                "r2": roll2,
                "p1": pitch1,
                "p2": pitch2,
            }, ignore_index=True)

            if len(df) == 15:
                dft = df.iloc[0:15, :]
            elif len(df) == 25:
                dft = df.iloc[10:25, :]
                dft.reset_index()
                df = dft
            
            roll1 = None
            pitch1 = None
            roll2 = None
            pitch2 = None

            if len(dft) != 0:
                val =  (model.predict(dft)).sum() / 15 
                print(val)
                if 0.9 < val and val < 1.1:
                    print(1)
                elif 1.9 < val and val < 2.1:
                    print(2)
                else:
                    print(0)


                # res = collections.Counter(model.predict(dft))
                # print(max(res))





# 1: 손가락 튕기기 
# 2: 주먹 쥐었다 펴기
# 4: 손바닥 하늘로 향한 뒤 엎어다 펴기