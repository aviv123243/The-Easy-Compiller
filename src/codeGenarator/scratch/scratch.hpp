#ifndef __SCRATCH
#define __SCRATCH

#define NUM_OF_SCRATCH_REGISTERS 7
#define NUM_OF_FLOAT_SCRATCH_REGISTERS 16

#include <string>

using namespace std;
struct scratchRegister
{
    string name;
    bool inUse;
};

class ScratchManager
{
private:
    scratchRegister _regArr[NUM_OF_SCRATCH_REGISTERS];
    scratchRegister _floatRegArr[NUM_OF_FLOAT_SCRATCH_REGISTERS];
    void initRegArr();

public:
    ScratchManager();
    int alloc();
    int allocFloat();
    void free(int i);
    string getName(int i);
    bool isAllocated(int i) { return _regArr[i].inUse; }
};

#endif