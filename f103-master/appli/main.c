/**
  ******************************************************************************
  * @file    main.c
  * @brief   Fonction principale.
  * @author  Clémence MAIGNAN - Timothée VIARD
  * @date    09 mars 2023
  ******************************************************************************
  */

/**
  * @brief  Inclusion des bibliothèques
  */
#include "stm32f1xx_hal.h"
#include "stm32f1_uart.h"
#include "stm32f1_sys.h"
#include "stm32f1_gpio.h"
#include "macro_types.h"
#include "systick.h"
#include "servo.h"
#include "stm32f1_adc.h"
#include "display.h"
#include "stdbool.h"

/**
  * @brief  Inclusion des bibliothèques
  */
#define ADC_SENSOR_CHANNEL_0		ADC_0
#define ADC_SENSOR_CHANNEL_1		ADC_1
#define ADC_SENSOR_CHANNEL_2		ADC_2
#define ADC_SENSOR_CHANNEL_3		ADC_3
#define ADC_SENSOR_CHANNEL_4		ADC_8

/**
  * @brief  Définition des couleurs
  */
typedef enum {
	white = 0xFFFF,
	black = 0x0000,
	blue = 0x001F,
	red = 0xF800,
	green = 0x07E0
} Color;

/**
  * @brief  Définition des doigts
  */
typedef enum {
	pouce = 4,
	indexD = 6,
	majeur = 8,
	annulaire = 10,
	auriculaire = 12
} Doigt;

/**
  * @brief  Définition des objets Servo
  */
Servo servo1 = {0, TIM_CHANNEL_1, TIMER1_ID, 0, 200, 75};
Servo servo2 = {0, TIM_CHANNEL_2, TIMER1_ID, 0, 225, 60};
Servo servo3 = {0, TIM_CHANNEL_3, TIMER1_ID, 0, 225, 60};
Servo servo4 = {0, TIM_CHANNEL_4, TIMER1_ID, 1, 75, 260};
Servo servo5 = {0, TIM_CHANNEL_1, TIMER4_ID, 1, 60, 225};

/**
  * @brief  Définition des objets Capteur
  */
Capteur capt1 = {0, 0, 0, 0};
Capteur capt2 = {0, 0, 0, 0};
Capteur capt3 = {0, 0, 0, 0};
Capteur capt4 = {0, 0, 0, 0};
Capteur capt5 = {0, 0, 0, 0};

/**
  * @brief  Fonction de traitement des millisecondes
  */
static volatile uint32_t t = 0;
void process_ms(void)
{
	if(t)
		t--;
}

/**
  * @brief  Fonction de traitement des millisecondes
  */
void initScreen(void){
	TFT_LineBreak();
	TFT_Print_CenterAligned("Etat de la main", false, red);
	TFT_LineBreak();
	TFT_LineBreak();
	TFT_Print("Pouce :", true, black);
	TFT_LineBreak();
	TFT_Print("Index :", true, black);
	TFT_LineBreak();
	TFT_Print("Majeur :", true, black);
	TFT_LineBreak();
	TFT_Print("Annulaire :", true, black);
	TFT_LineBreak();
	TFT_Print("Auriculaire :", true, black);
	TFT_LineBreak();
}

/**
  * @brief Définition de la position du capteur
  * @param capt Le capteur dont on souhaite définir la position
  * @return Le capteur avec la position mise à jour
  */
void updateValue(void)
{
	char str[12];
	sprintf(str, "%d", capt1.position);
	TFT_DefineLine(pouce);
	TFT_Print_RightAligned(str, false, black);
	sprintf(str, "%d", capt2.position);
	TFT_DefineLine(indexD);
	TFT_Print_RightAligned(str, false, black);
	sprintf(str, "%d", capt3.position);
	TFT_DefineLine(majeur);
	TFT_Print_RightAligned(str, false, black);
	sprintf(str, "%d", capt4.position);
	TFT_DefineLine(annulaire);
	TFT_Print_RightAligned(str, false, black);
	sprintf(str, "%d", capt5.position);
	TFT_DefineLine(auriculaire);
	TFT_Print_RightAligned(str, false, black);
}

