#include "Error.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <iostream>
#include <sstream>
/*


 F. Aubert

*/
using namespace prog3d;
using namespace std;


void prog3d::error(string mesg,int line,string fichier) {
    cout << "Error in " << fichier << " line " << line << " : " << mesg << endl;
    exit(1);
}

Error::Error(string mesg, int line,const char *fichier) {
        std::ostringstream oss;
        oss << "Error in "<< fichier << " line " << line << " : " << mesg;
        this->message = oss.str();
    }

const char * Error::what() const throw() {
     return this->message.c_str();
}


void Error::show() {
    cout << message << endl;
}

Error::~Error() throw() {};
