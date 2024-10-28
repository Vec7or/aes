#ifndef SUBKEY_FACTORY_HPP
#define SUBKEY_FACTORY_HPP

#include <array>
#include <cstddef>

#include "s_box.hpp"
#include "utilities.hpp"

template <aes_key_size KEY_SIZE> class SubkeyFactory {
  static_assert(KEY_SIZE == AES_128 || KEY_SIZE == AES_196 ||
                    KEY_SIZE == AES_256,
                "Unsuported AES keysize selected");

private:
  static inline constexpr size_t getIterations() {
    switch (KEY_SIZE) {
    case AES_128:
      return 10;
    case AES_196:
      return 8;
    case AES_256:
      return 7;
    default:
      return 0;
    }
  }

  static constexpr std::array<std::byte, 10> roundConstant{
      std::byte{0x01}, std::byte{0x02}, std::byte{0x04}, std::byte{0x08},
      std::byte{0x10}, std::byte{0x20}, std::byte{0x40}, std::byte{0x80},
      std::byte{0x1B}, std::byte{0x36}};

  static inline constexpr void
  subkeyGFunction(unsigned int round, std::array<std::byte, 4> &input) {
    std::byte first = input[0];
    for (size_t i = 0; i < input.size(); i++) {
      input[i] = input[i + 1];
    }
    input[3] = first;

    for (size_t i = 0; i < input.size(); i++) {
      input[i] = SBox::forward(input[i]);
    }

    input[0] = input[0] ^ roundConstant[round - 1];
  }

  static inline constexpr std::array<std::byte, static_cast<size_t>(KEY_SIZE)>
  getSubkey(unsigned int round,
            std::array<std::byte, static_cast<size_t>(KEY_SIZE)> lastSubkey) {
    constexpr size_t wordSize = 4;
    std::array<std::array<std::byte, wordSize>, KEY_SIZE / wordSize> slices;
    // printByteArray(lastSubkey);
    for (size_t i = 0; i < slices.size(); i++) {
      for (size_t y = 0; y < slices[i].size(); y++) {
        slices[i][y] = lastSubkey[i * wordSize + y];
      }
      // printByteArray(slices[i]);
    }
    std::array<std::byte, wordSize> gFunctionWord;
    std::copy(std::begin(slices.back()), std::end(slices.back()),
              std::begin(gFunctionWord));
    subkeyGFunction(round, gFunctionWord);

    for (size_t i = 0; i < slices[0].size(); i++) {
      slices[0][i] = slices[0][i] ^ gFunctionWord[i];
    }

    for (size_t i = 1; i < slices.size(); i++) {
      for (size_t j = 0; j < slices[i].size(); j++) {
        slices[i][j] = slices[i][j] ^ slices[i - 1][j];
      }
    }
    // printByteArray(gFunctionWord);

    std::array<std::byte, static_cast<size_t>(KEY_SIZE)> subkey{};
    for (size_t i = 0; i < slices.size(); i++) {
      for (size_t j = 0; j < slices[i].size(); j++) {
        subkey[i * wordSize + j] = slices[i][j];
      }
    }

    return subkey;
  }

public:
  static constexpr auto
  calculateSubkeys(std::array<std::byte, static_cast<size_t>(KEY_SIZE)> key) {
    std::array<std::array<std::byte, static_cast<size_t>(KEY_SIZE)>,
               getIterations() + 1>
        subkeys{};
    subkeys[0] = key;
    for (size_t i = 1; i < getIterations() + 1; i++) {
      subkeys[i] = getSubkey(i, subkeys[i - 1]);
    }

    return subkeys;
  }
};

#endif // SUBKEY_FACTORY_HPP