/**
  * @brief  Initialisation des capteurs
  */
void capteurInit(void){
	capt1.max = ADC_getValue(ADC_1);
	capt2.max = ADC_getValue(ADC_0);
	capt3.max = ADC_getValue(ADC_2);
	capt4.max = ADC_getValue(ADC_3);
	capt5.max = ADC_getValue(ADC_8);

	capt1.min = ADC_getValue(ADC_1);
	capt2.min = ADC_getValue(ADC_0);
	capt3.min = ADC_getValue(ADC_2);
	capt4.min = ADC_getValue(ADC_3);
	capt5.min = ADC_getValue(ADC_8);
}

/**
  * @brief Définition de la position du capteur
  * @param capt Le capteur dont on souhaite définir la position
  * @return Le capteur avec la position mise à jour
  */
Capteur defCapteurPosition(Capteur capt){
	if(capt.value < capt.min){
		capt.min = capt.value;
	}
	if(capt.value > capt.max){
			capt.max = capt.value;
		}
	if(capteurDelta(capt) != 0){
		capt.position = ((capt.value - capt.min) * 100) / capteurDelta(capt);
	}
	return capt;
}

/**
  * @brief  Fonction principale
  */
int main(void)
{
	//Initialisation de la couche logicielle HAL (Hardware Abstraction Layer)
	//Cette ligne doit rester la premiere etape de la fonction main().
	HAL_Init();

	//Initialisation de l'UART2 a la vitesse de 115200 bauds/secondes (92kbits/s) PA2 : Tx  | PA3 : Rx.
	//Attention, les pins PA2 et PA3 ne sont pas reliees jusqu'au connecteur de la Nucleo.
	//Ces broches sont redirigees vers la sonde de debogage, la liaison UART etant ensuite encapsulee sur l'USB vers le PC de developpement.
	UART_init(UART2_ID,115200);

	//"Indique que les printf sortent vers le peripherique UART2."
	SYS_set_std_usart(UART2_ID, UART2_ID, UART2_ID);

	//Initialisation du port de la led Verte (carte Nucleo)
	BSP_GPIO_PinCfg(LED_GREEN_GPIO, LED_GREEN_PIN, GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH);

	//Initialisation du port du bouton bleu (carte Nucleo)
	BSP_GPIO_PinCfg(BLUE_BUTTON_GPIO, BLUE_BUTTON_PIN, GPIO_MODE_INPUT,GPIO_PULLUP,GPIO_SPEED_FREQ_HIGH);

	//On ajoute la fonction process_ms a la liste des fonctions appelees automatiquement chaque ms par la routine d'interruption du peripherique SYSTICK
	Systick_add_callback_function(&process_ms);

	ADC_init();
	TFT_Init();
	initScreen();
	capteurInit();

	SERVO_init(servo1);
	SERVO_init(servo2);
	SERVO_init(servo3);
	SERVO_init(servo4);
	SERVO_init(servo5);


	while(1){

		capt1.value = ADC_getValue(ADC_1);
		capt1 = defCapteurPosition(capt1);
		capt2.value = ADC_getValue(ADC_0);
		capt2 = defCapteurPosition(capt2);
		capt3.value = ADC_getValue(ADC_2);
		capt3 = defCapteurPosition(capt3);
		capt4.value = ADC_getValue(ADC_3);
		capt4 = defCapteurPosition(capt4);
		capt5.value = ADC_getValue(ADC_8);
		capt5 = defCapteurPosition(capt5);

		SERVO_main(capt1, servo1);
		SERVO_main(capt2, servo2);
		SERVO_main(capt3, servo3);
		SERVO_main(capt4, servo4);
		SERVO_main(capt5, servo5);

		updateValue();

		HAL_Delay(50);

	}
}



