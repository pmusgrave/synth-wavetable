import re
sine_table_file = open("sine_table.hex","r")
fixed_sine_table_file = open("sine_table2.hex", "w")
for line in sine_table_file:
    for char in line.split():
        output_line = "".join(list(line)[1:])
        fixed_sine_table_file.write(output_line)
