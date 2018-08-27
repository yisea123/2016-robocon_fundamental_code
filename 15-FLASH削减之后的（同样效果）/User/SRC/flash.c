#include "main.h"           

/******  flashÈý¸ö¼ì²â×Ö·û**********/
u8 check1 = 0x00;    //W    		      
u8 check2 = 0x00;    //H   		
u8 check3 = 0x00;    //U
u8 check1_temp = 0x57;    //W    		      
u8 check2_temp = 0x48;    //H   		
u8 check3_temp = 0x55;    //U

u8 flash_first_flag = 0x00;

#define check_PAGE_ADDRESS             						0x0801FC00           
#define all_PAGE_ADDRESS             							0x0801F800

#define check1_ADDRESS             								0x0801FC02
#define location_p_ADDRESS              					0x0801F802




void Flash_Write_Word(uint32_t Address,uint32_t Data)
{
	FLASH_Unlock();
	FLASH_ProgramWord(Address, (uint32_t)Data);
	FLASH_Lock();
}

void Flash_Write_HalfWord(uint32_t Address,uint16_t Data)
{
	FLASH_Unlock();
	FLASH_ProgramHalfWord(Address, (uint16_t)Data);
	FLASH_Lock();
}

void Flash_Erase_Page(uint32_t Page_Address)
{
	FLASH_Unlock();
	FLASH_ErasePage(Page_Address);
	FLASH_Lock();
}

uint16_t Flash_Read_HalfWord(uint32_t Address)
{
	return *((uint32_t*)Address);
}



void Flash_Write_check(void)
{
	u32 Address_temp;
	u16 temp;
	Flash_Erase_Page(check_PAGE_ADDRESS);
	Address_temp = check1_ADDRESS;
	temp = (u16)(check1_temp);
	Flash_Write_HalfWord(Address_temp ,temp);
	Address_temp += 0x00000002;
	temp = (u16)(check2_temp);
	Flash_Write_HalfWord(Address_temp ,temp);
	Address_temp += 0x00000002;
	temp = (u16)(check3_temp);
	Flash_Write_HalfWord(Address_temp ,temp);
	Address_temp += 0x00000002;
	temp = (u16)(flash_first_flag);
	Flash_Write_HalfWord(Address_temp , temp);
}





