#include <packet/transfer.hpp>

class Sender : public Transfer
{
public:
    Sender(int idValue, int **data);
    int setUp(int **data);
    int run(memory_data &iterator, int **data) override;
};
