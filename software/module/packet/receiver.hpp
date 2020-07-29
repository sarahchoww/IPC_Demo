#include <packet/transfer.hpp>

class Receiver : public Transfer
{

public:
    Receiver(int idValue, uint8_t **data);
    int setUp(uint8_t **data);
    int run(memory_data &iterator, uint8_t data[]) override;

};
