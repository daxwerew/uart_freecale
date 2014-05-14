#include "main.h"
#define bit_1_on 1
#define bit_2_on 2
#define bit_3_on 4
#define bit_4_on 8
#define bit_5_on 16
#define bit_6_on 32
#define bit_7_on 64
#define bit_8_on 128
#define bit_1_off 254
#define bit_2_off 253
#define bit_3_off 251
#define bit_4_off 247
#define bit_5_off 239
#define bit_6_off 223
#define bit_7_off 191
#define bit_8_off 127
int i,checkreal,checkrecibido;

int main(void){
	
	char ch,entradaByte=0;
	
	
	while(TRUE)
	{
		put("\r\nElige Light Sensor\r\n");
		ch = in_char();
		out_char(ch);
		switch (ch){
			case '0':
				entradaByte &= bit_3_off;
				entradaByte &= bit_4_off;
				break;
			case '1':
				entradaByte &= bit_3_off;
				entradaByte |= bit_4_on;
				break;
			case '2':
				entradaByte |= bit_3_on;
				entradaByte &= bit_4_off;
				break;
			case '3':
				entradaByte |= bit_3_on;
				entradaByte |= bit_4_on;
				break;
			default:
				entradaByte &= bit_3_off;
				entradaByte |= bit_4_on;
		}
		
		put("\r\nElige Selector\r\n");
		ch = in_char();
		out_char(ch);
		switch (ch){
			case '0':
				entradaByte &= bit_5_off;
				entradaByte &= bit_6_off;
				break;
			case '1':
				entradaByte &= bit_5_off;
				entradaByte |= bit_6_on;
				break;
			case '2':
				entradaByte |= bit_5_on;
				entradaByte &= bit_6_off;
				break;
			case '3':
				entradaByte |= bit_5_on;
				entradaByte |= bit_6_on;
				break;
			default:
				entradaByte &= bit_5_off;
				entradaByte &= bit_6_off;
		}

		put("\r\nElige Ignition Status\r\n");
		ch = in_char();
		out_char(ch);
		switch (ch){
			case '0':
				entradaByte &= bit_7_off;
				entradaByte &= bit_8_off;
				break;
			case '1':
				entradaByte &= bit_7_off;
				entradaByte |= bit_8_on;
				break;
			case '2':
				entradaByte |= bit_7_on;
				entradaByte &= bit_8_off;
				break;
			case '3':
				entradaByte |= bit_7_on;
				entradaByte |= bit_8_on;
				break;
			default:
				entradaByte &= bit_7_off;
				entradaByte |= bit_8_on;
		}
		
		put("\r\nStop Bit\r\n");
		ch = in_char();
		out_char(ch);
		switch (ch){
			case '0':
				entradaByte &= bit_2_off;
				break;
			case '1':
				entradaByte |= bit_2_on;
				break;
			default:
				entradaByte &= bit_2_off;
		}
		
		put("\r\Checksum\r\n");
		ch = in_char();
		out_char(ch);
		switch (ch){
			case '0':
				checkrecibido=0;
				entradaByte &= bit_1_off;
				break;
			case '1':
				checkrecibido=1;
				entradaByte |= bit_1_on;
				break;
			default:
				entradaByte &= bit_1_off;
		}
		
		//*/
		checkreal=0;
		for(i=1;i<200;i=i*2){
		    // print last bit and shift left.
			if( entradaByte & i ){
				checkreal++;
			    put("1");
			}else{
			    put("0");	
			}
		}
		
		if( (checkreal%2)!=checkrecibido ){
			put("CheckSum es correcto");
		}
		else
		{
			put("CheckSum es incorrecto");
		}
		//*/
		
	}
	
	return 0;
}
