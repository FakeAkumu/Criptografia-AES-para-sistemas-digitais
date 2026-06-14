#include "aes.h"
#include <cassert>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>

const uint8_t AESConstants::sbox[256] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b,
    0xfe, 0xd7, 0xab, 0x76, 0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0,
    0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, 0xb7, 0xfd, 0x93, 0x26,
    0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2,
    0xeb, 0x27, 0xb2, 0x75, 0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0,
    0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, 0x53, 0xd1, 0x00, 0xed,
    0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f,
    0x50, 0x3c, 0x9f, 0xa8, 0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5,
    0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, 0xcd, 0x0c, 0x13, 0xec,
    0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14,
    0xde, 0x5e, 0x0b, 0xdb, 0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c,
    0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, 0xe7, 0xc8, 0x37, 0x6d,
    0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f,
    0x4b, 0xbd, 0x8b, 0x8a, 0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e,
    0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, 0xe1, 0xf8, 0x98, 0x11,
    0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f,
    0xb0, 0x54, 0xbb, 0x16};

const uint8_t AESConstants::Rcon[11] = {
    0x00, 0x01, 0x02, 0x04, 0x08, 0x10,
    0x20, 0x40, 0x80, 0x1B, 0x36, // Rcon[1] a Rcon[10] para AES-128
                                  // Rcon[11] a Rcon[12] para AES-192
                                  // Rcon[13] a Rcon[14] para AES-256
};

// Construtor
AES::AES(int keyBits) {
  switch (keyBits) {
  case 128:
    Nk = 4;
    Nr = 10;
    break;

  case 192:
    Nk = 6;
    Nr = 12;
    break;

  case 256:
    Nk = 8;
    Nr = 14;
    break;

  default:
    throw std::invalid_argument("Tamanho de chave invalido");
  }
}

void AES::loadState(const std::vector<uint8_t> &input, uint8_t state[4][4]) {
  for (int col{}; col < 4; col++) {
    for (int row{}; row < 4; row++) {
      state[row][col] = input[col * 4 + row];
    }
  }
}

std::vector<uint8_t> AES::storeState(uint8_t state[4][4]) {
  std::vector<uint8_t> output(16);

  for (int col{}; col < 4; col++) {
    for (int row{}; row < 4; row++) {
      output[col * 4 + row] = state[row][col];
    }
  }
  return output;
}

void AESUtils::printState(uint8_t state[4][4]) {
  for (int row{}; row < 4; row++) {
    for (int col{}; col < 4; col++) {
      std::cout << std::hex << std::setw(2) << std::setfill('0')
                << (int)state[row][col] << ' ';
    }
    std::cout << '\n';
  }
  std::cout << '\n';
}

std::vector<uint8_t> AES::encryptBlock(const std::vector<uint8_t> &plaintext,
                                       const std::vector<uint8_t> &key) {
  if (plaintext.size() != 16)
    throw std::invalid_argument("AES usa blocos de 16 bytes");

  uint8_t state[4][4];

  loadState(plaintext, state);
  KeyExpansion(key);
  AddRoundKey(state, 0);

  AESUtils::printState(state); // Imprime o estado após AddRoundKey inicial

  for (int round{1}; round < Nr; round++) {
    SubBytes(state);
    ShiftRows(state);
    MixColumns(state);
    AddRoundKey(state, round);
  }
  SubBytes(state);
  ShiftRows(state);
  AddRoundKey(state, Nr);

  AESUtils::printState(state); // Imprime o estado após a rodada final

  return storeState(state);
}

void printVector(const std::vector<uint8_t> &v) {
  for (auto b : v) {
    std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)b;
  }
  std::cout << '\n';
}

void AES::SubBytes(uint8_t state[4][4]) {
  for (int row{}; row < 4; row++) {
    for (int col{}; col < 4; col++) {
      state[row][col] = AESConstants::sbox[state[row][col]];
    }
  }
}

void AES::ShiftRows(uint8_t state[4][4]) {
  // deslocamentos para a esquerda
  uint8_t temp;

  // Linha 0 não tem deslocamento

  // Linha 1: desloca 1

  temp = state[1][0];
  state[1][0] = state[1][1];
  state[1][1] = state[1][2];
  state[1][2] = state[1][3];
  state[1][3] = temp;

  // Linha 2: desloca 2
  std::swap(state[2][0], state[2][2]);
  std::swap(state[2][1], state[2][3]);

  // Linha 3: equivalente a deslocar 1 para direita
  temp = state[3][3];
  state[3][3] = state[3][2];
  state[3][2] = state[3][1];
  state[3][1] = state[3][0];
  state[3][0] = temp;
}

namespace AESMath {

uint8_t xtime(uint8_t x) {
  if (x & 0x80)
    return (x << 1) ^ 0x1B;

  return x << 1;
}

uint8_t mul2(uint8_t x) { return xtime(x); }
uint8_t mul3(uint8_t x) { return xtime(x) ^ x; }

} // namespace AESMath

void AES::MixColumns(uint8_t state[4][4]) {
  for (int col{}; col < 4; col++) {
    uint8_t a0 = state[0][col];
    uint8_t a1 = state[1][col];
    uint8_t a2 = state[2][col];
    uint8_t a3 = state[3][col];

    state[0][col] = AESMath::mul2(a0) ^ AESMath::mul3(a1) ^ a2 ^ a3;

    state[1][col] = a0 ^ AESMath::mul2(a1) ^ AESMath::mul3(a2) ^ a3;

    state[2][col] = a0 ^ a1 ^ AESMath::mul2(a2) ^ AESMath::mul3(a3);

    state[3][col] = AESMath::mul3(a0) ^ a1 ^ a2 ^ AESMath::mul2(a3);
  }
}

void AESUtils::RotWord(uint8_t word[4]) {
  uint8_t temp = word[0];
  word[0] = word[1];
  word[1] = word[2];
  word[2] = word[3];
  word[3] = temp;
}

void AES::SubWord(uint8_t word[4]) {
  for (int i{}; i < 4; i++) {
    word[i] = AESConstants::sbox[word[i]];
  }
}

void AES::KeyExpansion(const std::vector<uint8_t> &key) {
  for (int i{}; i < Nk * 4; i++) {
    roundKeys[i] = key[i];
  }

  int totalWords = 4 * (Nr + 1);

  uint8_t temp[4];

  for (int i{Nk}; i < totalWords; i++) {
    for (int j{}; j < 4; j++) {
      temp[j] = roundKeys[(i - 1) * 4 + j];
    }
    if (i % Nk == 0) {
      AESUtils::RotWord(temp);
      SubWord(temp);
      temp[0] ^= AESConstants::Rcon[i / Nk];
    } else if (Nk > 6 && i % Nk == 4) {
      SubWord(temp);
    }
    for (int j{}; j < 4; j++) {
      roundKeys[i * 4 + j] = roundKeys[(i - Nk) * 4 + j] ^ temp[j];
    }
  }
}

void AES::AddRoundKey(uint8_t state[4][4], int round) {
  int offset = round * 16;
  for (int col{}; col < 4; col++) {
    for (int row{}; row < 4; row++) {
      state[row][col] ^= roundKeys[offset + col * 4 + row];
    }
  }
}
