#include "debug.h"
#include "uart.h"

void ADC_Function_Init(void) {
  ADC_InitTypeDef ADC_InitStructure = {0};
  GPIO_InitTypeDef GPIO_InitStructure = {0};

  // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  ADC_DeInit(ADC1);

  ADC_CLKConfig(ADC1, ADC_CLK_Div6);

  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 1;
  ADC_Init(ADC1, &ADC_InitStructure);
  ADC_Cmd(ADC1, ENABLE);
}

u16 Get_ADC_Val(u8 ch) {
  u16 val;
  ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_11Cycles);
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
  while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC))
    ;
  val = ADC_GetConversionValue(ADC1);
  return val;
}


int main(void) {
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  SystemCoreClockUpdate();
  Delay_Init();
  PIOC_INIT();
  PIOC_UART_INIT(115200, 0, 1, 8);

  ADC_Function_Init();

  R8_CTRL_WR = 0X33; // To R8_CTRL_WR write any value,then start
  while (1) {


    u16 adc1 = Get_ADC_Val(ADC_Channel_9);
    u8 buff[] = {'\r','\n', 'L', (adc1 >> 8) & 0xFF, adc1 & 0xFF,'F','\r','\n'};

    PIOC_UART_SEND(buff, sizeof(buff));
    Delay_Ms(100);
  }
}
