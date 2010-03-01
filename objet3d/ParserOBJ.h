#ifndef INC_PARSEROBJ_H
#define INC_PARSEROBJ_H

#include "Parser.h"
#include "Facet.h"
#include "Soup.h"
#include <string>

namespace prog3d {

class Soup;
class ParserOBJ : public Parser {
public:
    ParserOBJ(std::string nom);
    void load(Soup *o);
    Soup *load();
};



}

#endif
