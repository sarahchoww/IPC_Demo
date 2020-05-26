#include "transfer.hpp"

class Sender : public Transfer
{
public:
    int setUp();

    Sender();
    ~Sender();

    int run();

    void genData();

};
