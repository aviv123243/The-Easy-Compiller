#include "tableEntery.hpp"

tableEntery createEntery(SyntaxToken *symbol,enteryType type)
{
    return tableEntery{symbol,type};
}