void Flash_Write_all(void)
{ 
	u16 temp;	
	u32 Address_temp;
  Flash_Erase_Page(all_PAGE_ADDRESS );
	
	Address_temp = location_p_ADDRESS;
	temp = (u16)((s16)(PidDataLocation.Kp*100));
	Flash_Write_HalfWord(Address_temp , temp);
	Address_temp += 0x00000002;
	temp = (u16)((s16)(PidDataLocation.Ki*100));
	Flash_Write_HalfWord(Address_temp  ,temp);
	Address_temp += 0x00000002;
	temp = (u16)((s16)(PidDataLocation.Kd*100));
	Flash_Write_HalfWord(Address_temp , temp);
	Address_temp += 0x00000002;
	temp = (u16)((s16)(PidDataLocation.beta));
	Flash_Write_HalfWord(Address_temp , temp);
	Address_temp += 0x00000002;
	temp = (u16)((s16)(PidDataLocation.outbeta));
	Flash_Write_HalfWord(Address_temp  ,temp);
	Address_temp += 0x00000002;
	temp = (u16)(PidDataLocation.dif_prior);
	Flash_Write_HalfWord(Address_temp , temp);
	Address_temp += 0x00000002;
	temp = (u16)((s16)(PidDataLocation.Kvff));
	Flash_Write_HalfWord(Address_temp , temp);
	Address_temp += 0x00000002;
	temp = (u16)((s16)(PidDataLocation.Kaff));
	Flash_Write_HalfWord(Address_temp , temp);
	Address_temp += 0x00000002;
	temp = (u16)((s16)(PidDataLocation.full_beta));
	Flash_Write_HalfWord(Address_temp  , temp);
	
	Address_temp += 0x00000002;
	temp = (u16)((s16)(PidDataSpeed.Kp*100));
	Flash_Write_HalfWord(Address_temp , temp);
	Address_temp += 0x00000002;
	temp = (u16)((s16)(PidDataSpeed.Ki*100));
	Flash_Write_HalfWord(Address_temp  ,temp);
	Address_temp += 0x00000002;
	temp = (u16)((s16)(PidDataSpeed.Kd*100));
	Flash_Write_HalfWord(Address_temp , temp);
	Address_temp += 0x00000002;
	temp = (u16)((s16)(PidDataSpeed.beta));
	Flash_Write_HalfWord(Address_temp , temp);
	Address_temp += 0x00000002;
	temp = (u16)((s16)(PidDataSpeed.outbeta));
	Flash_Write_HalfWord(Address_temp  ,temp);
	Address_temp += 0x00000002;
	temp = (u16)(PidDataSpeed.dif_prior);
	Flash_Write_HalfWord(Address_temp , temp);
	Address_temp += 0x00000002;
	temp = (u16)((s16)(PidDataSpeed.Kvff));
	Flash_Write_HalfWord(Address_temp , temp);
	Address_temp += 0x00000002;
	temp = (u16)((s16)(PidDataSpeed.Kaff));
	Flash_Write_HalfWord(Address_temp , temp);
	Address_temp += 0x00000002;
	temp = (u16)((s16)(PidDataSpeed.full_beta));
	Flash_Write_HalfWord(Address_temp  , temp);
	
	Address_temp += 0x00000002;
	temp = (u16)((s16)(PidDataCurrent.Kp*100));
	Flash_Write_HalfWord(Address_temp , temp);
	Address_temp += 0x00000002;
	temp = (u16)((s16)(PidDataCurrent.Ki*100));
	Flash_Write_HalfWord(Address_temp  ,temp);
	Address_temp += 0x00000002;
	temp = (u16)((s16)(PidDataCurrent.Kd*100));
	Flash_Write_HalfWord(Address_temp , temp);
	Address_temp += 0x00000002;
	temp = (u16)((s16)(PidDataCurrent.beta));
	Flash_Write_HalfWord(Address_temp , temp);
	Address_temp += 0x00000002;
	temp = (u16)((s16)(PidDataCurrent.outbeta));
	Flash_Write_HalfWord(Address_temp  ,temp);
	Address_temp += 0x00000002;
	temp = (u16)(PidDataCurrent.dif_prior);
	Flash_Write_HalfWord(Address_temp , temp);
	Address_temp += 0x00000002;
	temp = (u16)((s16)(PidDataCurrent.Kvff));
	Flash_Write_HalfWord(Address_temp , temp);
	Address_temp += 0x00000002;
	temp = (u16)((s16)(PidDataCurrent.Kaff));
	Flash_Write_HalfWord(Address_temp , temp);
	Address_temp += 0x00000002;
	temp = (u16)((s16)(PidDataCurrent.full_beta));
	Flash_Write_HalfWord(Address_temp  , temp);
	

	Address_temp += 0x00000002;
	temp = (u16)(printf_choose);
	Flash_Write_HalfWord(Address_temp  ,temp);
	Address_temp += 0x00000002;
	temp = (u16)(print_count);
	Flash_Write_HalfWord(Address_temp , temp);
	Address_temp += 0x00000002;
	temp = (u16)(max_current);
	Flash_Write_HalfWord(Address_temp , temp);
	Address_temp += 0x00000002;
	temp = (u16)(overcurrent_count);
	Flash_Write_HalfWord(Address_temp  ,temp);
	Address_temp += 0x00000002;
	temp = (u16)(release_current_count);
	Flash_Write_HalfWord(Address_temp , temp);
	Address_temp += 0x00000002;
	temp = (u16)(base_current_count2);
	Flash_Write_HalfWord(Address_temp , temp);
	Address_temp += 0x00000002;
	temp = ((u16)((s16)(location_init_speed)));
	Flash_Write_HalfWord(Address_temp , temp);
	Address_temp += 0x00000002;
	temp = (u16)(clear_location_count);
	Flash_Write_HalfWord(Address_temp  , temp);
	
	Address_temp += 0x00000002;
	temp = first_location_flag1;
	Flash_Write_HalfWord(Address_temp , temp);
	Address_temp += 0x00000002;
	temp = ID_CHOOSE_MODE;
	Flash_Write_HalfWord(Address_temp  ,temp);
	Address_temp += 0x00000002;
	temp = ID_master;
	Flash_Write_HalfWord(Address_temp , temp);
	Address_temp += 0x00000002;
	temp = ID_Master_TEST;
	Flash_Write_HalfWord(Address_temp , temp);
	Address_temp += 0x00000002;
	temp = ID_Self_TEST;
	Flash_Write_HalfWord(Address_temp  ,temp);
	Address_temp += 0x00000002;
	temp = ID_Search_Zero;
	Flash_Write_HalfWord(Address_temp , temp);	
	Address_temp += 0x00000002;
	temp = (u16)(answer_master);
	Flash_Write_HalfWord(Address_temp , temp);
	Address_temp += 0x00000002;
	temp = (u16)(ecorder_resolution_ratio);
	Flash_Write_HalfWord(Address_temp , temp);

}


