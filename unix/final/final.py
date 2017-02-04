#!/usr/bin/env python2.7

import os
import socket
import sys

import socket
import subprocess
import sys
from datetime import datetime

# Constants

ADDRESS = ''
PORT    = 9775
PROGRAM = os.path.basename(sys.argv[0])

# Clear the screen
subprocess.call('clear', shell=True)

# Ask for server to scan
remoteServer    = raw_input("Enter a remote host to scan: ")
ADDRESS = remoteServer
remoteServerIP  = socket.gethostbyname(remoteServer)

# Shows that it is scanning host
print "-" * 60
print "Please wait, scanning remote host", remoteServerIP
print "-" * 60

# Check what time the scan started
t1 = datetime.now()

# Scan ports 9700-9799
try:
    for port in range(9700, 9799):  
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        result = sock.connect_ex((remoteServerIP, port))
        if result == 0:
            print "Port {}: 	 Open".format(port)
            PORT = port
        sock.close()

except KeyboardInterrupt:
    print "You pressed Ctrl+C"
    sys.exit()

except socket.gaierror:
    print 'Hostname could not be resolved. Exiting'
    sys.exit()

except socket.error:
    print "Couldn't connect to server"
    sys.exit()

# Checking the time again
t2 = datetime.now()

# Calculates the difference of time, to see how long it took to run the script
total =  t2 - t1

# Printing the information to screen
print 'Scanning Completed in: ', total

# Echo Client

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # Allocate TCP socket
client.connect((ADDRESS, PORT))                             # Connect to server with ADDRESS and PORT

stream = client.makefile('w+')                              # Create file object from socket
data   = sys.stdin.readline()                               # Read from STDIN

while data:
    # Send STDIN to Server
    stream.write(data)
    stream.flush()

    # Read from Server to STDOUT
    data = stream.readline()
    sys.stdout.write(data)

    # Read from STDIN
    data = sys.stdin.readline()