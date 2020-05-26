#include "transfer.hpp"

class Receiver : public Transfer
{

public:
    int setUp();
    Receiver();
    ~Receiver();

    int run();

};
