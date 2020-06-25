#include <packet/transfer.hpp>

class Sender : public Transfer
{
public:
    Sender(int idValue);
    ~Sender();
    int setUp(int idValue);
    int run();
    void genData(memory_data *&addr);
};
