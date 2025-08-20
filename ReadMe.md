# 📡 Guia de Conexão e Pinagem GPS com Arduino

Este guia detalhado oferece um passo a passo completo para configurar seu projeto de GPS com Arduino, abordando **duas situações principais**:  
- Conexão com um **módulo GPS físico**  
- Simulação de dados de localização **sem hardware**

---

## 🛰️ Cenário 1: Com Módulo GPS Físico

Use este método quando desejar obter **dados reais de localização** com um módulo GPS **U-blox**.

### 🔧 1. Componentes Necessários
- Placa Arduino compatível (**ESP32** ou **ESP8266** são ideais).  
- Módulo GPS: **U-blox NEO-6M, NEO-7M ou NEO-8M**.  
- Antena GPS: **U-blox ANN-MS-0-005**.  
- Cabos de conexão (jumpers).  

### 🔌 2. Pinagem e Conexões
A comunicação é feita por **UART (Serial)**.  
⚠️ **Atenção**: sempre conectar **TX → RX** e **RX → TX**.

| Pino do Módulo GPS | Função        | Conectar ao Arduino   |
|--------------------|---------------|-----------------------|
| VCC                | Energia       | 5V ou 3.3V (verifique no módulo) |
| GND                | Terra         | GND                   |
| TX                 | Transmissão   | RX do Arduino         |
| RX                 | Recepção      | TX do Arduino         |

📌 Exemplo no **ESP32**:
- **TX do GPS → GPIO 16 (RX2)** do ESP32  
- **RX do GPS → GPIO 17 (TX2)** do ESP32  

### ▶️ 3. Procedimento Passo a Passo
1. **Faça as Conexões** conforme a tabela.  
2. **Instale a Biblioteca**: na IDE do Arduino → Gerenciar Bibliotecas → instale `TinyGPSPlus`.  
3. **Carregue o Código** que lê dados do GPS.  
4. **Leve ao ar livre** para captar sinal dos satélites (primeiro *fix* pode demorar alguns minutos).  
5. **Abra o Monitor Serial** (115200 baud) → veja latitude e longitude aparecendo.  

---

## 💻 Cenário 2: Sem Módulo GPS (Simulação)

Use este método para **testar a lógica de envio MQTT** sem depender de um GPS físico.

### 🔧 1. Componentes Necessários
- Placa Arduino compatível (**ESP32** ou **ESP8266**).  
- Conexão **Wi-Fi**.  

### 🔌 2. Pinagem e Conexões
Nenhuma conexão extra é necessária.  
A placa será ligada apenas à **energia/USB**.  

### ▶️ 3. Procedimento Passo a Passo
1. **Configure o Código**: use variáveis com latitude e longitude **fixas ou aleatórias**.  
2. **Ajuste os Dados**: altere os valores no código para simular diferentes locais.  
3. **Carregue o Código** na placa.  
4. **Monitore no Serial**: veja as mensagens confirmando envio dos dados para o **broker Maquiatto**.  

---

## ✅ Benefícios
- **Com módulo GPS** → Dados reais de localização.  
- **Sem módulo GPS** → Testes rápidos de lógica, JSON e envio MQTT sem depender de satélites.  

---
