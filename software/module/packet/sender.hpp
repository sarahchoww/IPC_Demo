#include <packet/transfer.hpp>

class Sender : public Transfer
{
public:
    Sender(int idValue, uint8_t **data);
    int setUp(uint8_t **data);
    int run(memory_data &iterator, uint8_t data[]) override;
};
