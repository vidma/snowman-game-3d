#ifndef ERROR_H_INCLUDED
#define ERROR_H_INCLUDED

#include <string>
#include <exception>

namespace prog3d {

// critical error : stop the program
void error(std::string mesg,int line,std::string fichier);

// exception
class Error:public std::exception {
    std::string message;
    public:
    Error(std::string msg,int line,const char *fichier);
    virtual ~Error() throw();

    virtual const char * what() const throw();

    void show();

};
}
#endif
