/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2026 STMicroelectronics.
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
#include <stdlib.h>
#include <stdbool.h>
#include "st7735\st7735.h"
#include <stdio.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define BOTAO_INICIO	HAL_GPIO_ReadPin(botao_inicial_GPIO_Port, botao_inicial_Pin)
#define BOTAO_ENTRAR	HAL_GPIO_ReadPin(botao_entrada_GPIO_Port, botao_entrada_Pin)
#define BOTAO_SAIR		HAL_GPIO_ReadPin(botao_saida_GPIO_Port, botao_saida_Pin)
#define BOTAO_RETORNAR	HAL_GPIO_ReadPin(botao_retorno_GPIO_Port, botao_retorno_Pin)
#define DARK_GREEN  0x03E0
#define WHITE  0xFFFF
#define BLACK  0x0000

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */
int senhaAleatoria[4];
int senhaDigitada[4];
int alunos[100];
int pos = 1;
GPIO_PinState clickSomar;
GPIO_PinState clickInicio;
GPIO_PinState clickMudar;
GPIO_PinState clickDezena;
GPIO_PinState clickUnidade;
GPIO_PinState clickConfirmar1;
GPIO_PinState clickConfirmar2;
GPIO_PinState clickEntrarAluno;
GPIO_PinState clickFinalizar1;
GPIO_PinState clickFinalizar2;
GPIO_PinState clickSaiu;
GPIO_PinState clickVoltou;
int digito1 = 0;
int digito2 = 0;
int digito3 = 0;
int digito4 = 0;
int tentativas = 0;
uint32_t tempoBloq = 0;
bool senhaCorreta = true;
bool AulaAtiva = false;
bool telaInicial = false;
int maxAlunos = 0;
int quantAlunos = 0;
uint32_t inicio = 0;
uint32_t tempoSaida = 0;
uint32_t tempoVolta = 0;
uint32_t mediaTempoFora = 0;
uint32_t tempoTotalFora = 0;
uint32_t fim = 0;
uint32_t duracao = 0;
int quantSaidas = 0;
int quantAlunoFora = 0;
int larguraMax = 70;
int altura = 6;
int presentes = 0;
int larguraAtual = 0;
int quantBloqueios = 0;
int matricula = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */
void DigitarSenha(void);
void InserirAlunos(void);
void ControlarPresenca(void);
void MostrarSenha(void);
void MostrarQuantidade(void);
void MostrarAluno(int matricula);
void ControlarSaida(void);
void BarraDeCarregamento(void);
void MostrarBarraComPresenca(void);
void MostrarRelatorio(void);
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
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
  ST7735_Init();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  clickInicio = BOTAO_INICIO;
	  if(clickInicio == 0){
		  srand(HAL_GetTick());
		  ST7735_FillScreen(DARK_GREEN);
		  ST7735_WriteString(25, 30, "Bem-Vindo!", Font_11x18, WHITE, DARK_GREEN);
		  HAL_Delay(2000);
		  ST7735_FillScreen(DARK_GREEN);
		  ST7735_WriteString(20, 10, "Digite sua senha:", Font_7x10, WHITE, DARK_GREEN);
		  ST7735_WriteString(10, 30, "Use PA9 para somar.", Font_7x10, WHITE, DARK_GREEN);
		  ST7735_WriteString(10, 45, "Use PA11 para mudar", Font_7x10, WHITE, DARK_GREEN);
		  HAL_Delay(3500);

		 for(int i = 0; i < 4; i++){
			 senhaAleatoria[i]  = rand() % 10;
		 }

		 tentativas = 0;
		 while(tentativas <= 3){

			 pos = 1;
			 DigitarSenha();

			 senhaDigitada[0] = digito1;
			 senhaDigitada[1] = digito2;
			 senhaDigitada[2] = digito3;
			 senhaDigitada[3] = digito4;


			 senhaCorreta = true;

			 for (int i = 0; i < 4; i++) {
				 if (senhaDigitada[i] != senhaAleatoria[i]) {
					 senhaCorreta = false;
					 break;
				 }
			 }

			 if(senhaCorreta){
				 ST7735_FillScreen(DARK_GREEN);
				 ST7735_WriteString(45, 20, "Senha", Font_11x18, WHITE, DARK_GREEN);
				 ST7735_WriteString(35, 50, "correta!", Font_11x18, WHITE, DARK_GREEN);
				 HAL_Delay(3000);
				 InserirAlunos();
				 ControlarPresenca();
				 ControlarSaida();
				 MostrarRelatorio();
				 telaInicial = false;
				 break;
			 }
			 else{
				 ST7735_FillScreen(DARK_GREEN);

				ST7735_WriteString(20, 20, "Senha incorreta!", Font_7x10, WHITE, DARK_GREEN);

				char tentativaStr[20];
				sprintf(tentativaStr, "Tentativa: %d/3", tentativas + 1);
				ST7735_WriteString(25, 50, tentativaStr, Font_7x10, WHITE, DARK_GREEN);

				HAL_Delay(2000);

				tentativas++;

				if (tentativas == 3) {

					quantBloqueios++;

					ST7735_FillScreen(DARK_GREEN);
					ST7735_WriteString(25, 15, "BLOQUEADO!", Font_11x18, WHITE, DARK_GREEN);
					ST7735_WriteString(10, 40, "Aguarde 30 segundos", Font_7x10, WHITE, DARK_GREEN);

					for(int i = 30; i > 0; i--){
						char tempoStr[20];
						sprintf(tempoStr, "Tempo: %ds", i);

						ST7735_FillRectangle(30, 60, 100, 20, DARK_GREEN); // limpa área
						ST7735_WriteString(30, 60, tempoStr, Font_7x10, WHITE, DARK_GREEN);

						HAL_Delay(1000);
					}

					if(quantBloqueios == 3){
				        ST7735_FillScreen(DARK_GREEN);
				        ST7735_WriteString(10, 25, "ACESSO BLOQUEADO", Font_7x10, WHITE, DARK_GREEN);
				        ST7735_WriteString(20, 45, "PERMANENTE", Font_7x10, WHITE, DARK_GREEN);
				        while(1);
					}

					ST7735_FillScreen(DARK_GREEN);
					ST7735_WriteString(15, 25, "Pode tentar", Font_11x18, WHITE, DARK_GREEN);
					ST7735_WriteString(25, 50, "novamente!", Font_11x18, WHITE, DARK_GREEN);

					HAL_Delay(2000);

					tentativas = 0;
				}
				}
		    }

		} else{

			if(telaInicial == false){

			 ST7735_FillScreen(DARK_GREEN);
			 ST7735_WriteString(25, 20, "Clique no", Font_11x18, WHITE, DARK_GREEN);
			 ST7735_WriteString(25, 40, "PA10", Font_11x18, WHITE, DARK_GREEN);

			 telaInicial = true;
			}

		}






    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
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
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
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
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ST7735_CS_GPIO_Port, ST7735_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, ST7735_DC_Pin|ST7735_RES_Pin|ledteste_Pin|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin : ST7735_CS_Pin */
  GPIO_InitStruct.Pin = ST7735_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ST7735_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ST7735_DC_Pin ST7735_RES_Pin ledteste_Pin PB4
                           PB5 PB6 */
  GPIO_InitStruct.Pin = ST7735_DC_Pin|ST7735_RES_Pin|ledteste_Pin|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : botao_saida_Pin botao_inicial_Pin botao_entrada_Pin botao_retorno_Pin */
  GPIO_InitStruct.Pin = botao_saida_Pin|botao_inicial_Pin|botao_entrada_Pin|botao_retorno_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void DigitarSenha(void){

	ST7735_FillScreen(DARK_GREEN);
	ST7735_WriteString(20, 15,"Senha:",Font_11x18,WHITE,DARK_GREEN);

	digito1 = 0;
	digito2 = 0;
	digito3 = 0;
	digito4 = 0;

	MostrarSenha();

	 while(pos <= 4 ){
		 clickSomar = BOTAO_SAIR;
		 clickMudar = BOTAO_ENTRAR;

		 if(clickMudar == 0  ){
			 HAL_Delay(200);
			 pos++;
		 }

		 if(clickSomar == 0 && pos == 1){
			 HAL_Delay(200);
			 digito1 = (digito1 + 1) % 10;
		 }

		 else if(clickSomar == 0 && pos == 2){
			 HAL_Delay(200);
			 digito2 = (digito2 + 1) % 10;
		 }

		 else if(clickSomar == 0 && pos == 3){
			 HAL_Delay(200);
			 digito3 = (digito3 + 1) % 10;
		 }

		 else if(clickSomar == 0 && pos == 4){
			 HAL_Delay(200);
			 digito4 = (digito4 + 1) % 10;
		 }

		 MostrarSenha();
	 }
}

