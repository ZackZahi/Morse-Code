import time
import RPi.GPIO as GPIO
from Encoder import*

class Sender:
    def __init__(self):
        self.m_encoder=Encoder()
        GPIO.setmode(GPIO.BCM)
        GPIO.setup(18, GPIO.OUT)
        pass

    def Send(self,StringToSend):
        #print(StringToSend)
        Binary_tab = self.m_encoder.Encode(StringToSend)
        self.TransmittSignal(Binary_tab)
        return Binary_tab

    def TransmittSignal(self,binary_tab):
        voltage_level=0
        for el in binary_tab:
            if el[0] == "High":
                voltage_level =GPIO.HIGH
            else :
                voltage_level=GPIO.LOW
            GPIO.output(18,voltage_level)
            time.sleep(el[1]*0.001)
        GPIO.cleanup()
