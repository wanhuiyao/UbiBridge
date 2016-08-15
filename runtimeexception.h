#ifndef RUNTIMEEXCEPTION_H
#define RUNTIMEEXCEPTION_H
#include <exception>
#include <string>
namespace ads_bridge{
    class RuntimeException : public std::exception{
    protected:
        std::string _what;
    public:
        RuntimeException(std::string _what) : _what(_what){}
        const char* what() const noexcept {return _what.c_str();}
        ~RuntimeException() throw(){}
    };
}

#endif // RUNTIMEEXCEPTION_H
