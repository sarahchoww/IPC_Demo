#include <packet/transfer.hpp>

class Sender : public Transfer
{
public:
    Sender(int idValue, bitPack_t *&sendBit);
    int setUp(int idValue, bitPack_t *&sendBit);
    int run(bitPack_t *&sendBit) override;
};
