#include "String.h"
#include "Abbreviations.h"
#include <sstream>
#include "Exceptions.h"
#include <iostream>

namespace mpw {

bool
String::isDouble() const
{

    /**
     *  @brief Checks to see if the string passed in meets the requirements of a
     *         Number as specified in the documentation.
    */

    //Can't have no length.
    if (this->length() == 0)
        return false;

    //Number of decimals we encounter; if there's more than one, the string input is
    //not a Number.
    unsigned decimalCount = 0;

    for (unsigned i = 0; i < this->length(); ++i)
    {
        if (!isdigit((*this)[i]))
        {
            if ((*this)[i] != '.')
                return false;
            else
            {
                if (decimalCount == 0)
                    ++decimalCount;
                else
                    return false;
            }
        }
    }
    return true;
}

bool String::isInParentheses() const
{
    if (length() <= 1)
        return false;

    if ((*this)[0] != '(' || (*this)[length() - 1] != ')')
        return false;

    return true;
}

double String::toDouble() const
{
    std::istringstream iss(this->c_str());
    double retVal;
    iss >> retVal;
    return retVal;
}

unsigned
String::findClosingChar(unsigned startPosition, char closeChar) const
{
    assert(startPosition < this->size());

    char openChar = (*this)[startPosition];
    unsigned openCharCount = 1;

    //Scan through the whole string for the proper closing character.
    for (unsigned i = startPosition + 1; i != this->size(); ++i)
    {
        if ((*this)[i] == openChar)
        {
            ++openCharCount;
            continue;
        }

        if ((*this)[i] == closeChar)
        {
            --openCharCount;
            if (openCharCount == 0)
                return i;
        }
    }

    THROW_EXCEPTION(MissingClosingChar, ""); //:_:TODO:_: add more info?
}

unsigned
String::findOpeningChar(unsigned endPosition, char startChar) const
{
    assert(endPosition < this->size());

    char closeChar = (*this)[endPosition];
    unsigned closeCharCount = 1;

    //Scan through the whole string for the proper closing character.
    for (unsigned i = endPosition - 1; i != static_cast<unsigned>(-1); --i)
    {
        if ((*this)[i] == closeChar)
        {
            ++closeCharCount;
            continue;
        }

        if ((*this)[i] == startChar)
        {
            --closeCharCount;
            if (closeCharCount == 0)
                return i;
        }
    }

    THROW_EXCEPTION(MissingClosingChar, ""); //:_:TODO:_: add more info?
}

String&
String::removeChar(char remove)
{
    /**
     *  This removes all instances of remove in this-> For instance, if *this =
     *  "ab c   d efg", and remove = ' ', removeChar() would return "abcdefg".
    */

    std::string retStr;
    for (unsigned i = 0; i < this->size(); ++i)
    {
        if ((*this)[i] != remove)
            retStr += (*this)[i];
    }

    *this = retStr;
    return *this;
}

std::queue<String>
String::extractStrBetween(char openChar, char closeChar)
{
    /**
     *  Suppose that *this = "abc((defg)h)i(jk)", openChar = '(', and closeChar = ')'.
     *  When extractValueBetween is called with those parameters, the contents in
     *  the parentheses are removed from the string placed into the queue that's
     *  returned, IN THE ORDER THAT THEY OCCURRED. Hence, the queue returned would
     *  contain "(defg)h" and "jk" in that order.
    */
    std::queue<String> strQueue;
    unsigned index = 0; //Place to start searching.
    while ((index = this->find(openChar, index)) != std::string::npos)
    {
        unsigned closeCharPos = this->findClosingChar(index, closeChar);
        strQueue.push(this->strBetweenExcl(index, closeCharPos));
        this->eraseBetweenExcl(index, closeCharPos);

        ++index; //First, index was the position of the ( in ---(---)---, where
                 //--- represents any string. Now, index is the position of the )
                 //in ---()---, which is the new string. Hence, from ), we may
                 //continue searching for the next (.
    }

    return strQueue;
}

std::list<String>
String::separateByChar(char separator) const
{
    /**
     *  This function breaks up a string into sections before and after a particular
     *  character. If, for instance, *this = "ab|c|d||efg|h", and separator = '|',
     *  separateStringByChar will return a vector containing "ab", "c", "d", "",
     *  "efg", and "h". Note that despite the fact there is a | missing from the h
     *  at the end, "h" is still returned. By this logic, if the string contains no
     *  | at all, e.g., if it were "abcdefgh", this function would simply return
     *  "abcdefgh".
    */

    //Vector to return.
    String str = *this;

    std::list<String> strList;
    unsigned separatorPos;

    while ((separatorPos = str.find(separator)) != std::string::npos)
    {
        strList.push_back(str.substr(0, separatorPos));
        str.erase(0, separatorPos + 1);
    }

    strList.push_back(str);

    return strList;
}

std::list<String>
String::separateByCharEx(char separator,
                         std::map<char, char> symbolList) const
{
    /**
     *  This does the same thing as separateStringByChar, except it ignores the
     * char's found between each starting symbol and closing symbol in
     *  symbolList. For instance, if separator = '+' and symbolList had one member,
     *  make_pair('(', ')'), and string = "3 + (5 + 8)",
     *  separateStringByCharIgnoringSymbols() would return a list containing "3" and
     *  "(5 + 8)".
     *
     *  First, for each opening character, we create a map mapping that character
     *  to a queue of all values between that opening characters and its respective
     *  closing character. We then call extractStrBetween() for each closing and
     *  opening char. Since as of now, the values between all the closing/opening char pairs are
     *  empty strings, we let retVal be separateStringByChar(*this, separator).
     *  We then go through the map of all values, substituting the values in
     *  appropriately.
     *
     *  :_:TODO:_: Document this function.
    */

    std::map< char, std::queue<String> > charStrMap; //:_:TODO:_: RENAME LATER
    std::list<String> retVal;
    String str = *this;

    for (std::map<char, char>::iterator it = symbolList.begin();
         it != symbolList.end(); ++it)
        charStrMap[it->first] =  str.extractStrBetween(it->first, it->second);

    retVal = str.separateByChar(separator);

    for (std::list<String>::iterator it = retVal.begin(); it != retVal.end(); ++it)
    {
        for (std::map< char, std::queue<String> >::reverse_iterator it2 = charStrMap.rbegin();
             it2 != charStrMap.rend(); ++it2)
        {
            unsigned index = 0;
            while ((index = it->find(it2->first, index)) != String::npos)
            {
                it->insert(index + 1, (it2->second).front());
                (it2->second).pop();

                index = it->findClosingChar(index, symbolList[it2->first]);
            }
        }
    }

    return retVal;
}

}
