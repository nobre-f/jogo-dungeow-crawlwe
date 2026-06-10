# ⚔️ Dungeon Crawler

## 👥 Desenvolvedores
* **Adan Arthur Mathias De Castro Correa De Melo**
* **Davi Fernando Costa Nunes**
* **Fernando Ariel Dias Nobre**

---

## 📜 História do Jogo
A pacata Vila do Vale sempre viveu em perfeita harmonia, até que tremores misteriosos abriram portais para uma masmorra antiga e esquecida nas profundezas da terra. Delas, emergiu o temível **Boss Z** e suas hordas de monstros corrompidos, espalhando armadilhas e bloqueando os caminhos. 

Como o último guardião da vila, sua missão é visitar o Ferreiro local para escolher sua arma de preferência, descer pelos perigosos andares da masmorra, desvendar mecanismos secretos, coletar chaves e derrotar o Boss Z antes que ele destrua o vilarejo por completo. A integridade do reino está em suas mãos!

---

## 🎮 Como Jogar

### **Objetivo Geral**
O jogador começa na Vila (Andar 1). O objetivo é progredir pelos andares (descendo as escadas `L`) até chegar ao Andar 4, onde enfrentará o Boss Final (`Z`). Para vencer o jogo, você deve derrotar o Boss atacando-o até que sua vida chegue a zero. Se você perder suas 3 vidas esbarrando em monstros ou espinhos, o jogo terminará em *Game Over*.

### **Controles**
Os comandos devem ser digitados utilizando as teclas correspondentes no teclado (o jogo responde instantaneamente sem necessidade de apertar Enter):

* **`W`**: Movimenta o jogador para **Cima** / Altera a direção do olhar para cima (`^`).
* **`S`**: Movimenta o jogador para **Baixo** / Altera a direção do olhar para baixo (`V`).
* **`A`**: Movimenta o jogador para a **Esquerda** / Altera a direção do olhar para a esquerda (`<`).
* **`D`**: Movimenta o jogador para a **Direita** / Altera a direção do olhar para a direita (`>`).
* **`I`**: **Interagir** (Falar com o ferreiro, coletar chaves, abrir portas trancadas, ativar botões e descer escadas).
* **`O`**: **Atacar** (Dispara o ataque da arma atualmente equipada).
* **`M`**: Voltar para o Menu Principal.

---

## 🔣 Significado dos Símbolos

| Símbolo | Significado | Comportamento no Jogo |
| :---: | :--- | :--- |
| **`^` `V` `<` `>`** | **Jogador** | Representa você. O símbolo muda indicando para qual direção você está olhando e atacando. |
| **`*`** | **Parede** | Obstáculo intransponível. Bloqueia a movimentação. |
| **`#`** | **Espinhos** | Armadilha. Pisar aqui faz você perder 1 vida e reinicia o andar atual do zero. |
| **`k`** | **Caixa** | Obstáculo destrutível. Pode ser quebrada usando qualquer ataque. |
| **`@`** | **Chave** | Item coletável necessário para abrir as portas trancadas. |
| **`D`** | **Porta Trancada** | Bloqueia o caminho. Consome 1 chave para ser aberta através da interação (`I`). |
| **`=`** | **Porta Aberta** | Caminho livre criado após abrir uma porta trancada. |
| **`O`** | **Botão/Alavanca** | Mecanismo que, ao interagir, abre passagens secretas nas paredes em fases avançadas. |
| **`L`** | **Escada** | Ponto de transição. Interagir aqui faz você avançar para o próximo andar. |
| **`C`** | **Ferreiro** | NPC localizado na Vila. Interagir com ele abre o menu de escolha de armas. |
| **`X`** | **Monstro Aleatório** | Inimigo básico que se move aleatoriamente pelo mapa. Causa dano se encostar em você. |
| **`Y`** | **Monstro Perseguidor** | Inimigo inteligente que caça ativamente a posição do jogador pelo mapa. |
| **`Z`** | **Boss Final** | O grande vilão do jogo. Possui 3 pontos de vida, persegue o jogador e esmaga caixas (`k`) pelo caminho. |

---

## 🤖 Declaração sobre o uso de IA Generativa

Para a realização deste projeto de introdução à programação, foi utilizada a Inteligência Artificial generativa (modelo Gemini da Google) com os seguintes objetivos:

1.Revisionamento do código.
2.Clean Code.
3.Resolução de problemas que não conseguimos resolver usando a lógica.
