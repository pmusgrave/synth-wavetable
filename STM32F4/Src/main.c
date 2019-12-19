/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "globals.h"
#include "spi_handler.h"
#include "midi.h"
#include "waves.h"
#include "oscillator.h"
#include "lfo.h"
#include "envelopes.h"
//#include "r2rdac.h"
#include "dac.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
DAC_HandleTypeDef hdac;
I2C_HandleTypeDef hi2c1;
I2S_HandleTypeDef hi2s2;
SPI_HandleTypeDef hspi1;
TIM_HandleTypeDef htim6;
UART_HandleTypeDef huart4;
/* USER CODE BEGIN PV */
uint8_t uart_tx_data = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DAC_Init(void);
static void MX_I2C1_Init(void);
static void MX_I2S2_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM6_Init(void);
static void MX_UART4_Init(void);
/* USER CODE BEGIN PFP */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void handle_byte_queue();
void handle_midi_queue();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DAC_Init();
  MX_I2C1_Init();
  MX_I2S2_Init();
  MX_SPI1_Init();
  MX_TIM6_Init();
  MX_UART4_Init();
  /* USER CODE BEGIN 2 */
  /* USER CODE BEGIN 2 */
  // uint8_t init_msg[20] = {"\nSTM32F429!\n"};
  // HAL_UART_Transmit(&huart4, init_msg, 20, 50);
  HAL_Delay(1000);
  InitDac(&hi2c1);
  init_wavetable();
  HAL_TIM_Base_Start_IT(&htim6);
  //HAL_DAC_Start(&hdac, DAC_CHANNEL_2);

  for(int i = 0; i < VOICES; i++) {
    env_state[i] = NOT_TRIGGERED;
    note_on[i] = MIDI_NOTE_OFF;
    note_freq[i] = 0;
    lfo_freq[i] = 20;
  }

  // DAC TEST NOTE
  struct midi_msg test_msg = {
                              0x90,
                              0x82,
                              0xFF,
                              0x00
  };
  enqueue(test_msg);
  // END DAC TEST NOTE

  //  uint8_t process_msg_flag  = 0;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    // uint8_t byte = SPI_ReceiveByte();
    HAL_UART_Receive_IT(&huart4, &uart_tx_data, 1);
    handle_byte_queue();
    handle_midi_queue();
    if(update_value_flag){
      update_value_flag = 0;
      update_lfos();
      update_envelope();
      update_output_value();
      //HAL_DAC_SetValue(&hdac, DAC_CHANNEL_2, DAC_ALIGN_8B_R, output_val);

      HAL_I2S_Transmit(&hi2s2, &output_val, 32, 100);
    }
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 125;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2S;
  PeriphClkInitStruct.PLLI2S.PLLI2SN = 50;
  PeriphClkInitStruct.PLLI2S.PLLI2SR = 2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief DAC Initialization Function
  * @param None
  * @retval None
  */
