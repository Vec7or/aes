#include "kica_aes.hpp"
#include <iostream>
#include <string>

int main(int argc, char const *argv[]) {
  /* code */
  auto aes = KicaAES<AES_128>{};
  auto key = std::array<std::byte, 16>{
      std::byte{0x01}, std::byte{0x02}, std::byte{0x03}, std::byte{0x04},
      std::byte{0x05}, std::byte{0x06}, std::byte{0x07}, std::byte{0x08},
      std::byte{0x09}, std::byte{0x0a}, std::byte{0x0b}, std::byte{0x0c},
      std::byte{0x0d}, std::byte{0x0e}, std::byte{0x0f}, std::byte{0x10}};
  auto data = std::array<std::byte, 16>{std::byte{1}};
  (void)aes.encryptBlock(key, data)[0];
  // std::byte res = SBox::inverser(std::byte{0x01});
  // std::cout << std::hex << std::showbase << static_cast<int>(res) <<
  // std::endl;
  return 0;
}
