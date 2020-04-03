import sys
import time
import socket

from mesylib import send_cmd


try:
 #   addr = sys.argv[1]
    rate = int(sys.argv[1])
except (ValueError, IndexError):
    print('usage: mesyparams.py  rate')
    sys.exit(1)

addr = "192.168.168.121"

#rate = 2000

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
send_cmd(sock, addr, 0xF1F0, 'IH', rate, 0)

print('configure ok')
