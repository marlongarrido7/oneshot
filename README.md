# **Temporizador de Um Disparo (One Shot) utilizando o Raspberry Pi Pico W 2040**

## **Autor do Projeto**  
Dr. Marlon da Silva Garrido  
Professor Associado IV (CENAMB - PPGEA)  
Universidade Federal do Vale do São Francisco (UNIVASF)  

Este projeto faz parte das atividades do **EMBARCATECH 2024/25**.  

---

## **Índice**  

1. [Objetivos](#objetivos)  
2. [Descrição do Projeto](#descrição-do-projeto)  
3. [Funcionalidades](#funcionalidades)  
4. [Requisitos do Projeto](#requisitos-do-projeto)  
5. [Diagrama Simplificado de Conexões](#diagrama-simplificado-de-conexões)  
6. [Como Executar o Projeto](#como-executar-o-projeto)  
7. [Estrutura do Código](#estrutura-do-código)  
8. [Trecho de Código](#trecho-de-código)  
9. [Explicação do Código](#explicação-do-código)  
10. [Referências](#referências)  
11. [Demonstração em Vídeo](#demonstração-em-vídeo)  
12. [Contato](#contato)  

---

## **Objetivos**  

- Implementar um sistema de temporização utilizando a função `add_alarm_in_ms()` do **Pico SDK**.  
- Controlar o acionamento de LEDs por meio de um **botão (pushbutton)**.  
- Criar uma lógica onde o **botão só pode ser acionado quando o último LED for desligado**.  
- Aplicar um atraso de **3 segundos** entre as transições de estado dos LEDs.  
- Implementar **interrupções no botão** para detectar seu acionamento.  
- Exibir informações no terminal serial para monitoramento.  
- Realizar testes na **ferramenta educacional BitDogLab**.  
- (Opcional) Implementar uma lógica de **debounce** para evitar o efeito **bouncing** no botão.  

---

## **Descrição do Projeto**  

Este projeto utiliza um **Raspberry Pi Pico W** para controlar três LEDs (azul, vermelho e verde) acionados por um botão **pushbutton**.  

### **Funcionamento do Sistema**  
1. **O botão é pressionado**.  
2. **Todos os LEDs acendem simultaneamente**.  
3. **Após 3 segundos**, um LED se apaga.  
4. **Após mais 3 segundos**, um segundo LED se apaga.  
5. **Após mais 3 segundos**, o último LED se apaga.  
6. **O sistema fica pronto para um novo acionamento do botão**.  

A função `add_alarm_in_ms()` é utilizada para programar os tempos de atraso na transição dos LEDs. Durante a execução do ciclo de temporização, o botão **não pode ser acionado novamente**, garantindo que a sequência seja concluída antes de um novo disparo.  

---

## **Funcionalidades**  

- **Temporização programada**: Utiliza `add_alarm_in_ms()` para alternar os LEDs com um atraso de **3 segundos**.  
- **Controle dos LEDs**: Inicializa três LEDs (azul, vermelho e verde) e alterna entre eles automaticamente.  
- **Detecção de botão (Pushbutton)**: Usa interrupção (`GPIO_IRQ_EDGE_FALL`) para iniciar a sequência.  
- **Prevenção de múltiplos acionamentos**: O botão só funciona **depois que todos os LEDs forem apagados**.  
- **Mensagens no Terminal Serial**: Exibe logs a cada segundo para indicar o estado do sistema.  
- **Suporte à simulação no BitDogLab**: Possível testar o código usando um LED RGB e um botão conectado aos GPIOs 11, 12, 13 e 5.  

---

## **Requisitos do Projeto**  

- O botão deve acionar os LEDs apenas quando **todos estiverem apagados**.  
- Durante o ciclo de acionamento dos LEDs, **o botão não pode ser pressionado novamente**.  
- A transição dos LEDs deve ser controlada por **funções de callback do temporizador**.  
- Implementação opcional de **debounce** para evitar múltiplos acionamentos indevidos.  
- Testes utilizando a **ferramenta BitDogLab**.  

---

## **Diagrama Simplificado de Conexões**  

```
       Raspberry Pi Pico W
    +---------------------------+
    |                           |
    |  GPIO 13 -> LED Azul      |
    |  GPIO 12 -> LED Vermelho  |
    |  GPIO 11 -> LED Verde     |
    |  GPIO  5 -> Pushbutton    |
    +---------------------------+
```

Caso esteja utilizando a ferramenta **BitDogLab**, conectar o **LED RGB** nos **GPIOs 11, 12 e 13** e o **botão no GPIO 5**.  

---

## **Como Executar o Projeto**  

1. **Clonar o repositório**:  

```sh
git clone https://github.com/seu-usuario/one-shot-timer.git
cd one-shot-timer
```

2. **Configurar o ambiente de desenvolvimento** com o **Raspberry Pi Pico SDK**.  

3. **Compilar o projeto**:  

```sh
mkdir build
cd build
cmake ..
make
```

4. **Transferir o arquivo `.uf2`** para o **Raspberry Pi Pico W**.  

5. **Abrir o terminal serial** para visualizar as mensagens:  

```sh
screen /dev/ttyUSB0 115200
```

No Windows, utilizar **PuTTY** ou **Thonny** para monitoramento.  

---

## **Demonstração em Vídeo**  

- Explicação e demonstração do funcionamento do temporizador:  
  [https://youtu.be/O_SgAEHmI54](https://youtu.be/O_SgAEHmI54)  

---

## **Contato**  

Se este projeto foi útil para você, **não se esqueça de dar uma estrela no GitHub**!  

📧 **Email:** marlon.garrido@univasf.edu.br  
🌐 **Site:** [Universidade Federal do Vale do São Francisco (UNIVASF)](https://www.univasf.edu.br/)  

---

