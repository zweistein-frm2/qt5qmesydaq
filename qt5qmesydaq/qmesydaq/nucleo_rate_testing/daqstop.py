import sys
import time
import socket

from mesylib import send_cmd


#try:
#    addr = sys.argv[1]
#    rate = int(sys.argv[2])
#except (ValueError, IndexError):
#    print('usage: mesyparams.py ipaddr rate')
#    sys.exit(1)

addr = "192.168.168.121"

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
send_cmd(sock, addr, 0x2, 'IH', 0, 0)

print('configure ok')
