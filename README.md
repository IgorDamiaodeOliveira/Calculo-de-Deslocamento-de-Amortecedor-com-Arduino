# Cálculo de Deslocamento de Amortecedor com Arduino

Este projeto é um sistema de medição e cálculo em tempo real para determinar o deslocamento de um amortecedor em um mecanismo de suspensão. Utilizando um sensor de ângulo (potenciômetro, por exemplo) conectado a um Arduino, o código aplica a **Lei dos Cossenos** para traduzir a variação angular em uma mudança no comprimento do amortecedor.

## Funcionalidades

- **Cálculo Geométrico**: O script utiliza a Lei dos Cossenos para calcular o comprimento atual do amortecedor com base em três parâmetros geométricos fixos e no ângulo medido.
  $$c^2 = a^2 + b^2 - 2ab \cos(C)$$
  No nosso caso:
  $$\text{novo\_comprimento}^2 = \text{comprimento\_base}^2 + \text{distância\_vertical}^2 - 2 \cdot \text{comprimento\_base} \cdot \text{distância\_vertical} \cdot \cos(\text{ângulo\_calculado})$$
- **Interface Serial Interativa**: O código solicita ao usuário, via monitor serial, os parâmetros essenciais do sistema mecânico (**comprimento inicial do amortecedor**, **distância da base** e **distância vertical**).
- **Medição em Tempo Real**: Após a configuração, o Arduino lê continuamente a entrada analógica de um sensor, converte-a para um ângulo e exibe o deslocamento do amortecedor no monitor serial a cada 100 milissegundos.
- **Leitura de Sensor Analógico**: O código é otimizado para ler um valor de 0 a 1023 (típico para entradas analógicas do Arduino) e mapeá-lo para um intervalo angular de 0° a 180°.

## Requisitos de Hardware

- Placa Arduino (Uno, Nano, etc.)
- Um sensor de ângulo analógico, como um potenciômetro ou um sensor de posição rotativa, conectado ao pino **A0**.
- Os componentes mecânicos cuja geometria será analisada (o sistema de suspensão real).

## Como Usar

1.  **Conecte o Hardware**: Conecte o sensor de ângulo analógico ao pino **A0** do seu Arduino. Certifique-se de que a leitura do sensor mude de 0 para 1023 conforme o ângulo varia.
2.  **Carregue o Código**: Carregue o código para a sua placa Arduino usando a IDE do Arduino.
3.  **Insira os Parâmetros**: Abra o **Monitor Serial** na IDE do Arduino. O programa solicitará que você insira os três parâmetros geométricos, um por um.
4.  **Visualize os Dados**: Após inserir todos os parâmetros, o monitor serial começará a exibir em tempo real o ângulo medido, o comprimento atual e o deslocamento do amortecedor.

