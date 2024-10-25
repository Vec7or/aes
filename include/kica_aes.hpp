#ifndef KICA_AES_HPP
#define KICA_AES_HPP

#include <array>
#include <cstddef>
#include <algorithm>
#include <iterator>
#include <iostream>

#include "utilities.hpp"
#include "subkey_factory.hpp"

template <size_t n>
inline void printByteArray(std::array<std::byte, n> input)
{
    std::cout << "[";
    for (size_t i = 0; i < n; i++)
    {
        std::cout << std::hex << std::showbase << static_cast<unsigned int>(input[i]);
        std::cout << std::string{"|"};
    }
    std::cout << "]" << std::endl;
}

template <aes_key_size KEY_SIZE>
class KicaAES
{
    static_assert(KEY_SIZE == AES_128 || KEY_SIZE == AES_196 || KEY_SIZE == AES_256,
                  "Unsuported AES keysize selected");

private:
    static constexpr size_t blockSize = 128 / 8;
    inline constexpr size_t getRounds()
    {
        switch (KEY_SIZE)
        {
        case AES_128:
            return 10;
        case AES_196:
            return 12;
        case AES_256:
            return 14;
        default:
            return 0;
        }
    }

public:
    constexpr KicaAES() {}

    inline std::array<std::byte, blockSize> encryptBlock(std::array<std::byte, static_cast<size_t>(KEY_SIZE)> &key, std::array<std::byte, blockSize> &data)
    {
        auto subkeys = SubkeyFactory<KEY_SIZE>::calculateSubkeys(key);
        for (size_t i = 0; i < subkeys.size(); i++)
        {
            std::cout << std::string{"Subkey Round: "} << std::to_string(i) << std::endl;
            printByteArray(subkeys[i]);
        }

        return std::array<std::byte, blockSize>{std::byte{40}};
    };

    inline std::array<std::byte, blockSize> decryptBlock(std::array<std::byte, static_cast<size_t>(KEY_SIZE)> &key, std::array<std::byte, blockSize> &encryptedData)
    {
        return std::array<std::byte, blockSize>{std::byte{40}};
    }
};

#endif // KICA_AES_HPP