
//Empty C++ Application
#include <stdio.h>
#include "xil_types.h"
#include "xtmrctr.h"
#include "xparameters.h"
#include "xil_cache.h"
#include "xil_io.h"
#include "xil_exception.h"
#include "xiicps.h"
#include "xscugic.h"
#include "xgpio.h"
#include "xil_printf.h"
#include <cstdlib>
#include <cstring>
#include "graphics_driver.h"
#include "menu.h"
#include "xuartps.h"
#include "digits.h"
#include "game_logic.h"

#define INTC_DEVICE_ID 		XPAR_PS7_SCUGIC_0_DEVICE_ID
#define BTNS_DEVICE_ID		XPAR_AXI_GPIO_1_DEVICE_ID
#define INTC_GPIO_INTERRUPT_ID XPAR_FABRIC_AXI_GPIO_1_IP2INTC_IRPT_INTR
#define BTN_INT 			XGPIO_IR_CH1_MASK
#define UART_BASEADDR XPAR_PS7_UART_1_BASEADDR

XGpio BTNInst;
volatile bool TIMER_INTR_FLG;
XScuGic INTCInst;
static int btn_value;

extern bool GameOver;
extern int GameState;

static void BTN_Intr_Handler(void *baseaddr_p);

void GameOver_loop() {
	//do something
	//send a message in UART
}
void Timer_InterruptHandler(XTmrCtr *data, u8 TmrCtrNumber)
{
	if(!GameOver && GameState == GameStart)
		update_block();
	XTmrCtr_Stop(data,TmrCtrNumber);
	XTmrCtr_Reset(data,TmrCtrNumber);
	//Update Stuff
	TIMER_INTR_FLG = true;
}

int SetUpInterruptSystem(XScuGic *XScuGicInstancePtr){
	XGpio_InterruptEnable(&BTNInst, BTN_INT);
	XGpio_InterruptGlobalEnable(&BTNInst);

	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
	(Xil_ExceptionHandler) XScuGic_InterruptHandler,
	XScuGicInstancePtr);

	Xil_ExceptionEnable();
	return XST_SUCCESS;
}

/*INTERRUPT TUTORIAL FUNCTIONS */
void BTN_Intr_Handler(void *InstancePtr)
{
	// Disable GPIO interrupts
	XGpio_InterruptDisable(&BTNInst, BTN_INT);
	// Ignore additional button presses
	if ((XGpio_InterruptGetStatus(&BTNInst) & BTN_INT) !=
			BTN_INT) {
			return;
		}
	btn_value = XGpio_DiscreteRead(&BTNInst, 1)& 0x1F;

	CheckState(btn_value);
	if(GameState == GameStart) {
		switch (btn_value) {
			case 1: // CENTER
				break;
			case 2:
				change_direction(1); // DOWN
				break;
			case 4:
				change_direction(3); // LEFT
				break;
			case 8:
				change_direction(4);  // RIGHT
				break;
			case 16:
				change_direction(2); // UP
				break;
			default:
				printf("Default case is Matched.");
				break;
			}
	}

    (void)XGpio_InterruptClear(&BTNInst, BTN_INT);
    XGpio_InterruptClear(&BTNInst, XGPIO_IR_MASK);
    // Enable GPIO interrupts
    XGpio_InterruptEnable(&BTNInst, BTN_INT);
}

