/*
 * EQUIPO 6
 * DIEGO RUIZ
 * OCTAVIO FAJARDO
 * ALEJANDRO ZAMBRANO
 * */

#include "main.h"
typedef unsigned char     T_UBYTE;
typedef unsigned short    T_UWORD;
#define CHECKSUM_MASK 1
#define STOP_BIT_MASK 2
#define LIGHT_SENSOR_MASK 12
#define SELECTOR_MASK 48
#define IGNITION_STATUS_MASK 192

/*
#define bit_1_off 254
#define bit_2_off 253
#define bit_3_off 251
#define bit_4_off 247
#define bit_5_off 239
#define bit_6_off 223
#define bit_7_off 191
#define bit_8_off 127
*/
T_UBYTE rub_char;
T_UBYTE rub_entradaByte = 0;
T_UBYTE rub_checksum_calculado,rub_checksum_recibido,rub_current_lights=0;
T_UWORD i;

void print_input_byte();
int checksum_is_right();
void execute_commands_in_input_byte();
void Lights_Off();
void Half_Light();
void Lights_On();

int main(void){
	
	
	while(TRUE)
	{
		rub_entradaByte = 0;
		
		put("\r\nLight Sensor\r\n");
		rub_char = in_char();
		out_char(rub_char);
		switch (rub_char){
			case '0':
				//rub_entradaByte |= LIGHT_SENSOR_MASK & 0;
				break;
			case '1':
				rub_entradaByte |= LIGHT_SENSOR_MASK & 4;
				break;
			case '2':
				rub_entradaByte |= LIGHT_SENSOR_MASK & 8;
				break;
			case '3':
				rub_entradaByte |= LIGHT_SENSOR_MASK & 12;
				break;
			//default:
				//rub_entradaByte |= LIGHT_SENSOR_MASK & 0;
		}
		
		put("\r\nSelector\r\n");
		rub_char = in_char();
		out_char(rub_char);
		switch (rub_char){
			case '0':
				//rub_entradaByte |= SELECTOR_MASK & 0;
				break;
			case '1':
				rub_entradaByte |= SELECTOR_MASK & 16;
				break;
			case '2':
				rub_entradaByte |= SELECTOR_MASK & 32;
				break;
			case '3':
				rub_entradaByte |= SELECTOR_MASK & 48;
				break;
			//default:
				//rub_entradaByte |= SELECTOR_MASK & 0;
		}

		put("\r\nIgnition Status\r\n");
		rub_char = in_char();
		out_char(rub_char);
		switch (rub_char){
			case '0':
				//rub_entradaByte |= IGNITION_STATUS_MASK & 0;
				break;
			case '1':
				rub_entradaByte |= IGNITION_STATUS_MASK & 64;
				break;
			case '2':
				rub_entradaByte |= IGNITION_STATUS_MASK & 128;
				break;
			case '3':
				rub_entradaByte |= IGNITION_STATUS_MASK & 192;
				break;
			default:
				rub_entradaByte |= IGNITION_STATUS_MASK & 64;
		}
		
		put("\r\nStop Bit\r\n");
		rub_char = in_char();
		out_char(rub_char);
		switch (rub_char){
			case '0':
				//rub_entradaByte &= bit_2_off;
				break;
			case '1':
				rub_entradaByte |= STOP_BIT_MASK;
				break;
			//default:
				//rub_entradaByte &= bit_2_off;
		}
		
		put("\r\nChecksum\r\n");
		rub_char = in_char();
		out_char(rub_char);
		switch (rub_char){
			case '0':
				rub_checksum_recibido=0;
				//rub_entradaByte &= bit_1_off;
				break;
			case '1':
				rub_checksum_recibido=1;
				rub_entradaByte |= CHECKSUM_MASK;
				break;
			//default:
				//rub_entradaByte &= bit_1_off;
		}
		
		execute_commands_in_input_byte();
		print_input_byte();
	}
	
	return 0;
}

void print_input_byte(){
	put("\n");
	if(checksum_is_right())
		put("00");
	else 
		put("01");
	switch(SELECTOR_MASK & rub_entradaByte){
		case 0:
			put("00");
			break;
		case 16:
			put("01");
			break;
		case 32:
			put("10");
			break;
		case 48:
			put("11");
	};
	switch(IGNITION_STATUS_MASK & rub_entradaByte){
		case 0:
			put("00");
			break;
		case 64:
			put("01");
			break;
		case 128:
			put("10");
			break;
		case 192:
			put("11");
	};
	switch(LIGHT_SENSOR_MASK & rub_entradaByte){
		case 0:
			put("00");
			break;
		case 4:
			put("01");
			break;
		case 8:
			put("10");
			break;
		case 12:
			put("11");
	};
	
}

int checksum_is_right(){
	rub_checksum_calculado=0;
	for(i=2;i<0xFF;i=i*2){
	    // print last bit and shift left.
		if( rub_entradaByte & i){
			rub_checksum_calculado++;
		}else{
		}
	}
	
	return (rub_checksum_calculado%2)!=rub_checksum_recibido ;
}


void execute_commands_in_input_byte(){
	if(checksum_is_right()){
		switch(  SELECTOR_MASK & rub_entradaByte){
			case 0:
				Lights_Off();
				break;
			case 16:
				switch(LIGHT_SENSOR_MASK & rub_entradaByte){
					case 0:
						Lights_Off();
						break;
					case 4:
						if(rub_current_lights==1) Lights_On();
						break;
					case 8:
						if(rub_current_lights==2) Half_Light();
						break;
					case 12:
						if(rub_current_lights==1) Lights_Off();
						break;
					default:
						Lights_Off();
				}
				break;
			case 32:
				Half_Light();
				break;
			case 48:
				Lights_On();
				break;
			
		}
	}
	
}

void Lights_Off(){
	RED_OFF;
	GREEN_OFF;
	BLUE_OFF;
	rub_current_lights=0;
}

void Half_Light(){
	RED_ON; GREEN_OFF; BLUE_OFF;
	rub_current_lights=1;
}

void Lights_On(){
	if( (IGNITION_STATUS_MASK & rub_entradaByte)==192 || (IGNITION_STATUS_MASK & rub_entradaByte)==128){
		RED_ON; GREEN_OFF; BLUE_ON;	
	}
	else{
		RED_ON; GREEN_OFF; BLUE_OFF;
	}
	rub_current_lights=2;
}
