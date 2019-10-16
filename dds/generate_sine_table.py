#Generate a 24-bit sine table in Intel Hex format
#Paul Musgrave
#2019-09-28
import math,struct

# thanks to https://stackoverflow.com/questions/23624212/how-to-convert-a-float-into-hex
# for this function
def float_to_bin(f):
    return bin(struct.unpack('<I', struct.pack('<f', f))[0])

def calculate_checksum(val):
    checksum = 0
    for x in list(val):
        checksum += int(x)
    checksum = ((checksum))
    return bin(checksum ^ 0xff)

sine_table = open('sine_table.hex', 'w')
#new_sine_table = open('new_sine_table.hex','w')

num_samples = 4096
FS = 48000
amplitude = 126

i = 0
for i in range(0,num_samples):
    #hex_value = list(str(line))[9:-3]
    delta = 2*math.pi/num_samples
    x = delta * i;
    sine_float = amplitude * math.sin(x);
    sine_hex = float_to_bin(sine_float)
    #new_hex_line = "".join(list(str(line))[1:8] + list(str(sine_hex))[2:]).upper()
    #new_hex_line = ":" + new_hex_line + calculate_checksum(new_hex_line) + "\n"
    new_hex_line = ":" + hex(int("".join(list(sine_hex)[2:]))) #+ list(hex(calculate_checksum("".join(list(sine_hex)[2:])))[2:])
    print(new_hex_line)
    #new_sine_table.write(new_hex_line)
    i += 1

new_sine_table.close()
sine_table.close()
