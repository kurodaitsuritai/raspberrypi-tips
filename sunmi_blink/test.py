import serial
import threading
import time
import subprocess

def exec_subprocess(cmd: str, raise_error=True):
    child = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = child.communicate()
    rt = child.returncode
    if rt != 0 and raise_error:
        raise Exception(f"command return code is not 0. got {rt}. stderr = {stderr}")
    return stdout, stderr, rt

def thread_qr_func():
    while True:
        try:
            print("thread_qr_func started !")

            # 探索
            tty = ""
            for i in range(0, 10, 1):
                tty = "/dev/ttyACM" + str(i)
                res,a,b = exec_subprocess("udevadm info " + tty + " | grep -i 'ID_USB_VENDOR_ID' | cut -d'=' -f2")
                vendoer_id = res.decode().strip().upper()
                res,a,b = exec_subprocess("udevadm info " + tty + " | grep -i 'ID_USB_MODEL_ID' | cut -d'=' -f2")
                product_id = res.decode().strip().upper()
                # print(vendoer_id, product_id)
                if vendoer_id == "324F" and product_id == "0032":
                    print("found !")
                    break

            Serial_Port = serial.Serial(port=tty, baudrate=9600, parity='N')
                    
            print("thread_qr_func open !")
            data = Serial_Port.readline()
            data = data.strip().decode('utf-8')
            Serial_Port.close()
            print("thread_qr_func read !")
            print(data)
        except Exception as e:
            print(f"予期しないエラーが発生しました: {e}")
        
thread_qr = threading.Thread(target=thread_qr_func)
thread_qr.start()