void InserirAlunos(void){

	ST7735_FillScreen(DARK_GREEN);
    ST7735_WriteString(10, 15, "Insira a quantidade", Font_7x10, WHITE, DARK_GREEN);
    ST7735_WriteString(40, 30, "de alunos", Font_7x10, WHITE, DARK_GREEN);
    ST7735_WriteString(10, 50, "PA9 = DEZENA", Font_7x10, WHITE, DARK_GREEN);
    ST7735_WriteString(10, 65, "PA11 = UNIDADE", Font_7x10, WHITE, DARK_GREEN);

	maxAlunos = 0;

	while(1){

		clickConfirmar1 = BOTAO_RETORNAR;
		clickDezena = BOTAO_SAIR;
		clickUnidade = BOTAO_ENTRAR;

		if(clickDezena == 0){
			HAL_Delay(250);
			maxAlunos = maxAlunos + 10;
			MostrarQuantidade();
		}
		if(clickUnidade == 0){
			HAL_Delay(250);
			maxAlunos++;
			MostrarQuantidade();
		}
		if(clickConfirmar1 == 0){
			inicio = HAL_GetTick();
			HAL_Delay(250);
			break;
		}
	}
}

void MostrarQuantidade(void){

    char buffer[10];

    sprintf(buffer, "%d", maxAlunos);
	ST7735_FillScreen(DARK_GREEN);
    ST7735_WriteString(25, 15, "Alunos:", Font_11x18, WHITE, DARK_GREEN);
    ST7735_WriteString(35, 40, buffer, Font_11x18,WHITE,DARK_GREEN);
    ST7735_WriteString(25, 65, "PA12 = CONFIRMAR", Font_7x10, WHITE, DARK_GREEN);

}

