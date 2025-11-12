# 🏡 Sistema de Monitoramento de Condições em Home Office

Trabalhar em casa traz comodidade, mas também pode criar **hábitos prejudiciais à saúde** sem que o usuário perceba. Este projeto propõe um sistema inteligente capaz de **monitorar o ambiente e o comportamento postural**, emitindo **alertas preventivos** para promover bem-estar durante longos períodos de trabalho no computador.

---

## 🎯 Problema

Com a expansão do **home office**, milhares de pessoas passaram a trabalhar longas jornadas em casa, sem acompanhamento ergonômico ou controle ambiental. Isso gera riscos como:

- Permanecer **sentado por horas**, reduzindo o fluxo sanguíneo e aumentando dores e fadiga.
- Trabalhar em ambientes com **má ventilação, temperatura inadequada** ou **umidade baixa**, o que afeta o conforto respiratório e a concentração.
- Falta de **consciência sobre o tempo**, levando a jornadas pouco saudáveis.

Estudos mostram que **ficar sentado por longos períodos** está diretamente relacionado a:
- Problemas posturais e dores nas costas
- Redução da oxigenação e foco
- Maior risco de doenças cardiovasculares

Em muitos casos, o problema acontece **sem que a pessoa se dê conta**.  
A rotina “silenciosamente prejudicial” é o que torna esse cenário perigoso.

---

## ✅ Solução Proposta

Criamos um sistema embarcado com o **ESP32** que:
- **Monitora continuamente**:
  - Temperatura e umidade (DHT22)
  - Luminosidade do ambiente (LDR)
  - Tempo ininterrupto sentado (lógica interna + botão de reset)
- **Detecta situações prejudiciais**, como:
  - Ambiente muito quente
  - Ar excessivamente seco
  - Permanência prolongada sentado
- **Gera alertas automáticos**:
  - Mensagens explicativas enviadas via **MQTT**
  - Sinal sonoro através de **buzzer**

### Por que isso importa?

Em vez de exigir disciplina do usuário, o sistema **age como um lembrete inteligente**, incentivando pausas, hidratação e ajustes no ambiente.  
Ele transforma uma rotina invisível em algo percebido e **controlável**.

---

## 🧱 Componentes Utilizados

| Componente | Quantidade | Função |
|-----------|-----------|--------|
| ESP32 | 1 | Processamento + Wi-Fi |
| DHT22 | 1 | Temperatura e umidade |
| LDR | 1 | Luminosidade |
| Buzzer | 1 | Alerta sonoro |
| Push Button | 1 | Reset do tempo sentado |

---

## 🔌 Esquema do Circuito

<img width="723" height="841" alt="image" src="https://github.com/user-attachments/assets/5f809240-cb7d-4a93-98be-1c81fced1549" />

## 🔌 Fluxo node-red

<img width="511" height="322" alt="image" src="https://github.com/user-attachments/assets/55add54d-8006-49ce-a669-e681ec5161da" />

## 🔌 Dashboards

<img width="489" height="460" alt="image" src="https://github.com/user-attachments/assets/1272fe2b-ca22-4cd8-bfcd-4cb5d642c22c" />

---

## 🌐 Link do Wokwi (Simulação)

🔗 https://wokwi.com/projects/447384586090823681

---
🚀 Passo a Passo para Execução

1️⃣ Iniciar o Node-RED

Abra o Node-RED no seu computador.

Caso ainda não tenha, instale via terminal:

npm install -g node-red


Execute o Node-RED:

node-red


Acesse o editor no navegador:
http://localhost:1880

2️⃣ Importar o Fluxo do Projeto

No editor do Node-RED, clique em Menu (☰) → Import → Clipboard.

Cole o código JSON do fluxo fornecido neste projeto.

Clique em Importar.

Verifique se os nós estão conectados corretamente ao broker MQTT.

Clique em Deploy (canto superior direito).

3️⃣ Executar o Projeto no Wokwi

Acesse o link do projeto Wokwi:

 https://wokwi.com/projects/447384586090823681

Faça login (opcional, mas recomendado).

Clique em ▶️ Start Simulation.

O ESP32 se conectará ao Wi-Fi virtual e ao broker MQTT.

Observe as mensagens sendo enviadas para o Node-RED.

4️⃣ Visualizar o Dashboard

No Node-RED, acesse o painel do dashboard

Veja em tempo real os gráficos e valores de temperatura e umidade.

Se quiser, adicione indicadores, gráficos lineares e gauge para melhor visualização.

---

## 🧩 Comunicação MQTT

O sistema publica os dados no tópico:

pfc/sedentario_luz

### Formato da mensagem (JSON)

```json
{
  "temperatura": 28.4,
  "umidade": 41.2,
  "tempo_sentado_s": 190.5,
  "luminosidade_raw": 2300,
  "alerta_sentado": "Tempo sentado excessivo! Levante-se e movimente-se!",
  "alerta_temperatura": "",
  "alerta_umidade": "Umidade baixa! O ar pode estar ressecado."
}
Broker utilizado
Broker: broker.emqx.io
Porta: 1883

⚙️ Dependências

Biblioteca	Função
DHT Sensor Library	Leitura do DHT22
PubSubClient	Envio MQTT
WiFi.h	Conexão Wi-Fi do ESP32

Instaláveis pelo Gerenciador de Bibliotecas do Arduino IDE.

▶️ Modo de Uso
Carregue o código no ESP32 ou execute no Wokwi.

Abra um cliente MQTT (ex: MQTT Explorer).

Conecte ao broker: broker.emqx.io:1883.

Assine o tópico: pfc/sedentario_luz.

Observe as condições e alertas em tempo real.

Ao levantar para pausa, pressione o botão para resetar o tempo sentado.

📜 Licença
Projeto disponível para fins acadêmicos, educacionais e de pesquisa.
