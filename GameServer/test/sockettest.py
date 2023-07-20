# A Python Script for Running a Suite of Tests Against the Illumination Game Server

# Configuration Options
HOST = "127.0.0.1"
PORT = 8887

import socket
import time

totaltests = 0
passedtests = 0


# Testing Function
# Assumes Function Tested Returns a Tuple (bool, string)
# that provides a success/fail state and an error message if unsuccessful
def performTest(testfunc):
    global totaltests, passedtests
    try:
        res: tuple[bool, str] = testfunc()
    except Exception as e:
        res: tuple[bool, str] = (False, f"Error: {e}")

    totaltests += 1
    if res[0]:
        print(f"{testfunc.__name__} Passed!")
        passedtests += 1
        return
    print(f"{testfunc.__name__} Failed\nMessage: {res[1]}")


# Tests Socket Persistence and Tests Functionality (Server Should Print a Message Saying User id 14)
@performTest
def sendReadFlagPacket() -> tuple[bool, str]:
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST, PORT))
        for i in range(5):
            s.send(bytes([i, 0, 0, 0, 0, 0, 0, 0, 0, 0]))
            data = int.from_bytes(s.recv(4096), "little")
            if data != i:
                return False, "Server failed to read flag packet."
            time.sleep(.1)
        return True, "Server properly received flag read requests with UID"
