#include <packet/transfer.hpp>

class Sender : public Transfer
{
public:
    Sender(int idValue, bitPackCP_t *&sendBit);
    int setUp(int idValue, bitPackCP_t *&sendBit);
    int run(memory_data &iterator, bitPackCP_t *&sendBit) override;
};
