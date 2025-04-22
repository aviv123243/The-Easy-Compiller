#include "scratch.hpp"
#include <iostream>

using namespace std;

ScratchManager::ScratchManager()
{
    initRegArr();
}

void ScratchManager::initRegArr()
{
    int regIndex = 0;

    // int/char registers
    _regArr[regIndex++] = scratchRegister{"rbx", false};
    _regArr[regIndex++] = scratchRegister{"r10", false};
    _regArr[regIndex++] = scratchRegister{"r11", false};
    _regArr[regIndex++] = scratchRegister{"r12", false};
    _regArr[regIndex++] = scratchRegister{"r13", false};
    _regArr[regIndex++] = scratchRegister{"r14", false};
    _regArr[regIndex++] = scratchRegister{"r15", false};

    // float registers
    _regArr[regIndex++] = scratchRegister{"xmm0", false};
    _regArr[regIndex++] = scratchRegister{"xmm1", false};
    _regArr[regIndex++] = scratchRegister{"xmm2", false};
    _regArr[regIndex++] = scratchRegister{"xmm3", false};
    _regArr[regIndex++] = scratchRegister{"xmm4", false};
    _regArr[regIndex++] = scratchRegister{"xmm5", false};
    _regArr[regIndex++] = scratchRegister{"xmm6", false};
    _regArr[regIndex++] = scratchRegister{"xmm7", false};
    _regArr[regIndex++] = scratchRegister{"xmm8", false};
    _regArr[regIndex++] = scratchRegister{"xmm9", false};
    _regArr[regIndex++] = scratchRegister{"xmm10", false};
    _regArr[regIndex++] = scratchRegister{"xmm11", false};
    _regArr[regIndex++] = scratchRegister{"xmm12", false};
    _regArr[regIndex++] = scratchRegister{"xmm13", false};
    _regArr[regIndex++] = scratchRegister{"xmm14", false};
    _regArr[regIndex++] = scratchRegister{"xmm15", false};
}

// allocates a new scratch register
int ScratchManager::alloc()
{
    int res = -1;
    for (int i = 0; i < NUM_OF_SCRATCH_REGISTERS; i++)
    {
        if (!_regArr[i].inUse && res == -1)
            res = i;
    }

    if (res == -1)
    {
        cerr << "Fatal error: out of registers";
        exit(-1);
    }

    _regArr[res].inUse = true;
    return res;
}

// allocates a new scratch register
int ScratchManager::allocFloat()
{
    int res = -1;
    for (int i = NUM_OF_SCRATCH_REGISTERS; i < NUM_OF_FLOAT_SCRATCH_REGISTERS; i++)
    {
        if (!_floatRegArr[i].inUse)
            res = i;
    }

    if (res == -1)
    {
        cerr << "Fatal error: out of registers";
        exit(-1);
    }

    _floatRegArr[res].inUse = true;
    return res;
}

bool ScratchManager::isFloat(int i)
{
    return i >= NUM_OF_SCRATCH_REGISTERS && i < NUM_OF_FLOAT_SCRATCH_REGISTERS;
}

// frees an occupied register
void ScratchManager::free(int i)
{
    if (i >= 0 && i < NUM_OF_FLOAT_SCRATCH_REGISTERS)
        _regArr[i].inUse = false;
}

// returns the name of the register
string ScratchManager::getName(int i)
{
    string res;

    if (i >= 0 && i < NUM_OF_FLOAT_SCRATCH_REGISTERS)
        res = _regArr[i].name;

    return res;
}

string ScratchManager::getLowerByteName(int i)
{
    string res = _regArr[i].name;

    // rbx
    if (res[1] == 'b')
    {
        res = "bl";
    }
    else
    {
        res = res + "l";
    }

    return res;
}