static void MX_DAC_Init(void)
{

  /* USER CODE BEGIN DAC_Init 0 */

  /* USER CODE END DAC_Init 0 */

  DAC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN DAC_Init 1 */

  /* USER CODE END DAC_Init 1 */
  /** DAC Initialization 
  */
  hdac.Instance = DAC;
  if (HAL_DAC_Init(&hdac) != HAL_OK)
  {
    Error_Handler();
  }
  /** DAC channel OUT1 config 
  */
  sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
  if (HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /** DAC channel OUT2 config 
  */
  if (HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DAC_Init 2 */

  /* USER CODE END DAC_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter 
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter 
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief I2S2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2S2_Init(void)
{

  /* USER CODE BEGIN I2S2_Init 0 */

  /* USER CODE END I2S2_Init 0 */

  /* USER CODE BEGIN I2S2_Init 1 */

  /* USER CODE END I2S2_Init 1 */
  hi2s2.Instance = SPI2;
  hi2s2.Init.Mode = I2S_MODE_MASTER_TX;
  hi2s2.Init.Standard = I2S_STANDARD_PHILIPS;
  hi2s2.Init.DataFormat = I2S_DATAFORMAT_32B;
  hi2s2.Init.MCLKOutput = I2S_MCLKOUTPUT_ENABLE;
  hi2s2.Init.AudioFreq = I2S_AUDIOFREQ_44K;
  hi2s2.Init.CPOL = I2S_CPOL_LOW;
  hi2s2.Init.ClockSource = I2S_CLOCK_PLL;
  hi2s2.Init.FullDuplexMode = I2S_FULLDUPLEXMODE_ENABLE;
  if (HAL_I2S_Init(&hi2s2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2S2_Init 2 */

  /* USER CODE END I2S2_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_SLAVE;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_HARD_INPUT;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 0;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 1290;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

}

/**
  * @brief UART4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART4_Init(void)
{

  /* USER CODE BEGIN UART4_Init 0 */

  /* USER CODE END UART4_Init 0 */

  /* USER CODE BEGIN UART4_Init 1 */

  /* USER CODE END UART4_Init 1 */
  huart4.Instance = UART4;
  huart4.Init.BaudRate = 9600;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_1;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART4_Init 2 */

  /* USER CODE END UART4_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10 
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pins : PE7 PE8 PE9 PE10 
                           PE11 PE12 PE13 */
  GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10 
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
  if(uart_tx_data != 0 && uart_tx_data != '\n'){
    // HAL_UART_Transmit(&huart1, &uart_tx_data, 1, 50);
    enqueue_byte(uart_tx_data);
  }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
  if(htim->Instance == TIM6){
    update_value_flag = 1;
  }
}

void handle_byte_queue() {
  // probably need to refactor these SPI flags
  static uint8_t note_on_flag;
  static uint8_t note_off_flag;
  static uint8_t attack_cc_flag;
  static uint8_t decay_cc_flag;
  static uint8_t sustain_cc_flag;
  static uint8_t release_cc_flag;
  static uint8_t waveshape_cc_flag;
  static uint8_t lfo_cc_flag;

  if(spi_byte_queue.head != spi_byte_queue.tail){
    uint8_t value = dequeue_byte();
    uint8_t skip_command = 0;

    // HAL_UART_Transmit(&huart1, &value, 1, 50);

    if(attack_cc_flag) {
      attack_cc_flag = 0;
      struct midi_msg new_midi_msg =
        {
         ATTACK_CC,
         value,
         0,
         0
        };
      enqueue(new_midi_msg);
      skip_command = 1;
    }
    else if(decay_cc_flag) {
      decay_cc_flag = 0;
      struct midi_msg new_midi_msg =
        {
         DECAY_CC,
         value,
         0,
         0
        };
      enqueue(new_midi_msg);
      skip_command = 1;
    }
    else if(sustain_cc_flag) {
      sustain_cc_flag = 0;
      struct midi_msg new_midi_msg =
        {
         SUSTAIN_CC,
         value,
         0,
         0
        };
      enqueue(new_midi_msg);
      skip_command = 1;
    }
    else if(release_cc_flag) {
      release_cc_flag = 0;
      struct midi_msg new_midi_msg =
        {
         RELEASE_CC,
         value,
         0,
         0
        };
      enqueue(new_midi_msg);
      skip_command = 1;
    }
    else if(note_on_flag) {
      note_on_flag = 0;
      struct midi_msg new_midi_msg =
        {
         MIDI_NOTE_ON,
         value,
         0,
         0
        };
      enqueue(new_midi_msg);
      skip_command = 1;
    }
    else if (note_off_flag) {
      note_off_flag = 0;
      struct midi_msg new_midi_msg =
        {
         MIDI_NOTE_OFF,
         value,
         0,
         0
        };
      enqueue(new_midi_msg);
      skip_command = 1;
    }
    else if(waveshape_cc_flag) {
      waveshape_cc_flag = 0;
      struct midi_msg new_midi_msg =
        {
         WAVESHAPE_CC,
         value,
         0,
         0
        };
      enqueue(new_midi_msg);
      skip_command = 1;
    }
    else if(lfo_cc_flag){
      lfo_cc_flag = 0;
      struct midi_msg new_midi_msg =
        {
         LFO_CC,
         value,
         0,
         0
        };
      enqueue(new_midi_msg);
      skip_command = 1;
    }

    if(!skip_command){
      switch(value){
      case ATTACK_CC:
        attack_cc_flag = 1;
        break;
      case DECAY_CC:
        decay_cc_flag = 1;
        break;
      case SUSTAIN_CC:
        sustain_cc_flag = 1;
        break;
      case RELEASE_CC:
        release_cc_flag = 1;
        break;
      case MIDI_NOTE_ON:
        note_on_flag = 1;
        break;
      case MIDI_NOTE_OFF:
        note_off_flag = 1;
        break;
      case WAVESHAPE_CC:
        waveshape_cc_flag = 1;
        break;
      case LFO_CC:
        lfo_cc_flag = 1;
      }
    }
  }
}

void handle_midi_queue() {
  // uint8_t value;

  if(midi_msg_queue.head != midi_msg_queue.tail) {
    struct midi_msg current_midi_msg = dequeue();
    // value = current_midi_msg.byte1;

    switch(current_midi_msg.byte0) {
    case ATTACK_CC:
      attack = current_midi_msg.byte1 * 2;
      //UART_PrintADSR(&huart1);
      break;
    case DECAY_CC:
      decay = current_midi_msg.byte1 * 2;
      //UART_PrintADSR(&huart1);
      break;
    case SUSTAIN_CC:
      sustain = current_midi_msg.byte1 * 2;
      //UART_PrintADSR(&huart1);
      break;
    case RELEASE_CC:
      release = current_midi_msg.byte1 * 2;
      //UART_PrintADSR(&huart1);
      break;
    case MIDI_NOTE_ON:
      for (int i = 0; i < VOICES; i++) {
        if(note_on[i] == MIDI_NOTE_OFF){
          note_on[i] = MIDI_NOTE_ON;
          note_freq[i] = current_midi_msg.byte1;
          env_state[i] = ATTACK_MODE;
          break;
        }
      }
      break;
    case MIDI_NOTE_OFF:
      for (int i = 0; i < VOICES; i++) {
        if (note_on[i] == MIDI_NOTE_ON && note_freq[i] == current_midi_msg.byte1){
          //note_on[i] = MIDI_NOTE_OFF;
          env_state[i] = RELEASE_MODE;
        }
      }
      break;
      /*
    case WAVESHAPE_CC:
      if(current_midi_msg.byte1 < 50) {
        waveshape1 = base_sine;
        waveshape2 = base_tri;
      }
      else if(current_midi_msg.byte1 < 100) {
        waveshape1 = base_tri;
        waveshape2 = base_pos_saw;
      }
      else if(current_midi_msg.byte1 < 150) {
        waveshape1 = base_pos_saw;
        waveshape2 = base_neg_saw;
      }
      else if(current_midi_msg.byte1 < 200) {
        waveshape1 = base_neg_saw;
        waveshape2 = base_sq;
      }
      else {
        waveshape1 = base_sq;
        waveshape2 = base_sine;
      }
      break;
    case LFO_CC:
      global_lfo_freq = current_midi_msg.byte1 * 2;
      break;
      */
    }
  }
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
