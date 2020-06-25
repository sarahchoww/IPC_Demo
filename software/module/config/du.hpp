#include <packet/receiver.hpp>
#include <packet/sender.hpp>
#include <config/struct.hpp>

class DU
{
protected:
    int bandSectorId;
    int CCid;
    int DUPortId;
    std::string RATtype; // LTE or NR
    double numerology; // 15 kHz for LTE
    std::string divisionDuplex; // FDD or TDD
    double bandwidth; // 1.4, 3, 5, 10, 15, 20 MHz
    std::string prefixType; // Normal or extended

    int numOfFrames;
    int numOfSubframes;
    int numOfSlots;
    int numOfSyms;

    memory_data iterator;


public:
    void setData();
    void iterateData();
    void rotateGrid();

};