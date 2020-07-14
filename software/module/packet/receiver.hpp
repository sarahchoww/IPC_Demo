#include <packet/transfer.hpp>

class Receiver : public Transfer
{

public:
    Receiver(int idValue, bitPackCP_t *&sendBit);
    //~Receiver();
    int setUp(int idValue, bitPackCP_t *&sendBit);
    int run(memory_data &iterator, bitPackCP_t *&sendBit) override;

};
