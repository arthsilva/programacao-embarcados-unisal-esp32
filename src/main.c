// 1o - Bibliotecas de referencia para o desenvolvimento do codigo

// Adicionando referencias para chamadas da biliboteca C (printf/scanf)
#include <stdio.h>
// Adicionando referencias para as configuracoes da SDK
#include "sdkconfig.h"
// Adicionando recursos do FreeRTOS para gerenciamento de tarefas (usaremos para delay)
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
// Adicionando recursos para referencia de informacoes do sistema esp32
#include "esp_system.h"
// Adicionando recursos para visualizar informacoes da Flash (SPI)
#include "esp_spi_flash.h"
// Adicionando recursos para manipular os sinais de entrada e saida (GPIO)
#include "driver/gpio.h"

// 2o - Defines para referencia de dados a serem usados no programa
// Entenda o define como "apelido" - define apelido original
#define LED_PLACA   GPIO_NUM_2

// 3o - Variaveis globais (evitem se possivel, mas usem com cuidado)
// uint32_t = unsigned int 32 bits - variavel inteira, sem sinal, com dimensao de 32 bits
uint32_t contador = 0;

// 4o - Prototipos de funcoes presentes no codigo (quando nao usado .h a parte)

// 5o - Implementacao dos metodos e tarefas
void app_main(void) {
    // Exibe a mensagem no terminal
    printf("Inicializando Esquenta ESP32... \n");

    //Obtemos informacoes do nosso chip:
    // Criamos um tipo para armazenar as informacoes
    esp_chip_info_t chip_info;
    // Carregamos as informacoes
    esp_chip_info(&chip_info);

    printf("ESP32 - %s com %d CPU Cores, WiFi %s%s \n",
            CONFIG_IDF_TARGET,
            chip_info.cores,
            (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
            (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : ""
    );

    printf("Revisao de Silicio: %d \n", chip_info.revision);

    printf("%d MB de Flash %s \n", 
            (spi_flash_get_chip_size() / (1024*1024)),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embarcada" : "externa"
    );

    // Vamos configurar o uso do LED (GPIO 2)
    gpio_reset_pin(LED_PLACA);
    gpio_set_direction(LED_PLACA, GPIO_MODE_OUTPUT);

    // Tudo que foi feito ate aqui sera executado uma unica vez quando o microcontrolador iniciar

    // Laco de execucao continua - ficara em execucao ate expressamente usarmos break, ou o chip desligar
    while(1) {
        printf("Contador: %d \n", contador);
        // desliga led?
        printf("Ligando o LED... \n");
        gpio_set_level(LED_PLACA, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS); // espera 1000ms = 1s
        //liga led?
        printf("Desligando o LED... \n");
        gpio_set_level(LED_PLACA, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        contador++; // incrementa o contador a cada.... 2 segundos!
    }

}