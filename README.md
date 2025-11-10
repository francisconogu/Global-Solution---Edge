# 🏡 Sistema de Monitoramento de Condições em Home Office

Este projeto tem como objetivo auxiliar trabalhadores em **home office** a manterem um ambiente saudável e promoverem pausas durante o trabalho.  
O sistema realiza **monitoramento contínuo** de temperatura, umidade, luminosidade e tempo sentado, enviando os dados via **MQTT** para acompanhamento em dashboards IoT.

---

## 🎯 Problema

Muitas pessoas que trabalham remotamente passam longos períodos sentadas, em ambientes mal iluminados e com condições ambientais inadequadas. Isso pode causar:

- Desconforto físico e fadiga
- Ar ressecado e irritação respiratória
- Risco de estresse térmico
- Dores musculares e má postura

Além disso, muitas vezes o usuário **não percebe** quanto tempo já está na mesma posição.

---

## ✅ Solução Proposta

O sistema monitora em tempo real:

| Variável | Sensor | Finalidade |
|---------|--------|-----------|
| Temperatura e Umidade | DHT22 | Avaliar conforto térmico |
| Luminosidade | LDR | Verificar condição de iluminação |
| Tempo sentado | Lógica interna + botão de reset | Promover pausas e ergonomia |

Quando valores ultrapassam limites saudáveis, o sistema:

- Envia alertas via **MQTT**
- Ativa um **buzzer**
- Exibe mensagens de aviso no console

Isso estimula o usuário a **levantar, hidratar-se, ajustar luz, ventilar o ambiente**, etc.

---

## 🧱 Componentes Utilizados

| Componente | Quantidade | Função |
|-----------|-----------|--------|
| ESP32 DevKit | 1 | Processamento + Wi-Fi |
| Sensor DHT22 | 1 | Temperatura e Umidade |
| LDR + Resistor | 1 par | Sensor de luminosidade |
| Buzzer | 1 | Sinal sonoro de alerta |
| Push Button | 1 | Reset do tempo sentado |

---

## 🔌 Esquema do Circuito

> **Substitua pela imagem do seu projeto no Wokwi**

**Imagem do circuito:**  
![Circuito](colocar_link_da_imagem_aqui)

---

## 🌐 Link do Wokwi (Simulação)

> Colar aqui o link após publicar:

🔗 https://wokwi.com/projects/SEU_PROJETO_AQUI

---

## 🧩 Tópicos MQTT Utilizados

O sistema utiliza o broker público **test.mosquitto.org**, sem autenticação, usando o tópico:

pfc/sedentario_luz

pgsql
Copiar código

### Formato da mensagem enviada (JSON)

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

⚙️ Dependências
Biblioteca	Função	Instalação
DHT Sensor Library	Leitura do DHT22	Arduino IDE > Gerenciador de Bibliotecas
PubSubClient	Comunicação MQTT	Arduino IDE > Gerenciador de Bibliotecas
WiFi.h (nativa do ESP32)	Conexão Wi-Fi	Já incluída

▶️ Como Utilizar
Abra o projeto no Wokwi ou carregue no ESP32 real.

Conecte o ESP32 ao Wi-Fi configurado no código.

Abra um cliente MQTT e conecte ao broker:

Broker: test.mosquitto.org
Porta: 1883
Tópico: pfc/sedentario_luz
Observe os dados em tempo real.

Caso permaneça muito tempo sentado, o buzzer irá tocar.

Pressione o botão para resetar o tempo sentado.

📜 Licença
Este projeto pode ser utilizado para fins educacionais e de pesquisa.

