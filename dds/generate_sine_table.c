#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>

#define N 4096

uint32_t generate_sine_hex_str(int);
uint32_t checksum(char*);

int main(){
  FILE* sine_table_file = fopen("sine_table.hex","w+");

  for (int i = 0; i < N; i++) {
    //fputs(sine_table_file, generate_sine_hex_str(i));
    char record[100] = {0};
    //sprintf(record, "%.2x%.4x00%.8x",8,i,generate_sine_hex_str(i));
    //fprintf(sine_table_file,":%s%x\n", record,checksum(record));
    fprintf(sine_table_file, "\t%d\t:\t%06x;\n",i,(generate_sine_hex_str(i)>>8)&0xFFFFFF);
  }

  //fprintf(sine_table_file, ":00000001FF\n");
  fclose(sine_table_file);
  return 0;
}

 uint32_t generate_sine_hex_str(int i){
  uint32_t amplitude = UINT32_MAX;
   double delta = 2*M_PI/N;
  double x = delta * i;
  uint32_t sine_val = amplitude/2 * sin(x) + (amplitude/2);
  union {
    float f;
    uint32_t u;
  } f2u = { .f = sine_val };

  //return f2u.u;
  return sine_val;
}

uint32_t checksum(char* record) {
  int32_t sum = 0;
  for(int i = 0; i < 100; i++) {
    char ch = record[i];
    if (ch >= '0' && ch <= '9')
      sum += ch - '0';
    if (ch >= 'A' && ch <= 'F')
      sum += ch - 'A' + 10;
    if (ch >= 'a' && ch <= 'f')
      sum += ch - 'a' + 10;
  }
  return ((sum&0xFF) ^ 0xFF + 1) & 0xFF;
}
