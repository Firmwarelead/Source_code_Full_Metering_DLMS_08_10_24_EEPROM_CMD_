Version xxx (06-10-2024)
Contributor: Mrityunjay

File Updated: r_dlms_format.h
Change Description: Modified the EEPROM address definition on line 107, changing STORAGE_EEPROM_METER_FORMAT_LAST_ADDR to STORAGE_EEPROM_LOAD_CTRL_LAST_ADDR.
Impact: Updated address handling for the DLMS EEPROM load control section to improve memory management.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Version xxx (08-10-2024)
Contributor: Vikram
File Updated: key.h              :- port number is updated according to our hardware.
              key.c              :- key pooling process is enabled.
	      r_cg_lcd.c         :- void R_LCD_Create(void) function fully changed.
	      r_lcd_config.h     :- changed according to our LCD.
              r_lcd_config.c     :- changed according to our LCD.
              r_drv_lcd_ext.c    :-Function Name : LCD_WriteRAMDigitInfo and LCD_ClearRAMDigitInfo changed according to our 8 com LCD.
              r_cg_port.c        :- Port configuration changed w.r.t. lcd mapping. and p77 is included for magnet.
              r_cg_systeminit.c  :- PIORO register value changed from 0x20 to 0x00.
              em_display.c       :- Functions are canged according to our 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Version: xxx (10-10-2024)
Contributor: Mrityunjay

		Files Updated:
		 	relay.c & relay.h
				Modified RELAY_SwitchOff and RELAY_SwitchOn functions.
			eeprom.c & eeprom.h
				Added Erase and EraseAll functions.
			r_cg_tau_user.c
				Integrated UART2_Ideal_Timer in the r_tau0_channel2_interrupt function.
			r_cg_sau_user.c
				Added g_uart2_rx_buff, rx = 0, and UART2_Ideal_Timer variable.
			r_meter_cmd.c
				Introduced EEPROM_commands_PollingProcessing function to handle erase, read, and write operations via the HDLC port.
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
		 
		

