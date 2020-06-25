#include <packet/transfer.hpp>

class Receiver : public Transfer
{

public:
    Receiver(int idValue);
    ~Receiver();
    int setUp(int idValue);
    int run();

};
