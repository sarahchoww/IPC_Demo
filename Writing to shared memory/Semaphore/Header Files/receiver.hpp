#include "transfer.hpp"

class Receiver : public Transfer
{

public:
    Receiver();
    ~Receiver();
    int setUp();
    void cleanUp();

    int run();

};
