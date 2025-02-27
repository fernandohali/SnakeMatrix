# SnakeMatrix - Jogo da Cobrinha com Raspberry Pi Pico e Matriz de LEDs

## Descrição
SnakeMatrix é um jogo inspirado no clássico "Jogo da Cobrinha", desenvolvido para rodar no Raspberry Pi Pico. Ele utiliza uma matriz de LEDs WS2812 para exibir o jogo e um joystick analógico para controle dos movimentos. A pontuação é exibida em um display OLED SSD1306.

## Funcionalidades
- Controle da cobra com joystick.
- Crescimento da cobra ao comer comida.
- Reinício do jogo ao colidir com as bordas ou com o próprio corpo.
- Exibição da pontuação no display OLED.

## Hardware Utilizado
- Raspberry Pi Pico
- Módulo WS2812 (Matriz de LEDs RGB)
- Joystick analógico
- Display OLED SSD1306
- Botões adicionais para interações

## Dependências
Este projeto utiliza as seguintes bibliotecas:
- `pico/stdlib.h`
- `hardware/pio.h`
- `hardware/i2c.h`
- `ws2812.pio.h`
- `ssd1306.h`
- `joystick.h`
- `snake.h`
- `matriz.h`
- `buttons.h`

## Como Compilar e Executar
1. Clone este repositório:
   ```sh
   git clone https://github.com/seu-usuario/SnakeMatrix.git
   cd SnakeMatrix
   ```

2. Configure o ambiente de desenvolvimento para Raspberry Pi Pico (SDK do Pico).
3. Compile o projeto utilizando CMake:
   ```sh
   mkdir build
   cd build
   cmake ..
   make
   ```
4. Carregue o firmware no Raspberry Pi Pico e inicie a execução.

## Estrutura do Código
```
SnakeMatrix/
├── src/
│   ├── SnakeMatrix.c  # Lógica principal do jogo
│   ├── snake/
│   │   ├── snake.c  # Movimentação e colisão
│   │   ├── snake.h
│   ├── matriz/
│   │   ├── matriz.c  # Controle da matriz de LEDs
│   │   ├── matriz.h
│   ├── display/
│   │   ├── display.c  # Exibição no display OLED
│   │   ├── display.h
│   ├── buttons/
│   │   ├── buttons.c  # Apenas para abrir o bootsel
│   │   ├── buttons.h
│   ├── joystick/
│   │   ├── joystick.c  # Leitura do joystick
│   │   ├── joystick.h
│
├── inc/
│   ├── ssd1306.h  # Biblioteca do display OLED
│   ├── font.h  # Fonte para o display
│
├── ws2812.pio.h  # Controlador da matriz de LEDs
├── CMakeLists.txt  # Configuração do build
├── README.md  # Documentação do projeto
```

## Como Jogar
- Use o joystick para mover a cobra:
  - Cima
  - Baixo
  - Esquerda
  - Direita
- Coma a comida para crescer e aumentar a pontuação.
- O jogo reinicia caso a cobra colida com as bordas ou consigo mesma.

## Melhorias Futuras
- Adicionar modos de jogo (ex.: modo infinito, modo desafio)
- Implementar efeitos visuais nos LEDs para tornar o jogo mais dinâmico
- Criar uma interface web para exibição de estatísticas

## Autor
Desenvolvido por Fernando Hali Santos Andrade.