void ControlarPresenca(void){

	quantAlunos = 0;

	clickConfirmar2 = BOTAO_SAIR;

	ST7735_FillScreen(DARK_GREEN);
	ST7735_WriteString(10, 10, "Clique no PA10 ", Font_7x10, WHITE, DARK_GREEN);
	ST7735_WriteString(10, 25, "para entrar", Font_7x10, WHITE, DARK_GREEN);
	ST7735_WriteString(10, 45, "Clique no PA9 ", Font_7x10, WHITE, DARK_GREEN);
	ST7735_WriteString(10, 65, "para iniciar", Font_7x10, WHITE, DARK_GREEN);

	AulaAtiva = false;

	while(AulaAtiva == false){

	    clickEntrarAluno = BOTAO_INICIO;
	    clickConfirmar2 = BOTAO_SAIR;

	    if(clickEntrarAluno == 0){
	    	HAL_Delay(200);

	    	if(quantAlunos < maxAlunos){
	    		quantAlunos++;
	    		matricula = 0;
	    		MostrarAluno(matricula);
	    		HAL_Delay(1500);
	    		ST7735_FillScreen(DARK_GREEN);
	    		ST7735_WriteString(10, 10, "Clique no PA10 ", Font_7x10, WHITE, DARK_GREEN);
	    		ST7735_WriteString(10, 25, "para entrar", Font_7x10, WHITE, DARK_GREEN);
	    		ST7735_WriteString(10, 45, "Clique no PA9 ", Font_7x10, WHITE, DARK_GREEN);
	    		ST7735_WriteString(10, 65, "para iniciar", Font_7x10, WHITE, DARK_GREEN);
	    	}

	    	while(BOTAO_RETORNAR == 0);
	    }

	    if(clickConfirmar2 == 0){
	    	HAL_Delay(200);
	    	AulaAtiva = true;
	    	while(BOTAO_SAIR == 0);
	    }

	}
}

void MostrarSenha(void){

    char buffer[10];

    sprintf(buffer, "%d", digito1);
    ST7735_WriteString(20, 50, buffer, Font_11x18, WHITE, DARK_GREEN);

    sprintf(buffer, "%d", digito2);
    ST7735_WriteString(40, 50, buffer, Font_11x18, WHITE, DARK_GREEN);

    sprintf(buffer, "%d", digito3);
    ST7735_WriteString(60, 50, buffer, Font_11x18, WHITE, DARK_GREEN);

    sprintf(buffer, "%d", digito4);
    ST7735_WriteString(80, 50, buffer, Font_11x18, WHITE, DARK_GREEN);
}

void MostrarAluno(int matricula){

	char texto[10];

	ST7735_FillScreen(DARK_GREEN);
	ST7735_WriteString(10, 10, "Bem-vindo!", Font_11x18, WHITE, DARK_GREEN);
	ST7735_WriteString(10, 35, "Matricula:", Font_7x10, WHITE, DARK_GREEN);
	sprintf(texto, "%d", matricula);
    ST7735_WriteString(45, 50, texto, Font_11x18, WHITE, DARK_GREEN);

}

