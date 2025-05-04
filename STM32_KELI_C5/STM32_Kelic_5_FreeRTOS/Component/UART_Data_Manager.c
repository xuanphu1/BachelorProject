#include "UART_Data_Manager.h"

DataManager_t *DataManager;



static uint16_t strlen_custom(const char *str) {
    uint16_t length = 0;
    while (*str++) { // Lặp qua từng ký tự cho đến khi gặp '\0'
        length++;
    }
    return length;
}

static void uint16_to_char(uint16_t value, char *buffer) {
    uint8_t i = 0;
    char temp[6];  // Tối đa 5 chữ số + 1 null-terminator

    if (value == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }

    while (value > 0) {
        temp[i++] = (value % 10) + '0';
        value /= 10;
    }

    uint8_t j = 0;
    while (i > 0) {
        buffer[j++] = temp[--i];
    }

    buffer[j] = '\0';  // Kết thúc chuỗi
}

static void memset_custom(void *ptr, uint8_t value, uint16_t size) {
	uint8_t *p = (uint8_t*)ptr;  // Ép kiểu con trỏ về `uint8_t*`
	while (size--) {
			*p++ = value;  // Gán giá trị và tăng con trỏ
	}
}


void getSignalMode(void){
	
	DataManager->SetAuto = (Set_Auto_t)DataManager->UartBuff[6];
	DataManager->modeActive = (Mode_t)DataManager->UartBuff[7];

}


void InitDataToESP32(void) {
		char SymbolData[] = {'T','W','P','C','Y','S'};
    char tempBuffer[6];  // Đủ để chứa số `uint16_t`
    char *ptr = DataManager->DataToESP32;  // Con trỏ để ghi dữ liệu
		DataManager->DataTemperature = 0;
    memset_custom(DataManager->DataToESP32, 0, sizeof(DataManager->DataToESP32)); // Xóa dữ liệu cũ
	
    uint16_t *dataFields[] = {
				&DataManager->DataTemperature,
				&DataManager->DataSensor_Analog[WATERLEVER],
				&DataManager->DataSensor_Analog[PH],
				&DataManager->DataSensor_Analog[CONDUCTIVITY],
				&DataManager->DataSensor_Analog[TDS],
				&DataManager->StatusDeveice,    
    };

    for (uint8_t i = 0; i < 6; i++) {
        uint16_to_char(*dataFields[i], tempBuffer);  // Chuyển số thành chuỗi

        // Dùng con trỏ `tempPtr` thay vì `tempBuffer++`
        char *tempPtr = tempBuffer;
        if (i < 6) {
            *ptr++ = SymbolData[i];  // Thêm dấu casc symbol giữa các số
        }
        while (*tempPtr) {
            *ptr++ = *tempPtr++;  // Ghi dữ liệu vào `DataToESP32`
        }

       
    }

    *ptr = '\0';  // Kết thúc chuỗi
}


//xx.xx.xx.xx.xx.xx.at.mo.end


void ControlDevice(void){
		getSignalMode();
    if (DataManager->SetAuto == TURN_OFF_AUTO){
				for (Device_t device  = FAN; device <= FEEDER; device++) {
				uint8_t deviceState = (DataManager->UartBuff[device] & 0x01) ? 1 : 0;  
				WritePin(Port_B, (Pin_gpio_t)(device+3), deviceState);
				if (device == FEEDER) WritePin(Port_A, PIN_15,deviceState);
				}
    
			DataManager->StatusDeveice =  ((DataManager->UartBuff[FAN]        & 0x1) << FAN) 		| 
                                    ((DataManager->UartBuff[FILTER]     & 0x1) << FILTER) | 
                                    ((DataManager->UartBuff[PUMB]       & 0x1) << PUMB)  	| 
                                    ((DataManager->UartBuff[HEATER]     & 0x1) << HEATER) | 
                                    ((DataManager->UartBuff[LIGHT]      & 0x1) << LIGHT)	|
                                    ((DataManager->UartBuff[FEEDER]     & 0x1) << FEEDER) ; 
    } else {
			
			if (DataManager->DataTemperature >= 30) {}
			if (DataManager->DataTemperature <= 20) {}
			if(DataManager->UartBuff[FEEDER] == 1) {}
			
			for (Device_t device  = FAN; device <= FEEDER; device++) {
			uint8_t deviceState = (DataManager->UartBuff[device] & 0x01) ? 1 : 0;  
			WritePin(Port_B, (Pin_gpio_t)(device+3), deviceState);
			if (device == FEEDER) WritePin(Port_A, PIN_15,deviceState);
			}
		
		
		}

		
    
}


void InitDataManager(DataManager_t *DataManager_t){
    DataManager = DataManager_t;
}


void SignalModeNormal_LED(void){
	ON_Led_Hardware();
	Delay_SysTick(50);
	OFF_Led_Hardware();
	Delay_SysTick(50);
	
	ON_Led_Hardware();
	Delay_SysTick(50);
	OFF_Led_Hardware();
	Delay_SysTick(50);
	
	ON_Led_Hardware();
	Delay_SysTick(50);
	OFF_Led_Hardware();
	Delay_SysTick(50);
	
	ON_Led_Hardware();
	Delay_SysTick(50);
	OFF_Led_Hardware();
	Delay_SysTick(50);
	
	ON_Led_Hardware();
	Delay_SysTick(50);
	OFF_Led_Hardware();
	Delay_SysTick(50);
}

void SendData(void){
	
    InitDataToESP32();
    TransmitDataUART(UART_1,(uint8_t*)&DataManager->DataToESP32,strlen_custom(DataManager->DataToESP32));
    SignalModeNormal_LED();
}


