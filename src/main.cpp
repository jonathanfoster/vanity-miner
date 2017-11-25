#include <random>
#include <bitcoin/bitcoin.hpp>

int main(int argc, char* argv[])
{
    // Search string required
    if (argc < 2)
    {
        std::cerr << "Usage: vanity-miner search_string" << std::endl;
        return -1;
    }

    std::string search = argv[1];

    // Bitcoin P2PKH addresses always begin with '1'
    if (search.compare(0, 1, "1") != 0)
    {
        std::cerr << "search string does not begin with '1'" << std::endl;
        return -1;
    }

    std::random_device random;
    std::default_random_engine engine(random());

    while (true)
    {
        // Create random secret
        bc::ec_secret secret;
        for (uint8_t& byte: secret)
        {
            byte = engine() % std::numeric_limits<uint8_t>::max();
        }

        // Create random private key and address
        bc::wallet::ec_private private_key(secret);
        bc::wallet::payment_address address(private_key);
        std::string encoded_address = address.encoded();

        // Check if address begins with search string
        if (encoded_address.compare(0, search.length(), search) == 0)
        {
            std::cout << "Address: " << encoded_address << std::endl;
            std::cout << "Secret: " << bc::encode_base16(secret) << std::endl;       
            return 0;
        }
    }

    return 0;
}