void Flash_Read_check(void)
{
	u32 Address_temp;
	Address_temp = check1_ADDRESS;
	check1 = ((u8)(Flash_Read_HalfWord(Address_temp)));
	Address_temp += 0x00000002;
	check2 = ((u8)(Flash_Read_HalfWord(Address_temp)));
	Address_temp += 0x00000002;
	check3 = ((u8)(Flash_Read_HalfWord(Address_temp)));
	Address_temp += 0x00000002;
	flash_first_flag = ((u8)(Flash_Read_HalfWord(Address_temp)));

}

void Flash_Read_all(void)
{
	u32 Address_temp;
	Address_temp = location_p_ADDRESS;
	PidDataLocation.Kp = (((double)(Flash_Read_HalfWord(Address_temp)))/100);
	Address_temp += 0x00000002;
	PidDataLocation.Ki = (((double)(Flash_Read_HalfWord(Address_temp)))/100);
	Address_temp += 0x00000002;
	PidDataLocation.Kd = (((double)(Flash_Read_HalfWord(Address_temp)))/100);
	Address_temp += 0x00000002;
	PidDataLocation.beta = ((double)(Flash_Read_HalfWord(Address_temp)));
	Address_temp += 0x00000002;
	PidDataLocation.outbeta = ((double)(Flash_Read_HalfWord(Address_temp)));
	Address_temp += 0x00000002;
	PidDataLocation.dif_prior = ((int)(Flash_Read_HalfWord(Address_temp)));
	Address_temp += 0x00000002;
	PidDataLocation.Kvff = ((double)(Flash_Read_HalfWord(Address_temp)));
	Address_temp += 0x00000002;
	PidDataLocation.Kaff = ((double)(Flash_Read_HalfWord(Address_temp)));
	Address_temp += 0x00000002;
	PidDataLocation.full_beta = ((double)(Flash_Read_HalfWord(Address_temp)));

	Address_temp += 0x00000002;
	PidDataSpeed.Kp = (((double)(Flash_Read_HalfWord(Address_temp)))/100);
	Address_temp += 0x00000002;
	PidDataSpeed.Ki = (((double)(Flash_Read_HalfWord(Address_temp)))/100);
	Address_temp += 0x00000002;
	PidDataSpeed.Kd = (((double)(Flash_Read_HalfWord(Address_temp)))/100);
	Address_temp += 0x00000002;
	PidDataSpeed.beta = ((double)(Flash_Read_HalfWord(Address_temp)));
	Address_temp += 0x00000002;
	PidDataSpeed.outbeta = ((double)(Flash_Read_HalfWord(Address_temp)));
	Address_temp += 0x00000002;
	PidDataSpeed.dif_prior = ((int)(Flash_Read_HalfWord(Address_temp)));
	Address_temp += 0x00000002;
	PidDataSpeed.Kvff = ((double)(Flash_Read_HalfWord(Address_temp)));
	Address_temp += 0x00000002;
	PidDataSpeed.Kaff = ((double)(Flash_Read_HalfWord(Address_temp)));
	Address_temp += 0x00000002;
	PidDataSpeed.full_beta = ((double)(Flash_Read_HalfWord(Address_temp)));
	
	Address_temp += 0x00000002;
	PidDataCurrent.Kp = (((double)(Flash_Read_HalfWord(Address_temp)))/100);
	Address_temp += 0x00000002;
	PidDataCurrent.Ki = (((double)(Flash_Read_HalfWord(Address_temp)))/100);
	Address_temp += 0x00000002;
	PidDataCurrent.Kd = (((double)(Flash_Read_HalfWord(Address_temp)))/100);
	Address_temp += 0x00000002;
	PidDataCurrent.beta = ((double)(Flash_Read_HalfWord(Address_temp)));
	Address_temp += 0x00000002;
	PidDataCurrent.outbeta = ((double)(Flash_Read_HalfWord(Address_temp)));
	Address_temp += 0x00000002;
	PidDataCurrent.dif_prior = ((int)(Flash_Read_HalfWord(Address_temp)));
	Address_temp += 0x00000002;
	PidDataCurrent.Kvff = ((double)(Flash_Read_HalfWord(Address_temp)));
	Address_temp += 0x00000002;
	PidDataCurrent.Kaff = ((double)(Flash_Read_HalfWord(Address_temp)));
	Address_temp += 0x00000002;
	PidDataCurrent.full_beta = ((double)(Flash_Read_HalfWord(Address_temp)));

	Address_temp += 0x00000002;
	printf_choose = ((int)(Flash_Read_HalfWord(Address_temp)));
	Address_temp += 0x00000002;
	print_count = ((int)(Flash_Read_HalfWord(Address_temp)));
	Address_temp += 0x00000002;
	max_current = ((int)(Flash_Read_HalfWord(Address_temp)));
	Address_temp += 0x00000002;
	overcurrent_count = ((int)(Flash_Read_HalfWord(Address_temp)));
	Address_temp += 0x00000002;
	release_current_count = ((int)(Flash_Read_HalfWord(Address_temp)));
	Address_temp += 0x00000002;
	base_current_count2 = ((int)(Flash_Read_HalfWord(Address_temp)));
	Address_temp += 0x00000002;
	location_init_speed = ((double)((s16)(Flash_Read_HalfWord(Address_temp))));
	Address_temp += 0x00000002;
	clear_location_count = ((int)(Flash_Read_HalfWord(Address_temp)));
	
	Address_temp += 0x00000002;
	first_location_flag1 = Flash_Read_HalfWord(Address_temp);
	Address_temp += 0x00000002;
	ID_CHOOSE_MODE = Flash_Read_HalfWord(Address_temp);
	Address_temp += 0x00000002;
	ID_master = Flash_Read_HalfWord(Address_temp);
	Address_temp += 0x00000002;
	ID_Master_TEST = Flash_Read_HalfWord(Address_temp);
	Address_temp += 0x00000002;
	ID_Self_TEST = Flash_Read_HalfWord(Address_temp);
	Address_temp += 0x00000002;
	ID_Search_Zero =  Flash_Read_HalfWord(Address_temp);
	Address_temp += 0x00000002;
	answer_master = ((u8)(Flash_Read_HalfWord(Address_temp)));
	Address_temp += 0x00000002;
	ecorder_resolution_ratio = ((int)(Flash_Read_HalfWord(Address_temp)));

}



void Flash_Write(void)
{
	Flash_Write_check();
	Flash_Write_all();
}

void Flash_Read(void)
{
	Flash_Read_check();
	if((check1 == 0x57) && (check2 == 0x48) && (check3 == 0x55) && 	(flash_first_flag == 0x01))
	{
		Flash_Read_all();
	}
}



