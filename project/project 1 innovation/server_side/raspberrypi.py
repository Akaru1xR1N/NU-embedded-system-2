import mysql.connector
import hashlib
import serial
import socket
from time import sleep
import threading

header = ""
content = ""
separatorChar = "&"

class DB:
    def __init__(self):
        self.mydb = mysql.connector.connect(host="localhost", username="root", password="Password#123", database="db_esproject_door")
        self.mycursor = self.mydb.cursor()

    def get_names(self):
        self.mycursor.execute("SELECT name FROM tb_user;")
        result = self.mycursor.fetchall()
        return result

    def login(self, username, password) -> str:
        password = hashlib.sha512(password.encode()).hexdigest()
        self.mycursor.execute(f"SELECT name FROM tb_user WHERE name='{username}' AND password='{password}';")
        result = self.mycursor.fetchall()
        try:
            result[0]
            return True
        except Exception:
            return False

class Serial:
    def __init__(self):
        self.master_serial_port = 8
        self.slave_serial_port = 6

    def connect(self):
        self.ser = serial.Serial("COM"+str(self.master_serial_port), 9600)

    def read(self):
        global header
        global content
        global separatorChar
        recv = self.ser.readline()
        try:
            recv = recv.decode()
        except Exception:
            pass
        print(recv)
        try:
            if recv.find(separatorChar.encode()) != -1:
                header, content = recv.split(separatorChar)[0], recv.split(separatorChar)[1:]
                content[-1] = content[-1].split("\r\n")[0]
                print(header)
                print(content)
        except Exception:
            if recv.find(separatorChar) != -1:
                header, content = recv.split(separatorChar)[0], recv.split(separatorChar)[1:]
                content[-1] = content[-1].split("\r\n")[0]
                print(header)
                print(content)

    def write(self, data):
        self.ser.write(data.encode())

    def close(self):
        self.ser.close()

class Bluetooth:
    def __init__(self):
        self.baddr = "B4:23:24:02:6B:B6"
        self.channel = 1
        self.sock = socket.socket(socket.AF_BLUETOOTH, socket.SOCK_STREAM, socket.BTPROTO_RFCOMM)
        self.status = False

    def connect(self):
        while True:
            try:
                self.sock.connect((self.baddr, self.channel))
                self.status = True
                break
            except Exception as e:
                print(e)
                sleep(1)

    def receiving_data(self):
        global header
        global content
        global separatorChar
        recv = self.sock.recv(1024)
        try:
            recv = recv.decode()
        except Exception:
            pass

        # not sure about the code under
        try:
            if recv.find(separatorChar.encode()) != -1:
                header, content = recv.split(separatorChar)[0], recv.split(separatorChar)[1:]
                content[-1] = content[-1].split("\r\n")[0]
                print(header)
                print(content)
        except Exception:
            if recv.find(separatorChar) != -1:
                header, content = recv.split(separatorChar)[0], recv.split(separatorChar)[1:]
                content[-1] = content[-1].split("\r\n")[0]
                print(header)
                print(content)

    def write(self, data):
        try:
            self.sock.send(data.encode())
        except Exception:
            self.sock.send(data)

class MyThread(threading.Thread):
    def __init__(self, function):
        super().__init__()
        self.function = function
        self.ser = Serial()

    def run(self):
        while True:
            self.function()

def main():
    global header
    global content
    global separatorChar
    global db
    if str(header) == "serialPing":
        ser.write(f"serialPong{separatorChar}{content}")
        header = ""
        content = ""
    if str(header) == "btPing":
        bt.write(f"btPong{separatorChar}{content}".encode())
        header = ""
        content = ""
    if str(header) == "checkUsernamePasswordSer":
        try:
            result = db.login(content[0], content[1])
        except Exception:
            return
        print(content[0])
        print(content[1])
        ser.write(f"checkUsernamePasswordResultSer{separatorChar}{result}")
        header = ""
        content = ""
    if str(header) == "checkUsernamePasswordBT":
        try:
            result = db.login(content[0], content[1])
        except Exception:
            return
        print(content[0])
        print(content[1])
        bt.write(f"checkUsernamePasswordResultBT{separatorChar}{result}")
        header = ""
        content = ""
    if str(header) == "getUsernameSer":
        result = db.get_names()
        result = [name[0] for name in result]
        result = "$".join(result)
        ser.write(f"getUsernameResultSer{separatorChar}{result}")
        header = ""
        content = ""
    if str(header) == "getUsernameBT":
        result = db.get_names()
        result = [name[0] for name in result]
        result = "$".join(result)
        bt.write(f"getUsernameResultBT{separatorChar}{result}")
        header = ""
        content = ""

if __name__ == "__main__":
    db = DB()
    ser = Serial()
    ser.connect()
    bt = Bluetooth()
    bt.connect()
    while not bt.status:
        pass

    ser_thread = MyThread(ser.read)
    ser_thread.start()
    main_thread = MyThread(main)
    main_thread.start()
    bt_thread = MyThread(bt.receiving_data)
    bt_thread.start()
