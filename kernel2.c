#include "kernel.h"

uint32 vga_index;
static uint32 next_line_index = 1;
uint8 g_fore_color = WHITE, g_back_color = BLUE;
int digit_ascii_codes[10] = {0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39};

uint16 vga_entry(unsigned char ch,uint8 fore_color,uint8 back_color){
  uint16 ax = 0;
  uint8 ah=0,al=0;
  ah= back_color;
  ah<<=4;
  ah |= fore_color;
  ax = ah;
  ax <<= 8;
  al = ch;
  ax |= al;
  return ax;
}
void clear_vga_buffer(uint16 **buffer, uint8 fore_color, uint8 back_color){
  uint32 i;
  for(i=0;i<BUFSIZE;i++){
    (*buffer)[i] = vga_entry(NULL,fore_color,back_color);
  }
}
void init_vga(uint8 fore_color, uint8 back_color){
  vga_buffer = (uint16*)VGA_ADDRESS;
  clear_vga_buffer(&vga_buffer,fore_color,back_color);
  g_fore_color = fore_color;
  g_back_color = back_color;
}
void print_new_line(){
  if(next_line_index >=55){
    next_line_index = 0;
    clear_vga_buffer(&vga_buffer,g_fore_color,g_back_color);
  }
  vga_index = 80*next_line_index;
  next_line_index++;
}
void print_char(char ch){
  vga_buffer[vga_index] = vga_entry(ch,g_fore_color,g_back_color);
  vga_index++;
}
uint32 strlen(const char* str){
  uint32 length=0;
  while(str[length]){
    length++;
  }
  return length;
}
uint32 digit_count(int num){
  uint32 count = 0;
  if(num==0){
    return 1;
  }
  while(num>0){
    count++;
    num=num/10;
  }
  return count;
}
void itoa(int num, char *number){
  int dgcount = digit_count(num);
  int index = dgcount -1;
  char x;
  if(num==0 && dgcount == 1){
    number[0] = '0';
    number[1] = '\0';
  }
  else{
    while(num!=0){
      x = num%10;
      number[index] = x + '0';
      index--;
      num = num / 10;
    }
    number[dgcount] = '\0';
  }
}

uint8 addTwo(uint8 a,uint8 b){
	uint8 c;
	c=a+b;
	return c;
}

void print_string(char *str){
  uint32 index = 0;
  while(str[index]){
    print_char(str[index]);
    index++;
  }
}
void print_int(int num){
  char str_num[digit_count(num)+1];
  itoa(num,str_num);
  print_string(str_num);
}

void kernel_entry(){
  init_vga(WHITE,BLACK);
  print_string("HELLO WORLD !!");
  print_new_line();
  print_int(12344321);
  print_new_line();
  print_string("Goodbye !");
  print_string("Addition of 3 & 5 : ");
  print_int(addTwo(3,5));
}
