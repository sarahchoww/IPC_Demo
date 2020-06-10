#include <packet/transfer.hpp>

class Sender : public Transfer
{
public:
    int setUp(int id);
    Sender(int id);
    ~Sender();
    int run();
    void genData();
};
