#include <packet/transfer.hpp>

class Receiver : public Transfer
{

public:
    Receiver(int id);
    ~Receiver();
    int setUp(int id);
    int run();

};
