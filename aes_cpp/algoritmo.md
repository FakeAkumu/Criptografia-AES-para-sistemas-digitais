# Descrição do AES
Breve descrição sobre seu funcionamento para realização do trabalho

## Especificações do algoritmo
Algoritmo de criptografia simétrico, com tamanho de bloco e chave variáveis, 128, 192 e 256 bits. Ele é rápido e enxuto.

Resultado das operações é colocado numa matriz de estado, uma matriz retangular de bytes, 4 linhas e Nb (número de blocos) do tamanho do bloco, 128, 192, 256, dividido por 32

A cifra da chave também é uma matriz retangular de bits, com 4 linhas e Nk colunas pelo tamanho da chave, dividido por 32
As colunas só podem assumir valores de 4, 6 ou 8

Tanto o vetor de entrada, quanto de saída é uma vetor de 4*Nb - 1 (esses blocos podem ser de 16, 24 ou 32 bytes), para cifragem da chave, o vetor é numerado de 4*Nk-1

As transformações dos dados são feitas em rodadas por 4 operações: ByteSub, ShiftRow, MixColumn e AddRoundKey, com exceção da última rodada que usa apenas ByteSub, ShiftRow e AddRoundKey

- Nk - Tamanho da chave
- Nb - Tamanho do bloco
- Nr - Número de rodadas

| Algoritmo | Nk words | Nb words | Nr |
| --------------- | --------------- | --------------- | --------------- |
| AES-128 | 4 | 4 | 10 |
| AES-192 | 6 | 4 | 12 |
| AES-256 | 8 | 4 | 14 |

A versão final aprovada foi para um tamanho do bloco de entrada (input), saída (output) e da matriz de estado interna serem de 128 bits (16 bytes).
Com Nb=4, reflete em um número de palavras de 32 bits (número de colunas) na matriz de estado. Porém, o tamanho da chave de criptografia 'K' pode variar de 128, 192, ou 256 bits.

No AES moderno Nb = 4 sempre e bloco = 128 sempre, apenas a chave varia.
A matriz de estado sempre é 4x4 bytes

O número de rodadas serve para cifragem e para decifragem. Tais transformações são orientadas por bytes:
1. Substituição de byte usando a tabela de substituição (S-box);
2. Deslocamento de linha da matriz de estado por valores diferentes;
3. Mistura dos dados com cada coluna da matriz de estados;
4. Adicionar a chave de rodada na matriz de estado.


## Referências
[Dissertação](https://repositorio.unifei.edu.br/jspui/handle/123456789/1693)
