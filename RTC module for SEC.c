#include <At89s52.h>
#define scl P0_3
#define sda P1_5


void i2c_init(void){
scl=0;
sda=0;
}


void i2c_start(void){
sda=1;
scl=1;
sda=0;
scl=0;
}


void i2c_stop(void){
scl=1;
sda=1;
scl=0;
sda=0;
}

void i2c_ack(void){
sda=0;
scl=1;
scl=0;
}

void i2c_nack(void){
sda=1;
scl=1;
scl=0;
}
void i2c_write(char b){
char i;
__bit p=1;
while(p==1)
{
for(i=0;i<8;i++){
if(((b)&(0x80>>i))!=0){
  sda=1;
  }else{
  sda=0;
  }
  scl=1;
  scl=0;
 }
  sda=1;
 scl=1;
 p=sda;
 scl=0;
 sda=0;
 }

}
char i2c_read(void)
{
char s=0x00;
char j;
sda=1;
for(j=0;j<8;j++)
{
scl=1;
if(sda==1)
{
s=s|(0x80>>j);
}
else{
}
scl=0;
}
sda=0;
return s;
}
void main(){
i2c_init();
i2c_start();
i2c_write(0xD0);
i2c_write(0x00);
i2c_write(0x00);
i2c_stop();
while(1)
{
i2c_start();
i2c_write(0xD0);
i2c_write(0x00);
i2c_start();
i2c_write(0xD1);
P2=~i2c_read();
i2c_nack();
i2c_stop();
}
}
