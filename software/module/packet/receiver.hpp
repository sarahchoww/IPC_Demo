#include <packet/transfer.hpp>

class Receiver : public Transfer
{

public:
    Receiver(int idValue, bitPack_t *&sendBit);
    //~Receiver();
    int setUp(int idValue, bitPack_t *&sendBit);
    int run(memory_data &iterator, bitPack_t *&sendBit) override;

};
