#include "parser.hpp"
#include "../lexer/lexer.hpp"
#include "../errors/errors.hpp"
//#include "../nodes/nodes.hpp"
#include <vector>




bool tryParseInt(string num)
{
    try{
        stoi(num);

        return true;
    }catch(invalid_argument)
    {
        return false;
    }
    catch(out_of_range)
    {
        return false;
    }
}