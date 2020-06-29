#include <packet/transfer.hpp>

class Sender : public Transfer
{
public:
    Sender(int idValue, bitPack_t *&sendBit);
    int setUp(int idValue, bitPack_t *&sendBit);
    int run(memory_data &iterator, bitPack_t *&sendBit) override;
};
