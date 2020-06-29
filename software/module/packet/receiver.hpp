#include <packet/transfer.hpp>

class Receiver : public Transfer
{

public:
    Receiver(int idValue, bitPack_t *&sendBit);
    //~Receiver();
    int setUp(int idValue, bitPack_t *&sendBit);
    int run(bitPack_t *&sendBit) override;

};
