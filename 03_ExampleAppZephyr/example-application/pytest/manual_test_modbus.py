import minimalmodbus
import serial


segment = minimalmodbus.Instrument('/dev/ttyUSB0', 1)  # port name, slave address (in decimal)
segment.serial.port  # this is the serial port name
segment.serial.baudrate = 115200  # Baud
segment.serial.bytesize = 8
segment.serial.parity = serial.PARITY_NONE
segment.serial.stopbits = 1
segment.serial.timeout = 0.05  # seconds

segment.address  # this is the slave address number
segment.mode = minimalmodbus.MODE_RTU  # rtu or ascii mode
segment.clear_buffers_before_each_transaction = True

segment.write_bit(1, 1, 5)