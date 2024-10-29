import pytest
import re
import serial
from time import time,sleep
import os
import minimalmodbus

@pytest.fixture(scope='session')
def anyio_backend():
    return 'trio'

def pytest_addoption(parser):
    parser.addoption("--port",
            help="The port to which the device is attached (eg: /dev/ttyACM0)")
    parser.addoption("--baud", type=int, default=115200,
            help="Serial port baud rate (default: 115200)")
    parser.addoption("--fw-image", type=str,
            help="Firmware binary to program to device")
    parser.addoption("--serial-number", type=str,
            help="Serial number to identify on-board debugger")
    parser.addoption("--modbus-serial-number", type=str, default='',
            help="Serial number to Modbus connection")

@pytest.fixture(scope="session")
def port(request):
    return request.config.getoption("--port")

@pytest.fixture(scope="session")
def baud(request):
    return request.config.getoption("--baud")

@pytest.fixture(scope="session")
def fw_image(request):
    return request.config.getoption("--fw-image")

@pytest.fixture(scope="session")
def serial_number(request):
    return request.config.getoption("--serial-number")

@pytest.fixture(scope="session")
def modbus_serial_number(request):
    return request.config.getoption("--modbus-serial-number")

class Board():
    lckr_modbus = {}

    def __init__(self, port, baud, fw_image, serial_number, modbus_serial_number):
        self.port = port
        self.baud = baud
        self.fw_image = fw_image
        self.serial_number = serial_number

        #program firmware
        self.program(fw_image)

        self.serial_device = serial.Serial(port, self.baud, timeout=1, write_timeout=1)

        if modbus_serial_number != '':
            self.lckr_modbus = self.setup_modbus_conn(1)
            print("Modbus inited")

    def program(self, fw_image):
        print("programming")
        # os.system('west flash')
        os.system(f'pyocd flash -t stm32l432kc -f 400000 -O connect_mode=under-reset {self.fw_image}')

    def wait_for_regex_in_line(self, regex, timeout_s=20, log=True):

        if self.lckr_modbus != {}:
            sleep(3)
            self.lckr_modbus.write_bit(7, 1, 5)
            print("controlled")

        start_time = time()

        while True:
            self.serial_device.timeout=timeout_s
            line = self.serial_device.read_until().decode('utf-8', errors='replace').replace("\r\n", "")
            if line != "" and log:
                print(line)
            if time() - start_time > timeout_s:
                raise RuntimeError('Timeout')
            regex_search = re.search(regex, line)
            if regex_search:
                return regex_search
    
    def setup_modbus_conn(self, segment_id):
        segment = minimalmodbus.Instrument('/dev/ttyUSB0', segment_id)  # port name, slave address (in decimal)
        segment.serial.port  # this is the serial port name
        segment.serial.baudrate = 115200  # Baud
        segment.serial.bytesize = 8
        segment.serial.parity = serial.PARITY_NONE
        segment.serial.stopbits = 1
        segment.serial.timeout = 0.05  # seconds

        segment.address  # this is the slave address number
        segment.mode = minimalmodbus.MODE_RTU  # rtu or ascii mode
        segment.clear_buffers_before_each_transaction = True

        return segment
        

@pytest.fixture(scope="session")
def board(port, baud, fw_image, serial_number, modbus_serial_number):
    return Board(port, baud, fw_image, serial_number, modbus_serial_number)
