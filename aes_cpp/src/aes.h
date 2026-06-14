#pragma once
#include <cstdint>
#include <vector>

namespace AESMath {
uint8_t xtime(uint8_t x);
uint8_t mul2(uint8_t x);
uint8_t mul3(uint8_t x);
} // namespace AESMath

namespace AESConstants {
extern const uint8_t sbox[256];
extern const uint8_t Rcon[11]; // 11 para ser 128
} // namespace AESConstants

namespace AESUtils {
void printState(uint8_t state[4][4]);
void RotWord(uint8_t word[4]);
} // namespace AESUtils

// Apenas classes abstratas
class AES {
public:
  AES(int keyBits);

  std::vector<uint8_t> encryptBlock(const std::vector<uint8_t> &plaintext,
                                    const std::vector<uint8_t> &key);

  friend void testAES(); // Para acessar membros privados durante os testes

private:
  int Nk; // Tamanho da chave
  int Nr; // Número de rodadas

  uint8_t roundKeys[240];

  void loadState(const std::vector<uint8_t> &input, uint8_t state[4][4]);
  std::vector<uint8_t> storeState(uint8_t state[4][4]);

  void KeyExpansion(const std::vector<uint8_t> &key);

  void SubBytes(uint8_t state[4][4]);
  void SubWord(uint8_t word[4]);
  void ShiftRows(uint8_t state[4][4]);
  void MixColumns(uint8_t state[4][4]);
  void AddRoundKey(uint8_t state[4][4], int round);
};

/* Matriz uint8_t state[4][4]
 * Algoritmo AES armazena por colunas
| b0  b4  b8  b12 |
| b1  b5  b9  b13 |
| b2  b6  b10 b14 |
| b3  b7  b11 b15 |
*/
