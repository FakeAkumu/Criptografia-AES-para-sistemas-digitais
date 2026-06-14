#include "src/aes.h"
#include <cstdint>
#include <string>

int main() {
  AES aes(128);

  // mensagem a ser criptografada
  std::vector<uint8_t> bloco = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                                0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
  std::string mensagem = "senha para o cofre é 123456789";
  std::vector<uint8_t> bloco_mensagem(mensagem.begin(), mensagem.end());

  std::vector<uint8_t> chave(16, 0);

  aes.encryptBlock(bloco, chave);

  return 0;
}
