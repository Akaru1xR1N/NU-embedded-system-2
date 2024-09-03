import socket

baddr = "B4:23:24:02:6B:B6"
channel = 1

sock = socket.socket(socket.AF_BLUETOOTH, socket.SOCK_STREAM, socket.BTPROTO_RFCOMM)
while True:
    try:
        sock.connect((baddr, channel))
        break
    except Exception:
        pass
while True:
    inp = input()
    if inp == "QUIT":
        break
    sock.send(inp.encode())
    recv = sock.recv(1024).decode()
    print(recv, end="")
sock.close()
