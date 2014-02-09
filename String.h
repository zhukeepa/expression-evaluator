#ifndef STRING_H
#define STRING_H

#include <map>
#include <queue>
#include <list>
#include <string>

namespace mpw {

class String : public std::string
{
public:
    //Constructors: the only thing we really need to copy over.
    String()                        : std::string()     {}
    String(const std::string& str)  : std::string(str)  {}
    String(const char* s, size_t n) : std::string(s, n) {}
    String(const char* s)           : std::string(s)    {}
    String(size_t n, char c)        : std::string(n, c) {}
    String(const std::string& str, size_t pos, size_t n = npos)
        : std::string(str, pos, n) {}

    template<typename InputIterator> String(InputIterator begin, InputIterator end)
        : std::string(begin, end) {}

    String(const String& str)
        { *this = str.c_str(); }

    //The cast to string should only return the underlying string.
    //:_:TODO:_: Is there an implicit cast to an upper one?

    bool isDouble       () const;
    bool isInParentheses() const;

    //:_:TODO:_: GENERALIZE
    double toDouble() const;

    unsigned findClosingChar(unsigned, char) const;
    unsigned findOpeningChar(unsigned, char) const;

    String&            removeChar       (char);
    std::queue<String> extractStrBetween(char, char);

    std::list<String> separateByChar  (char)                       const;
    std::list<String> separateByCharEx(char, std::map<char, char>) const;

    String strBetweenExcl(unsigned start, unsigned end) const
        { return substr(start + 1, end - start - 1); }
    String strBetweenIncl(unsigned start,unsigned end) const
        { return substr(start, end - start + 1); }

    String eraseBetweenExcl(unsigned start, unsigned end)
        { return erase(start + 1, end - start - 1); }
    String eraseBetweenIncl(unsigned start, unsigned end)
        { return erase(start, end - start + 1); }
};

} //mpw

#endif
