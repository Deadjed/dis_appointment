#ifndef INPUT_CHECKS_H
#define INPUT_CHECKS_H

#include "input_chacks.hpp"

#include <Bits.h>
#include <string>
#include <sstream>

#define DELIM "."

/* function to check whether the
   IP Adress passed is valid or not */
bool ip_check(char* s)
{
    size_t n = strlen(s);

    // if length of passed string is
    // more than 3 then it is not valid
    if (n > 3)
        return false;

    // check if the string only contains digits
    // if not then return false
    for (int i = 0; i < n; i++)
        if ((s[i] >= '0' && s[i] <= '9') == false)
            return false;
    std::string str(s);

    // if the string is "00" or "001" or
    // "05" etc then it is not valid
    if (str.find('0') == 0 && n > 1)
        return false;
    std::stringstream geek(str);
    int x;
    geek >> x;

    // the string is valid if the number
    // generated is between 0 to 255
    return (x >= 0 && x <= 255);
}

/* return 1 if IP string is
valid, else return 0 */
int is_valid_ip(char* ip_str)
{
    // if empty string then return false
    if (ip_str == NULL)
        return 0;
    int dots = 0;
    size_t len = strlen(ip_str);
    int count = 0;
    char* next_token;

    // the number dots in the original
    // string should be 3
    // for it to be valid
    for (int i = 0; i < len; i++)
        if (ip_str[i] == '.')
            count++;
    if (count != 3)
        return false;

    // See following link for strtok()

    char* ptr = strtok_s(ip_str, DELIM, &next_token);
    if (ptr == NULL)
        return 0;

    while (ptr) {

        /* after parsing string, it must be valid */
        if (ip_check(ptr))
        {
            /* parse remaining string */
            ptr = strtok_s(NULL, DELIM, &next_token);
            if (ptr != NULL)
                ++dots;
        }
        else
            return 0;
    }

    /* valid IP string must contain 3 dots */
    // this is for the cases such as 1...1 where
    // originally the no. of dots is three but
    // after iteration of the string we find
    // it is not valid
    if (dots != 3)
        return 0;
    return 1;
}


#endif	// INPUT_CHECKS_H