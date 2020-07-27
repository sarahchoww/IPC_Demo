#include <eth/ecpri.hpp>
#include <iostream>

void Transport::getData()
{
    sendTrans->ecpriVersion = 1; // Version 1
    sendTrans->ecpriMessage = 0; // IQ data type
    sendTrans->ecpriConcatenation = 0; // No concatenation
    //sendTrans->ecpriPayload = sizeof(); // Size of payload


}