#include <stdio.h>
#include <stdlib.h>
#include <conio.h>    // Permite usar a funcao _getch() para ler o teclado na hora
#include <windows.h>  // Permite usar comandos do sistema como 'cls' (limpar tela)
#include <time.h>     // Permite usar o relogio para gerar numeros aleatorios

int main()
{
    // Configura a semente dos numeros aleatorios baseando-se no relogio do PC.
    // Isso garante que os monstros se movam de forma diferente em cada partida.
    srand(time(NULL));
    
    // ========================================================================
    // DECLARACAO DE VARIAVEIS (Todas no topo, organizadas por categoria)
    // ========================================================================
    
    // Variaveis de Controle dos Menus e Fluxo do Jogo
    int menuLoop = 1;          // Mantem o laco do Menu Principal rodando
    int opcao;                 // Guarda a escolha digitada no menu (1, 2 ou 3)
    char tecla;                // Guarda a tecla (W, A, S, D, etc.) que o jogador apertou
    int jogando = 1;           // Controla se a partida esta ativa (1 = Sim, 0 = Nao)
    int fase = 1;              // Indica o andar atual: 1=Vila, 2=Andar 1, 3=Andar 2, 4=Andar 3
    int precisaRecarregar = 0; // Se for 1, o jogo apaga o mapa e redesenha o cenario do zero
    
    // Variaveis de Configuração da Matriz (Mapa)
    char mapa[25][25];         // A matriz que guarda os caracteres do mapa do jogo
    int linhas = 10;           // Altura maxima do mapa atual
    int colunas = 10;          // Largura maxima do mapa atual
    int l;                     // Variavel contadora usada nos lacos 'for' das Linhas
    int c;                     // Variavel contadora usada nos lacos 'for' das Colunas
    
    // Variaveis de Atributos do Jogador
    int playerX = 5;           // Linha atual onde o jogador esta na matriz
    int playerY = 5;           // Coluna atual onde o jogador esta na matriz
    char dirAtual = '^';       // Seta que representa o visual do jogador e para onde ele olha
    int vidas = 3;             // Quantidade de vidas do heroi
    int chaves = 0;            // Quantidade de chaves que o jogador esta carregando
    int armaEquipada = 0;      // Codigo da arma: 0=Nenhuma, 1=Espada, 2=Arco, 3=Cajado
    int escolhaArma;           // Guarda a opcao digitada no menu do ferreiro
    char proxima;              // Guarda temporariamente o caractere da celula para onde queremos andar
    
    // Variaveis de Interacao (Tecla I)
    int alvoX;                 // Armazena a linha do quadrado que esta na frente do jogador
    int alvoY;                 // Armazena a coluna do quadrado que esta na frente do jogador
    
    // Variaveis de Combate e Ataque (Tecla O)
    int linha;                 // Controladora de loop para vasculhar linhas atingidas por ataques
    int coluna;                // Controladora de loop para vasculhar colunas atingidas por ataques
    int linhaInicio;           // Inicio do retangulo de dano da Espada
    int linhaFim;              // Fim do retangulo de dano da Espada
    int colunaInicio;          // Inicio do retangulo de dano da Espada
    int colunaFim;             // Fim do retangulo de dano da Espada
    int l_ataque;              // Guarda a linha exata atingida pelo disparo do Arco
    int c_ataque;              // Guarda a coluna exata atingida pelo disparo do Arco
    int alcance;               // Contador de distancia para o percurso da flecha do Arco
    int l_atq;                 // Controladora de loop para a linha da explosao do Cajado
    int c_atq;                 // Controladora de loop para a coluna da explosao do Cajado
    
    // Variaveis dos Monstros e Inimigos
    int monstroX_l = 0;        // Linha onde esta o Monstro X (Movimento Aleatorio)
    int monstroX_c = 0;        // Coluna onde esta o Monstro X (Movimento Aleatorio)
    int monstroX_vivo = 0;     // Estado do Monstro X (1 = Vivo, 0 = Morto)
    
    int monstroY_l = 0;        // Linha onde esta o Monstro Y (Perseguidor)
    int monstroY_c = 0;        // Coluna onde esta o Monstro Y (Perseguidor)
    int monstroY_vivo = 0;     // Estado do Monstro Y (1 = Vivo, 0 = Morto)
    
    int bossZ_l = 0;           // Linha onde esta o Boss Z
    int bossZ_c = 0;           // Coluna onde esta o Boss Z
    int bossZ_vivo = 0;        // Estado do Boss Z (1 = Vivo, 0 = Morto)
    int bossZ_hp = 3;          // Quantidade de vida (pontos de impacto) do Boss Z
    
    // Variaveis da Inteligencia Artificial (IA)
    int direcaoX;              // Guarda o numero sorteado de 0 a 3 para a direcao do Monstro X
    int novaL;                 // Guarda a nova linha pretendida por um monstro antes de ele dar o passo
    int novaC;                 // Guarda a nova coluna pretendida por um monstro antes de ele dar o passo

    // ========================================================================
    // LACO PRINCIPAL DO MENU
    // ========================================================================
    while(menuLoop != 0)
    {
        printf("\n\n----- DUNGEON CRAWLER -----\n\n");
        printf("1) TUTORIAL\n\n");
        printf("2) JOGAR\n\n");
        printf("3) SAIR\n\n");
        printf("Escolha uma opcao: ");
        
        // Se o scanf falhar (retornar 0 porque o usuario digitou uma letra), mudamos a opcao para 0 
        // de forma que caia diretamente no 'default' do switch case.
        if (scanf("%d", &opcao) != 1) 
        {
            opcao = 0; 
        }
        
        // LIMPEZA DO BUFFER: Esse pequeno laco captura caracteres residuais (como letras ou o ENTER)
        // e limpa a memoria do teclado, evitando que o menu entre em loop infinito.
        while (getchar() != '\n'); 

        // Substituicao dos IFs pelo SWITCH CASE pedido
        switch (opcao)
        {
            // --- CASO 1: EXIBICAO DO TUTORIAL ---
            case 1:
                system("cls"); // Limpa a tela antes de mostrar o texto
                printf("--- TUTORIAL DO JOGO ---\n\n");
                printf("O vilarejo foi invadido! Voce deve descer a masmorra e derrotar o Boss Z!\n\n");
                printf("SIGNIFICADO DOS SIMBOLOS:\n");
                printf(" ^, V, <, > : O seu personagem (aponta para onde voce esta olhando)\n");
                printf(" * : Parede solida (nao da para atravessar)\n");
                printf(" # : Espinhos no chao (voce perde 1 vida e reinicia o andar atual)\n");
                printf(" k : Caixa de madeira destruivel (bata nela para quebrar)\n");
                printf(" @ : Chave jogada no chao\n");
                printf(" D : Porta trancada (consome 1 chave para abrir)\n");
                printf(" = : Porta aberta livremente\n");
                printf(" O : Botao secreto no chao\n");
                printf(" L : Escada que conecta os andares\n");
                printf(" X : Monstro Bobo (anda para direcoes totalmente aleatorias)\n");
                printf(" Y : Monstro Perseguidor (calcula rotas para cacar voce)\n");
                printf(" Z : BOSS FINAL (tem 3 pontos de vida)\n");
                printf("\nCONTROLES DO TECLADO:\n");
                printf(" W, A, S, D -> Movem o seu personagem pelo mapa\n");
                printf(" I          -> Interage com elements (Portas, Botoes, Escadas, NPC)\n");
                printf(" O          -> Ataca na direcao atual usando sua arma equipada\n");
                printf(" M          -> Abandona a partida e retorna para este menu principal\n");
                printf("\nPressione qualquer tecla para retornar ao menu...");
                _getch(); // Espera o usuario clicar em qualquer tecla do teclado
                system("cls"); // Limpa a tela ao sair do tutorial
                break; // Obrigatorio para nao executar o codigo dos casos de baixo

            // --- CASO 2: INICIAR A PARTIDA ---
            case 2:
                // Toda vez que um novo jogo comeca, limpamos os status antigos para comecar do zero
                fase = 1;
                armaEquipada = 0; 
                vidas = 3;
                jogando = 1; 
                precisaRecarregar = 1; // Ativa o gatilho para gerar a Vila na primeira rodada

                // ====================================================================
                // LACO DE EXECUCAO DO JOGO (GAME LOOP PRINCIPAL)
                // ====================================================================
                while(jogando == 1)
                {
                    // ----------------------------------------------------------------
                    // CRIADOR E RECONSTRUTOR DE MAPAS (GERACAO DOS CENARIOS)
                    // ----------------------------------------------------------------
                    if (precisaRecarregar == 1)
                    {
                        chaves = 0; // O heroi perde chaves nao utilizadas ao resetar ou mudar de andar
                        monstroX_vivo = 0; 
                        monstroY_vivo = 0; 
                        bossZ_vivo = 0; 
                        bossZ_hp = 3;
                        
                        // --- CONSTRUTOR: FASE 1 (A VILA INICIAL) ---
                        if (fase == 1) 
                        {
                            linhas = 10; 
                            colunas = 10; 
                            playerX = 5; 
                            playerY = 5; 
                            dirAtual = '^';
                            
                            // Monta a matriz da Vila usando dois lacos 'for' tradicionais
                            for(l = 0; l < linhas; l++) 
                            {
                                for(c = 0; c < colunas; c++) 
                                {
                                    // Se estiver nas bordas da matriz, coloca uma parede '*'
                                    if (l == 0 || l == linhas - 1 || c == 0 || c == colunas - 1) 
                                    {
                                        mapa[l][c] = '*';
                                    } 
                                    // Caso contrario, deixa o espaco vazio ' ' (chao livre)
                                    else 
                                    {
                                        mapa[l][c] = ' ';
                                    }
                                }
                            }
                            mapa[2][5] = 'C'; // NPC Ferreiro posicionado
                            mapa[8][5] = 'L'; // Escada de descida posicionada
                        }
                        
                        // --- CONSTRUTOR: FASE 2 (PRIMEIRO ANDAR DA MASMORRA) ---
                        else if (fase == 2) 
                        {
                            linhas = 10; 
                            colunas = 10; 
                            playerX = 1; 
                            playerY = 1; 
                            dirAtual = 'V';
                            
                            for(l = 0; l < linhas; l++) 
                            {
                                for(c = 0; c < colunas; c++) 
                                {
                                    if (l == 0 || l == 9 || c == 0 || c == 9) 
                                    {
                                        mapa[l][c] = '*';
                                    } 
                                    else 
                                    {
                                        mapa[l][c] = ' ';
                                    }
                                }
                            }
                            // Posicionamento manual de paredes internas para criar um labirinto
                            mapa[1][2]='*'; mapa[2][2]='*'; mapa[3][2]='*'; mapa[3][3]='*';
                            mapa[3][4]='*'; mapa[3][5]='*'; mapa[3][6]='*'; mapa[3][7]='*';
                            mapa[2][7]='*'; mapa[1][7]='*';
                            
                            // Objetos espalhados estrategicamente no Andar 1
                            mapa[2][1]='k'; // Caixa de madeira obstruindo o caminho
                            mapa[5][4]='@'; // Uma chave jogada
                            mapa[3][8]='D'; // Porta trancada
                            mapa[1][8]='L'; // Escada secreta atrás da porta
                        }
                        
                        // --- CONSTRUTOR: FASE 3 (SEGUNDO ANDAR - LABIRINTO MEDIO) ---
                        else if (fase == 3) 
                        {
                            linhas = 15; 
                            colunas = 15; 
                            playerX = 1; 
                            playerY = 1; 
                            dirAtual = 'V';
                            
                            for(l = 0; l < linhas; l++) 
                            {
                                for(c = 0; c < colunas; c++) 
                                {
                                    if (l == 0 || l == 14 || c == 0 || c == 14) 
                                    {
                                        mapa[l][c] = '*';
                                    } 
                                    else 
                                    {
                                        mapa[l][c] = ' ';
                                    }
                                }
                            }
                            // Cria uma grande parede divisoria dividindo o mapa na linha 7
                            for(c = 1; c < 14; c++) 
                            {
                                mapa[7][c] = '*';
                            }
                            // Coloca duas portas nessa grande parede do meio
                            mapa[7][7] = 'D'; 
                            mapa[7][12] = 'D';
                            
                            // Posiciona armadilhas de espinhos '#' pelo cenario
                            mapa[4][3]='#'; mapa[4][4]='#'; mapa[4][5]='#'; 
                            mapa[10][8]='#'; mapa[11][8]='#';
                            
                            // Chaves, Botoes e Caixas espalhados
                            mapa[2][12]='@'; 
                            mapa[5][2]='@'; 
                            mapa[2][2]='O';  // Botao que libera a saida
                            mapa[10][5]='k';
                            
                            // Configura e ativa o Monstro Bobo X
                            monstroX_l = 10; 
                            monstroX_c = 12; 
                            monstroX_vivo = 1; 
                            mapa[monstroX_l][monstroX_c] = 'X';
                            
                            // Cria paredes cobrindo a escada final (Elas somem quando apertar o botao 'O')
                            mapa[12][12]='*'; mapa[12][13]='*'; mapa[13][12]='*'; 
                            mapa[13][13]='L'; // A escada esta encurralada aqui
                        }
                        
                        // --- CONSTRUTOR: FASE 4 (TERCEIRO ANDAR - COVIL DO BOSS Z) ---
                        else if (fase == 4) 
                        {
                            linhas = 25; 
                            colunas = 25; 
                            playerX = 2; 
                            playerY = 12; 
                            dirAtual = 'V';
                            
                            for(l = 0; l < linhas; l++) 
                            {
                                for(c = 0; c < colunas; c++) 
                                {
                                    if (l == 0 || l == 24 || c == 0 || c == 24) 
                                    {
                                        mapa[l][c] = '*';
                                    } 
                                    else 
                                    {
                                        mapa[l][c] = ' ';
                                    }
                                }
                            }
                            
                            // Cria grandes blocos de paredes decorativas/obstaculos para a arena do Boss
                            for(l = 10; l <= 20; l++) { mapa[l][7] = '*'; mapa[l][17] = '*'; }
                            for(c = 7; c <= 17; c++) { mapa[10][c] = '*'; mapa[20][c] = '*'; }
                            for(l = 1; l <= 9; l++) { mapa[l][7] = '*'; mapa[l][17] = '*'; }
                            
                            mapa[5][7] = ' ';  // Passagem secreta da esquerda
                            mapa[5][17] = ' '; // Passagem secreta da direita
                            
                            // Tripla barreira de portas trancadas protegendo o Boss central
                            mapa[8][12]='D'; mapa[9][12]='D'; mapa[10][12]='D';
                            
                            // Três chaves espalhadas nas extremidades do mapa gigante
                            mapa[2][2]='@'; mapa[2][22]='@'; mapa[22][12]='@';
                            
                            // Fileiras de espinhos perigosos pela sala do trono
                            mapa[7][11]='#'; mapa[7][12]='#'; mapa[7][13]='#'; 
                            mapa[3][2]='#';  mapa[3][3]='#';  mapa[4][2]='#';    
                            mapa[3][21]='#'; mapa[3][22]='#'; mapa[4][22]='#'; 
                            
                            // Caixas espalhadas pela arena
                            mapa[11][12]='k'; mapa[15][10]='k'; mapa[15][14]='k';
                            mapa[13][10]='*'; mapa[13][14]='*'; mapa[17][10]='*'; mapa[17][14]='*';
                            
                            // Ativa o Monstro Perseguidor Inteligente Y
                            monstroY_l = 8; 
                            monstroY_c = 3; 
                            monstroY_vivo = 1; 
                            mapa[monstroY_l][monstroY_c] = 'Y';
                            
                            // Ativa o temido BOSS FINAL Z no centro da arena
                            bossZ_l = 15; 
                            bossZ_c = 12; 
                            bossZ_vivo = 1; 
                            bossZ_hp = 3; 
                            mapa[bossZ_l][bossZ_c] = 'Z';
                        }
                        
                        // Coloca fisicamente o icone do jogador no mapa gerado
                        mapa[playerX][playerY] = dirAtual; 
                        precisaRecarregar = 0; // Desliga a flag para que o jogo rode normalmente
                    }

                    // ----------------------------------------------------------------
                    // DESENHO DO MAPA (RENDERIZACAO NA TELA)
                    // ----------------------------------------------------------------
                    system("cls"); // Apaga a tela anterior para desenhar a atual

                    for(l = 0; l < linhas; l++) 
                    {
                        for(c = 0; c < colunas; c++) 
                        {
                            printf("%c ", mapa[l][c]); // Mostra o caractere seguido de um espaco em branco
                        }
                        printf("\n"); // Quebra a linha ao terminar as colunas daquela linha
                    }
                    
                    // --- PAINEL DE INFORMACOES (HUD) ---
                    if(armaEquipada == 0)      { printf("\nArma: Nenhuma"); }
                    else if(armaEquipada == 1) { printf("\nArma: Espada (Area 3x2 a frente)"); }
                    else if(armaEquipada == 2) { printf("\nArma: Arco e Flecha (Linha Reta ate 4 blocos)"); }
                    else if(armaEquipada == 3) { printf("\nArma: Cajado (Explosao circular em volta)"); }
                    
                    if (bossZ_vivo == 1) 
                    { 
                        printf(" | VIDA DO BOSS Z: %d", bossZ_hp); 
                    }
                    
                    printf("\n\nVidas Restantes: %d | Chaves: %d\n", vidas, chaves);
                    printf("Comandos: W,A,S,D (Andar) | I (Interagir) | O (Atacar) | M (Voltar ao Menu)\nDigite seu comando: ");
                    
                    tecla = _getch(); // Captura o clique do teclado de forma instantanea sem precisar de Enter

                    // Botao de emergencia: Sair para o Menu
                    if (tecla == 'm' || tecla == 'M') 
                    {
                        jogando = 0; 
                    }
                    
                    // ----------------------------------------------------------------
                    // CONTROLE DE MOVIMENTACAO DO JOGADOR
                    // ----------------------------------------------------------------
                    
                    // --- MOVER PARA CIMA (W) ---
                    else if (tecla == 'w' || tecla == 'W') 
                    {
                        dirAtual = '^'; // Atualiza o visual do jogador olhando para cima
                        proxima = mapa[playerX - 1][playerY]; // Salva o que tem na linha de cima
                        
                        // Se pisou em algo perigoso, perde vida
                        if (proxima == '#' || proxima == 'X' || proxima == 'Y' || proxima == 'Z') 
                        { 
                            printf("\nVoce colidiu com um perigo fatal!\n");
                            vidas--; 
                            if (vidas <= 0) 
                            {
                                system("cls"); 
                                printf("\n=== GAME OVER ===\nVoce perdeu todas as suas vidas...\n\n"); 
                                system("pause"); 
                                jogando = 0;
                            } 
                            else 
                            {
                                printf("O andar sera reiniciado! Vidas restantes: %d\n", vidas); 
                                system("pause"); 
                                precisaRecarregar = 1; 
                                continue; // Pula o resto dos comandos e volta para o inicio do loop
                            }
                        }
                        // Se o caminho for chao limpo ou porta aberta, anda com sucesso
                        else if (proxima == ' ' || proxima == '=') 
                        { 
                            mapa[playerX][playerY] = ' '; // Apaga a posicao antiga
                            playerX--;                     // Sobe uma linha na matriz
                        }
                        mapa[playerX][playerY] = dirAtual; // Desenha o jogador na nova posicao
                    }
                    
                    // --- MOVER PARA BAIXO (S) ---
                    else if (tecla == 's' || tecla == 'S') 
                    {
                        dirAtual = 'V'; // Desenha o jogador olhando para baixo
                        proxima = mapa[playerX + 1][playerY]; // Salva o que tem na linha de baixo
                        
                        if (proxima == '#' || proxima == 'X' || proxima == 'Y' || proxima == 'Z') 
                        { 
                            printf("\nVoce colidiu com um perigo fatal!\n");
                            vidas--; 
                            if (vidas <= 0) {
                                system("cls"); printf("\n=== GAME OVER ===\nVoce perdeu todas as suas vidas...\n\n"); system("pause"); jogando = 0;
                            } else {
                                printf("O andar sera reiniciado! Vidas restantes: %d\n", vidas); system("pause"); 
                                precisaRecarregar = 1; continue;
                            }
                        }
                        else if (proxima == ' ' || proxima == '=') 
                        { 
                            mapa[playerX][playerY] = ' '; 
                            playerX++; // Desce uma linha na matriz
                        }
                        mapa[playerX][playerY] = dirAtual; 
                    } 
                    
                    // --- MOVER PARA A ESQUERDA (A) ---
                    else if (tecla == 'a' || tecla == 'A' )
                    {
                        dirAtual = '<'; // Desenha o jogador olhando para a esquerda
                        proxima = mapa[playerX][playerY - 1]; // Salva o que tem na coluna da esquerda
                        
                        if (proxima == '#' || proxima == 'X' || proxima == 'Y' || proxima == 'Z') 
                        { 
                            printf("\nVoce colidiu com um perigo fatal!\n");
                            vidas--; 
                            if (vidas <= 0) {
                                system("cls"); printf("\n=== GAME OVER ===\nVoce perdeu todas as suas vidas...\n\n"); system("pause"); jogando = 0;
                            } else {
                                printf("O andar sera reiniciado! Vidas restantes: %d\n", vidas); system("pause"); 
                                precisaRecarregar = 1; continue;
                            }
                        }
                        else if (proxima == ' ' || proxima == '=') 
                        { 
                            mapa[playerX][playerY] = ' '; 
                            playerY--; // Recua uma coluna na matriz
                        }
                        mapa[playerX][playerY] = dirAtual;   
                    }
                    
                    // --- MOVER PARA A DIREITA (D) ---
                    else if (tecla == 'd' || tecla == 'D')
                    {
                        dirAtual = '>'; // Desenha o jogador olhando para a direita
                        proxima = mapa[playerX][playerY + 1]; // Salva o que tem na coluna da direita
                        
                        if (proxima == '#' || proxima == 'X' || proxima == 'Y' || proxima == 'Z') 
                        { 
                            printf("\nVoce colidiu com um perigo fatal!\n");
                            vidas--; 
                            if (vidas <= 0) {
                                system("cls"); printf("\n=== GAME OVER ===\nVoce perdeu todas as suas vidas...\n\n"); system("pause"); jogando = 0;
                            } else {
                                printf("O andar sera reiniciado! Vidas restantes: %d\n", vidas); system("pause"); 
                                precisaRecarregar = 1; continue;
                            }
                        }
                        else if (proxima == ' ' || proxima == '=') 
                        { 
                            mapa[playerX][playerY] = ' '; 
                            playerY++; // Avanca uma coluna na matriz
                        }
                        mapa[playerX][playerY] = dirAtual;      
                    }
                    
                    // ----------------------------------------------------------------
                    // SISTEMA DE INTERACAO COM O CENARIO (TECLA I)
                    // ----------------------------------------------------------------
                    else if (tecla == 'i' || tecla == 'I')
                    {
                        // Comeca espelhando a posicao do heroi
                        alvoX = playerX;
                        alvoY = playerY;
                        
                        // Modifica as coordenadas do alvo baseado na direcao que o heroi esta olhando
                        if(dirAtual == '^')      { alvoX--; } // Olhando para cima: alvo e a linha de cima
                        else if(dirAtual == 'V') { alvoX++; } // Olhando para baixo: alvo e a linha de baixo
                        else if(dirAtual == '<') { alvoY--; } // Olhando para esquerda: alvo e a coluna anterior
                        else if(dirAtual == '>') { alvoY++; } // Olhando para direita: alvo e a proxima coluna
                        
                        // [INTERACAO] NPC Ferreiro ('C') - Valido apenas na Fase 1
                        if(mapa[alvoX][alvoY] == 'C' && fase == 1)
                        {
                            system("cls");
                            printf("--- ANCIÃO FERREIRO DA VILA ---\n\n\"Saudacoes, jovem guerreiro! Escolha sua arma de graca:\"\n\n");
                            printf("1) Espada Longa (Dano retangular abrangente)\n");
                            printf("2) Arco de Cacador (Disparo retilineo de longo alcance)\n");
                            printf("3) Cajado de Cristal (Explosao em area de 360 graus)\n");
                            printf("\nSua escolha (1-3): ");
                            scanf("%d", &escolhaArma);
                            while (getchar() != '\n'); // Limpa buffer do ferreiro tambem
                            
                            if(escolhaArma >= 1 && escolhaArma <= 3) 
                            { 
                                armaEquipada = escolhaArma; // Salva o codigo da arma escolhida
                                printf("\nArma guardada e equipada na mochila com sucesso!\n\n"); 
                            }
                            else 
                            { 
                                printf("\nOpcao invalida! Voce continuara atacando de maos vazias.\n\n"); 
                            }
                            system("pause");
                        }
                        
                        // [INTERACAO] Pegar Chave do Chao ('@')
                        else if (mapa[alvoX][alvoY] == '@') 
                        { 
                            chaves++; 
                            mapa[alvoX][alvoY] = ' '; // Limpa a chave do mapa deitando o espaco
                            printf("\nVoce guardou 1 Chave Reluzente!\n"); 
                            system("pause"); 
                        }
                        
                        // [INTERACAO] Abrir Portas Trancadas ('D')
                        else if (mapa[alvoX][alvoY] == 'D')
                        {
                            if (chaves > 0) 
                            { 
                                chaves--; // Consome a chave da mochila
                                mapa[alvoX][alvoY] = '='; // Modifica o caractere para porta aberta livremente
                                printf("\nPorta destrancada com sucesso!\n"); 
                            }
                            else 
                            { 
                                printf("\nA fechadura esta trancada! Voce precisa de uma chave (@).\n"); 
                            }
                            system("pause");
                        }                   
                        
                        // [INTERACAO] Pressionar Botao de Chao ('O')
                        else if (mapa[alvoX][alvoY] == 'O')
                        {
                            mapa[alvoX][alvoY] = ' '; // Consome o botao desativando-o
                            printf("\nVoce ouviu um forte estalo no chao!\n");
                            
                            // Evento unico da Fase 3: Destroi blocos secretos revelando a escada encurralada
                            if (fase == 3) 
                            { 
                                mapa[12][12] = ' '; 
                                mapa[12][13] = ' '; 
                                mapa[13][12] = ' '; 
                                printf("As pedras que cercavam a saida desmoronaram! Caminho livre para a Escada!\n"); 
                            }
                            system("pause");
                        }
                        
                        // [INTERACAO] Entrar in Escadas de Transicao ('L')
                        else if (mapa[alvoX][alvoY] == 'L') 
                        {
                            if (fase == 1) 
                            {
                                printf("\n\nDescendo em direcao ao 1o Andar da Masmorra...\n"); 
                                system("pause"); 
                                fase = 2; 
                                precisaRecarregar = 1; // Forca a construcao do mapa do Andar 1
                            }
                            else if (fase == 2) 
                            {
                                printf("\n\nDescendo em direcao ao 2o Andar (O Grande Labirinto)...\n"); 
                                system("pause"); 
                                fase = 3; 
                                precisaRecarregar = 1; // Forca a construcao do mapa do Andar 2
                            }
                            else if (fase == 3) 
                            {
                                printf("\n\nDescendo ao 3o Andar... O COVIL SAGRADO DO BOSS FINAL Z!\n"); 
                                system("pause"); 
                                fase = 4; 
                                precisaRecarregar = 1; // Forca a construcao do mapa da Arena do Boss
                            }
                        }
                    } 
                    
                    // ----------------------------------------------------------------
                    // SISTEMA DE ATAQUE E COMBATE (TECLA O)
                    // ----------------------------------------------------------------
                    else if (tecla == 'o' || tecla == 'O')
                    {
                        if (armaEquipada == 0) 
                        { 
                            printf("\nVoce esta desarmado e nao pode golpear! Garanta uma arma com o Ferreiro na Vila.\n"); 
                            system("pause"); 
                        }
                        else
                        {
                            // --- ARMA 1: LOGICA DA ESPADA (Ataque amplo em bloco 3x2) ---
                            if (armaEquipada == 1) 
                            {
                                // Define o retangulo de efeito dependendo de para onde o heroi esta olhando
                                if (dirAtual == '^') 
                                { 
                                    linhaInicio = playerX - 2; linhaFim = playerX - 1; 
                                    colunaInicio = playerY - 1; colunaFim = playerY + 1; 
                                }
                                else if (dirAtual == 'V') 
                                { 
                                    linhaInicio = playerX + 1; linhaFim = playerX + 2; 
                                    colunaInicio = playerY - 1; colunaFim = playerY + 1; 
                                }
                                else if (dirAtual == '<') 
                                { 
                                    linhaInicio = playerX - 1; linhaFim = playerX + 1; 
                                    colunaInicio = playerY - 2; colunaFim = playerY - 1; 
                                }
                                else if (dirAtual == '>') 
                                { 
                                    linhaInicio = playerX - 1; linhaFim = playerX + 1; 
                                    colunaInicio = playerY + 1; colunaFim = playerY + 2; 
                                }

                                printf("\nVoce balanca sua espada fazendo um corte horizontal!\n");

                                // Varre todas as celulas dentro do retangulo determinado
                                for (linha = linhaInicio; linha <= linhaFim; linha++) 
                                {
                                    for (coluna = colunaInicio; coluna <= colunaFim; coluna++) 
                                    {
                                        // Protecao: Impede a verificacao de posicoes inexistentes fora dos limites do mapa
                                        if (linha >= 0 && linha < linhas && coluna >= 0 && coluna < colunas) 
                                        {
                                            if (mapa[linha][coluna] == 'k')      { mapa[linha][coluna] = ' '; printf("- Caixa de madeira estracalhada!\n"); }
                                            else if (mapa[linha][coluna] == 'X') { mapa[linha][coluna] = ' '; monstroX_vivo = 0; printf("- Voce exterminou o Monstro X!\n"); }
                                            else if (mapa[linha][coluna] == 'Y') { mapa[linha][coluna] = ' '; monstroY_vivo = 0; printf("- Voce executou o Monstro Y!\n"); }
                                            else if (mapa[linha][coluna] == 'Z') { bossZ_hp--; printf("- Golpe de raspao no BOSS Z!\n"); }
                                        }
                                    }
                                }
                            }
                            
                            // --- ARMA 2: LOGICA DO ARCO E FLECHA (Linha reta ate 4 blocos de distancia) ---
                            else if (armaEquipada == 2) 
                            {
                                printf("\nVoce puxa o gatilho e dispara uma flecha certeira!\n");
                                
                                for (alcance = 1; alcance <= 4; alcance++) 
                                {
                                    // Avanca celula por celula na direcao do olhar
                                    if (dirAtual == '^')      { l_ataque = playerX - alcance; c_ataque = playerY; } 
                                    else if (dirAtual == 'V') { l_ataque = playerX + alcance; c_ataque = playerY; }
                                    else if (dirAtual == '<') { l_ataque = playerX;           c_ataque = playerY - alcance; } 
                                    else if (dirAtual == '>') { l_ataque = playerX;           c_ataque = playerY + alcance; }
                                    
                                    if (l_ataque >= 0 && l_ataque < linhas && c_ataque >= 0 && c_ataque < colunas) 
                                    {
                                        if (mapa[l_ataque][c_ataque] == 'k')      { mapa[l_ataque][c_ataque] = ' '; printf("- Flecha quebrou uma caixa a distancia!\n"); }
                                        else if (mapa[l_ataque][c_ataque] == 'X') { mapa[l_ataque][c_ataque] = ' '; monstroX_vivo = 0; printf("- Flecha perfurou o coracao do Monstro X!\n"); }
                                        else if (mapa[l_ataque][c_ataque] == 'Y') { mapa[l_ataque][c_ataque] = ' '; monstroY_vivo = 0; printf("- Flecha imobilizou o Monstro Y!\n"); }
                                        else if (mapa[l_ataque][c_ataque] == 'Z') { bossZ_hp--; printf("- Flecha perfurante atingiu as escamas do BOSS Z!\n"); }
                                    }
                                }
                            }
                            
                            // --- ARMA 3: LOGICA DO CAJADO RUNICO (Explosao radial de 3x3 em torno do heroi) ---
                            else if (armaEquipada == 3) 
                            {
                                printf("\nUma onde de energia magica se expande ao seu redor!\n");
                                
                                // Cria um anel vasculhando os vizinhos ao redor da posicao do jogador
                                for (l_atq = playerX - 1; l_atq <= playerX + 1; l_atq++) 
                                {
                                    for (c_atq = playerY - 1; c_atq <= playerY + 1; c_atq++) 
                                    {
                                        // Nao aplica dano na posicao central (onde esta o proprio heroi)
                                        if (l_atq == playerX && c_atq == playerY) 
                                        { 
                                            continue; 
                                        }
                                        
                                        if (l_atq >= 0 && l_atq < linhas && c_atq >= 0 && c_atq < colunas) 
                                        {
                                            if (mapa[l_atq][c_atq] == 'k')      { mapa[l_atq][c_atq] = ' '; printf("- Impacto magico pulverizou uma caixa!\n"); }
                                            else if (mapa[l_atq][c_atq] == 'X') { mapa[l_atq][c_atq] = ' '; monstroX_vivo = 0; printf("- Explosao baniu o Monstro X!\n"); }
                                            else if (mapa[l_atq][c_atq] == 'Y') { mapa[l_atq][c_atq] = ' '; monstroY_vivo = 0; printf("- Explosao vaporizou o Monstro Y!\n"); }
                                            else if (mapa[l_atq][c_atq] == 'Z') { bossZ_hp--; printf("- Choque arcano eletrocutou o BOSS Z!\n"); }
                                        }
                                    }
                                }
                            }
                            
                            // --- EVENTO ESPECIAL: VERIFICACAO DE VITORIA NO BOSS ---
                            if (bossZ_vivo == 1 && bossZ_hp <= 0)
                            {
                                mapa[bossZ_l][bossZ_c] = ' '; // Remove o corpo do chefe da arena
                                bossZ_vivo = 0;
                                
                                system("cls");
                                printf("\n\n=======================================================\n");
                                printf("               V I T O R I A   M A S S I V A !           \n");
                                printf("=======================================================\n");
                                printf("O gigante Boss Z solta um rugido de agonia e desaba!\n");
                                printf("A nevoa das sombras se dissipa e o vilarejo celebra sua volta!\n");
                                printf("Parabens por zerar o jogo!\n");
                                printf("=======================================================\n\n");
                                system("pause");
                                jogando = 0; // Termina o game loop e volta ao menu inicial
                            }
                            else 
                            {
                                system("pause");
                            }
                        }
                    } 
                    
                    // ----------------------------------------------------------------
                    // INTELIGENCIA ARTIFICIAL (TURNO DOS INIMIGOS)
                    // ----------------------------------------------------------------
                    
                    // --- MOVIMENTO: MONSTRO X (IA Totalmente Aleatoria) ---
                    if (monstroX_vivo == 1)
                    {
                        direcaoX = rand() % 4; // Entrega um valor aleatorio de 0 a 3
                        novaL = monstroX_l;
                        novaC = monstroX_c;
                        
                        if (direcaoX == 0)      { novaL--; } // Tentativa de ir para Cima
                        else if (direcaoX == 1) { novaL++; } // Tentativa de ir para Baixo
                        else if (direcaoX == 2) { novaC--; } // Tentativa de ir para Esquerda
                        else if (direcaoX == 3) { novaC++; } // Tentativa de ir para Direita
                        
                        // Se o espaco sorteado estiver livre, o Monstro X caminha para la
                        if (mapa[novaL][novaC] == ' ' || mapa[novaL][novaC] == '=') 
                        { 
                            mapa[monstroX_l][monstroX_c] = ' '; // Limpa o rastro antigo
                            monstroX_l = novaL; 
                            monstroX_c = novaC; 
                            mapa[monstroX_l][monstroX_c] = 'X'; // Registra ele na nova posicao
                        }
                        // Se esbarrou diretamente nas coordenadas do heroi, causa ferimentos
                        else if (novaL == playerX && novaC == playerY) 
                        { 
                            printf("\nO Monstro X pulou no seu pescoco de surpresa!\n"); 
                            vidas--; 
                            if (vidas <= 0) {
                                system("cls"); printf("\n=== GAME OVER ===\nVoce perdeu todas as suas vidas...\n\n"); system("pause"); jogando = 0;
                            } else {
                                printf("O andar sera reiniciado! Vidas restantes: %d\n", vidas); system("pause"); 
                                precisaRecarregar = 1; continue;
                            }
                        }
                    }
                    
                    // --- MOVIMENTO: MONSTRO Y (IA Perseguicao Direta/Calculada) ---
                    if (monstroY_vivo == 1)
                    {
                        novaL = monstroY_l;
                        novaC = monstroY_c;
                        
                        // Avalia onde o jogador esta e avanca na direcao dele diminuindo a distancia
                        if (playerX < monstroY_l)      { novaL--; }
                        else if (playerX > monstroY_l) { novaL++; }
                        else if (playerY < monstroY_c) { novaC--; }
                        else if (playerY > monstroY_c) { novaC++; }
                        
                        if (mapa[novaL][novaC] == ' ' || mapa[novaL][novaC] == '=') 
                        { 
                            mapa[monstroY_l][monstroY_c] = ' '; 
                            monstroY_l = novaL; 
                            monstroY_c = novaC; 
                            mapa[monstroY_l][monstroY_c] = 'Y'; 
                        }
                        else if (novaL == playerX && novaC == playerY) 
                        { 
                            printf("\nO Monstro Perseguidor Y encurralou voce!\n"); 
                            vidas--; 
                            if (vidas <= 0) {
                                system("cls"); printf("\n=== GAME OVER ===\nVoce perdeu todas as suas vidas...\n\n"); system("pause"); jogando = 0;
                            } else {
                                printf("O andar sera reiniciado! Vidas restantes: %d\n", vidas); system("pause"); 
                                precisaRecarregar = 1; continue;
                            }
                        }
                    }
                    
                    // --- MOVIMENTO: BOSS Z (IA Gigante Perseguicao Avançada) ---
                    if (bossZ_vivo == 1)
                    {
                        novaL = bossZ_l;
                        novaC = bossZ_c;
                        
                        // Persegue o jogador fechando o cerco inclusive pelas diagonais
                        if (playerX < bossZ_l) { novaL--; } else if (playerX > bossZ_l) { novaL++; }
                        if (playerY < bossZ_c) { novaC--; } else if (playerY > bossZ_c) { novaC++; }
                        
                        // Habilidade passiva do Chefe: Quebra caixas ('k') que estiverem bloqueando seus passos
                        if (mapa[novaL][novaC] == 'k') 
                        { 
                            mapa[novaL][novaC] = ' '; 
                        }
                        
                        if (mapa[novaL][novaC] == ' ' || mapa[novaL][novaC] == '=') 
                        { 
                            mapa[bossZ_l][bossZ_c] = ' '; 
                            bossZ_l = novaL; 
                            bossZ_c = novaC; 
                            mapa[bossZ_l][bossZ_c] = 'Z'; 
                        }
                        else if (novaL == playerX && novaC == playerY) 
                        { 
                            printf("\nO Boss Z desferiu um soco massivo esmagando seus ossos!\n"); 
                            vidas--; 
                            if (vidas <= 0) {
                                system("cls"); printf("\n=== GAME OVER ===\nVoce perdeu todas as suas vidas...\n\n"); system("pause"); jogando = 0;
                            } else {
                                printf("O andar sera reiniciado! Vidas restantes: %d\n", vidas); system("pause"); 
                                precisaRecarregar = 1; continue;
                            }
                        }
                    }
                    
                } // Fim do laco do Game Loop Interno
                break;

            // --- CASO 3: CREDITO E FINALIZACAO DO PROGRAMA ---
            case 3:
                printf("\n\n---- OBRIGADO POR JOGAR NOSSO JOGO ----\n\n");
                printf("------- TRABALHO DESENVOLVIDO POR -------\n\n");
                printf("Adan Arthur Mathias De Castro Correa De Melo\n");
                printf("Davi Fernando Costa Nunes\n");
                printf("Fernando Ariel Dias Nobre\n\n");
                
                menuLoop = 0; // Rompe o laco do menu para fechar o programa de forma correta
                break;

            // --- CASO PADRAO (DEFAULT): SE O USUARIO DIGITAR UMA LETRA OU NUMERO INVALIDO ---
            default:
                printf("\nOpcao Invalida! Por favor, digite apenas os numeros 1, 2 ou 3.\n");
                system("pause");
                system("cls");
                break;
        }
    } 
    
    return 0;
}