#include <packet/transfer.hpp>

class Receiver : public Transfer
{

public:
    Receiver(int idValue, int **data);
    int setUp(int **data);
    int run(memory_data &iterator, int **data) override;

};