void ControlarSaida(void){

	clickFinalizar1 = BOTAO_INICIO;
	clickFinalizar2 = BOTAO_ENTRAR;
	clickSaiu = BOTAO_SAIR;
	clickVoltou = BOTAO_RETORNAR;

	quantAlunoFora = 0;
	quantSaidas = 0;
	tempoSaida = 0;
	tempoVolta = 0;

	ST7735_FillScreen(DARK_GREEN);
	ST7735_WriteString(5, 10, "PA9 = SAIR", Font_7x10, WHITE, DARK_GREEN);
    ST7735_WriteString(5, 20, "PA12 = ENTRAR", Font_7x10, WHITE, DARK_GREEN);
    ST7735_WriteString(5, 30, "PA10 E PA11 = ACABAR", Font_7x10, WHITE, DARK_GREEN);
	BarraDeCarregamento();

	while(AulaAtiva){

		clickFinalizar1 = BOTAO_INICIO;
		clickFinalizar2 = BOTAO_ENTRAR;
		clickSaiu = BOTAO_SAIR;
		clickVoltou = BOTAO_RETORNAR;

		if(clickSaiu == 0){
			HAL_Delay(200);
			if(quantAlunoFora < 3 && quantAlunoFora < quantAlunos && maxAlunos != 0){
				tempoSaida = HAL_GetTick();
				HAL_Delay(200);
				quantAlunoFora++;
				quantSaidas++;
				MostrarBarraComPresenca();
		    }else if (maxAlunos == 0){
		    	ST7735_WriteString(10, 10, "Nenhum aluno!", Font_7x10, WHITE, DARK_GREEN);
		    	HAL_Delay(2000);
		    	MostrarBarraComPresenca();
		    }else{
			    ST7735_WriteString(5, 10, "Limite maximo!", Font_11x18, WHITE, DARK_GREEN);
		    	HAL_Delay(2000);
		    	MostrarBarraComPresenca();
		    }

		}

		if(clickVoltou == 0){
			HAL_Delay(200);


			if(quantAlunoFora > 0){
				tempoVolta = HAL_GetTick();
				tempoTotalFora += (tempoVolta - tempoSaida);
				quantAlunoFora--;
				MostrarBarraComPresenca();
			}else{
				ST7735_WriteString(10, 10, "Ninguem fora!", Font_11x18, WHITE, DARK_GREEN);
		    	HAL_Delay(2000);
		    	MostrarBarraComPresenca();
			}
		}

		if(clickFinalizar1 == 0 && clickFinalizar2 == 0){
		    HAL_Delay(300);
		    fim = HAL_GetTick();
		    duracao = fim - inicio;

		    if(quantSaidas > 0){
		        mediaTempoFora = tempoTotalFora / quantSaidas;
		    }

		    AulaAtiva = false;
		}
	}

}

void BarraDeCarregamento(void){

    char texto[20];

    larguraMax = 70;
    altura = 15;
    int presentes = quantAlunos;

    if (maxAlunos > 0) {
        larguraAtual = (presentes * larguraMax) / maxAlunos;
    } else {
        larguraAtual = 0;
    }

    ST7735_FillRectangle(5, 55, larguraMax, altura, WHITE);
    ST7735_FillRectangle(5, 55, larguraAtual, altura, BLACK);

    sprintf(texto, "(%d/%d)", presentes, maxAlunos);
    ST7735_WriteString(75, 60, texto, Font_7x10, WHITE, DARK_GREEN);
}

void MostrarRelatorio(void){

    char buffer[30];

    uint32_t mediaSegundos = mediaTempoFora / 1000;


    ST7735_FillScreen(DARK_GREEN);

    ST7735_WriteString(5, 5, "RELATORIO", Font_11x18, WHITE, DARK_GREEN);

    sprintf(buffer, "Presentes: %d", quantAlunos);
    ST7735_WriteString(5, 30, buffer, Font_7x10, WHITE, DARK_GREEN);

    sprintf(buffer, "Saidas: %d", quantSaidas);
    ST7735_WriteString(5, 45, buffer, Font_7x10, WHITE, DARK_GREEN);

    HAL_Delay(5000);
    ST7735_FillScreen(DARK_GREEN);
    ST7735_WriteString(5, 5, "RELATORIO", Font_11x18, WHITE, DARK_GREEN);

    sprintf(buffer, "Media fora: %lu s", mediaSegundos);
    ST7735_WriteString(5, 30, buffer, Font_7x10, WHITE, DARK_GREEN);

    sprintf(buffer, "Tempo total: %lu s", duracao / 1000);
    ST7735_WriteString(5, 45, buffer, Font_7x10, WHITE, DARK_GREEN);
    HAL_Delay(5000);


}

void MostrarBarraComPresenca(void) {

    char dentro[20];
    char fora[20];

    ST7735_FillScreen(DARK_GREEN);

    BarraDeCarregamento();

    sprintf(dentro, "Dentro: %d", quantAlunos - quantAlunoFora);
    sprintf(fora, "Fora: %d", quantAlunoFora);

    ST7735_WriteString(10, 10, dentro, Font_7x10, WHITE, DARK_GREEN);
    ST7735_WriteString(10, 20, fora, Font_7x10, WHITE, DARK_GREEN);
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
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