int IntcInitFunction(u16 DeviceId, XGpio *GpioInstancePtr, XTmrCtr* TimerInstancePtr)
{
	XScuGic_Config *IntcConfig;
	int status;

	// Interrupt controller initialisation
	IntcConfig = XScuGic_LookupConfig(DeviceId);
	if(NULL == IntcConfig) {
		return XST_FAILURE;
	}
	status = XScuGic_CfgInitialize(&INTCInst, IntcConfig, IntcConfig->CpuBaseAddress);
	if(status != XST_SUCCESS)
		return XST_FAILURE;

	// Call to interrupt setup
	status = SetUpInterruptSystem(&INTCInst);
	if(status != XST_SUCCESS)
		return XST_FAILURE;

	// Connect GPIO interrupt to handler
	status = XScuGic_Connect(&INTCInst,
					  	  	 INTC_GPIO_INTERRUPT_ID,
					  	  	 (Xil_ExceptionHandler)BTN_Intr_Handler,
					  	  	 (void *)GpioInstancePtr);
	if(status != XST_SUCCESS)
		return XST_FAILURE;

	// Connect Timer interrupt to handler
	status = XScuGic_Connect(&INTCInst,
			61,
			(Xil_ExceptionHandler)XTmrCtr_InterruptHandler,
			(void *)TimerInstancePtr);
	if(status != XST_SUCCESS)
		return XST_FAILURE;
	// Enable GPIO interrupts interrupt
	XGpio_InterruptEnable(GpioInstancePtr, 1);
	XGpio_InterruptGlobalEnable(GpioInstancePtr);

	// Enable GPIO and timer interrupts in the controller
	XScuGic_Enable(&INTCInst, INTC_GPIO_INTERRUPT_ID);
	XScuGic_Enable(&INTCInst, 61);

	return XST_SUCCESS;
}


int main()
{
	xil_printf("It's in the second cpu!!!");
	int xStatus;
	XTmrCtr TimerInstancePtr;

	/*Setting up timer interrupt  */

			xStatus = XTmrCtr_Initialize(&TimerInstancePtr,XPAR_AXI_TIMER_0_DEVICE_ID);
			XTmrCtr_SetHandler(&TimerInstancePtr,
			(XTmrCtr_Handler)Timer_InterruptHandler,
			&TimerInstancePtr);

			//Reset Values
			XTmrCtr_SetResetValue(&TimerInstancePtr,
			0, //Change with generic value
			//0xFFF0BDC0);
			//0x23C34600);
			0xFF3CB9FF);
			//Interrupt Mode and Auto reload
//			XTmrCtr_SetOptions(&TimerInstancePtr,
//			XPAR_AXI_TIMER_0_DEVICE_ID,
//			(XTC_INT_MODE_OPTION | XTC_AUTO_RELOAD_OPTION ));
			XTmrCtr_SetOptions(&TimerInstancePtr,
								0,
								(XTC_INT_MODE_OPTION | XTC_AUTO_RELOAD_OPTION ));
			//xStatus=ScuGicInterrupt_Init(XPAR_PS7_SCUGIC_0_DEVICE_ID,&TimerInstancePtr);
		/*End of timer setup */

	xStatus = XGpio_Initialize(&BTNInst, BTNS_DEVICE_ID);
	if(xStatus != XST_SUCCESS)
		return XST_FAILURE;
	XGpio_SetDataDirection(&BTNInst, 1, 0xFF);

	xStatus = IntcInitFunction(INTC_DEVICE_ID, &BTNInst, &TimerInstancePtr);
	if(xStatus != XST_SUCCESS)
		return XST_FAILURE;


	/*Enable the interrupt for the device and then cause (simulate) an interrupt so the handlers will be called*/
	XScuGic_Enable(&INTCInst, INTC_GPIO_INTERRUPT_ID);
	XScuGic_SetPriorityTriggerType(&INTCInst, 61, 0xa0, 3);
	Init_Map();
	u32 CntrlRegister;
	XUartPs_WriteReg(UART_BASEADDR, XUARTPS_CR_OFFSET,
					  ((CntrlRegister & ~XUARTPS_CR_EN_DIS_MASK) |
					   XUARTPS_CR_TX_EN | XUARTPS_CR_RX_EN));
	xil_printf("SNAKE GAME BEGINS SSSSSSSSS \n");
	StartScreenStartGame();
	Xil_DCacheDisable();
	/* initializing snake */
	// playspace dimensions 1100 by 800 pixels
	// starting playspace coordinate = 90, 130


	while(1) {
		TIMER_INTR_FLG = false;
		XTmrCtr_Start(&TimerInstancePtr,0);
				while(TIMER_INTR_FLG == false){
				}
		TIMER_INTR_FLG = false;

	}
	return 0;
}

