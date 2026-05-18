# 📚 Sistema Embarcado de Controle de Presença

Sistema embarcado desenvolvido com STM32 para controle de presença em sala de aula, utilizando autenticação por senha, gerenciamento de entradas e saídas e interface gráfica em display.

---

## 👩‍💻 Integrantes

Mariana Ferreira da Silva
Tuany Silva Pereira

## 🎓 Turma

34DS

## 🎯 Objetivo

Desenvolver um sistema embarcado interativo para controle de presença em sala de aula utilizando STM32, botoeiras e display gráfico.

O sistema simula um ambiente real, permitindo:

* Controle de entrada de alunos
* Gerenciamento de saídas temporárias
* Monitoramento em tempo real
* Geração de relatório final

## ⚙️ Tecnologias Utilizadas

* STM32 → Controle principal do sistema
* Linguagem C → Programação embarcada
* ST7735 → Interface gráfica
* GPIO → Leitura dos botões
* SPI → Comunicação com o display

## 🔐 Sistema de Autenticação

O sistema utiliza uma senha numérica aleatória de 4 dígitos.

### Entrada da senha

* 🔘 Botão para incrementar o dígito
* 🔘 Botão para avançar a posição

### Regras de segurança

* Máximo de 3 tentativas
* Após erro: bloqueio temporário de 30 segundos
* Após 3 bloqueios: 🚫 bloqueio permanente


## 👥 Configuração da Turma

O professor define a quantidade máxima de alunos utilizando os botões da placa.

### Ajustes disponíveis

* ➕ Incremento da dezena
* ➕ Incremento da unidade

Após a configuração:

* ✅ O valor deve ser confirmado
* 📺 O total é exibido no display


## 📋 Controle de Presença

O registro de entrada é realizado através de um botão.

O sistema faz uma simulação de leitura de matrícula, representando um leitor facial por meio de variáveis internas do código.

### Regras

* ✔️ Incrementa a quantidade de alunos presentes
* ❌ Não permite ultrapassar o limite máximo definido


## 🚪 Controle de Saída

O sistema permite controlar alunos temporariamente fora da sala.

### Botões utilizados

* 🔘 Botão de saída
* 🔘 Botão de retorno

### Regras

* Máximo de 3 alunos fora simultaneamente
* O sistema bloqueia:

  * excesso de saídas
  * retornos inválidos


## 🖥️ Interface Gráfica

Durante a execução do sistema, o display apresenta:

* 📊 Barra de presença
* 👥 Quantidade de alunos dentro e fora da sala
* ⚠️ Mensagens do sistema
* 🔐 Informações de autenticação


## 📄 Relatório Final

Ao encerrar a aula, o sistema exibe um relatório contendo:

* Total de alunos
* Quantidade de saídas
* Tempo médio fora da sala
* Tempo total da aula


## ⏱️ Funcionalidades Extras (BÔNUS)

* ✔️ Tempo total da aula
* ✔️ Tempo médio fora da sala
* ✔️ Sistema de bloqueio por tentativas


## 🧠 Estrutura do Código

```c
DigitarSenha();              // Entrada da senha
InserirAlunos();             // Configuração inicial
ControlarPresenca();         // Registro de entrada
ControlarSaida();            // Controle de saída e retorno
MostrarBarraComPresenca();   // Interface gráfica
MostrarRelatorio();          // Relatório final
```

---

## 🏁 Encerramento da Aula

A aula é finalizada ao pressionar dois botões simultaneamente.

Após o encerramento, o sistema gera automaticamente o relatório final.

---

## 🚀 Considerações Finais

O projeto atende aos requisitos propostos e simula de forma eficiente um sistema real de controle de presença em sala de aula.

A implementação das funcionalidades bônus tornou o sistema mais completo e próximo de aplicações reais de sistemas embarcados.

---

## 🎥 Vídeo de Apresentação

📌[Clique para assistir](https://www.youtube.com/watch?v=OtP16_d4_kA)
