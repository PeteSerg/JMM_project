/**
 *        @file: main.cc
 *      @author: Eric Nelson
 *        @date: 
 * @description: 
 * */

#include <iostream>
#include <vector>

#include <bits/stdc++.h>

#include <boost/preprocessor.hpp>

// Macro allows efficient conversion of Enum to string
#define X_DEFINE_ENUM_WITH_STRING_CONVERSIONS_TOSTRING_CASE(r, data, elem)    \
    case elem : return BOOST_PP_STRINGIZE(elem);

#define DEFINE_ENUM_WITH_STRING_CONVERSIONS(name, enumerators)                \
    enum name {                                                               \
        BOOST_PP_SEQ_ENUM(enumerators)                                        \
    };                                                                        \
                                                                              \
    inline const char* ToString(name v)                                       \
    {                                                                         \
        switch (v)                                                            \
        {                                                                     \
            BOOST_PP_SEQ_FOR_EACH(                                            \
                X_DEFINE_ENUM_WITH_STRING_CONVERSIONS_TOSTRING_CASE,          \
                name,                                                         \
                enumerators                                                   \
            )                                                                 \
            default: return "[Unknown " BOOST_PP_STRINGIZE(name) "]";         \
        }                                                                     \
    }

// Data structures
// Options
DEFINE_ENUM_WITH_STRING_CONVERSIONS(Response, (RIP)(TEAR)(DESPACITO)(DEFAULT))

// Local declarations
std::string line(std::string prompt);
Response interpret(std::string response);
int damerau_levenshtein_distance(std::string p_string1, std::string p_string2);
void blackrock();
void bRRip();
void pRip();
void pTear();
void bRTear();

int main(int argc, char **argv){
    //std::cout<<ToString(interpret(line("Rip or Tear?\n")))<<'\n';
    blackrock();

    return EXIT_SUCCESS;
}

// GAME FUNCTIONS
void blackrock(){
    Response response = DEFAULT;
    std::string prompt1 = "You are in the town of Blackrock. Would you like to rip or tear?\n";
    bool good = true;
    do{
        response = interpret(line(prompt1));
        switch(response){
            case RIP:
                bRRip();
                good = true;
                break;
            case TEAR:
                bRTear();
                good = true;
                break;
            case DESPACITO:
                std::cout<<"You can't despacito at this time.\n";
                good = false;
                break;
            default:
                std::cout<<"Input could not be interpreted.\n";
                good = false;
        }
    }while(!good);
}
void bRRip(){
    Response response = DEFAULT;
    std::string prompt1 = "You rip down the streets of Blackrock, impressing a peasant. Would you like to rip or tear?\n";
    bool good = true;
    do{
        response = interpret(line(prompt1));
        switch(response){
            case RIP:
                pRip();
                good = true;
                break;
            case TEAR:
                pTear();
                good = true;
                break;
            case DESPACITO:
                std::cout<<"You can't despacito at this time.\n";
                good = false;
                break;
            default:
                std::cout<<"Input could not be interpreted.\n";
                good = false;
        }
    }while(!good);
}
void pRip(){
    std::cout<<"You rip his arms off, but are seen by a guard and promply killed.\n";
}
void pTear(){
    std::cout<<"You tear off your clothes. The peasant is not impressed, and you live the rest of your life in the dungeon\n";
}
void bRTear(){
    std::cout<<"A single tear runs down your cheek. There is nothing left to conquer\n";
}

// UTILTIY

std::string line(std::string prompt){
    std::cout<<prompt;
    std::string response;
    std::getline(std::cin, response);
    return response;
}

/** Interpret 
 * @param response string to be interpreted
 * @returns clarified response
 * */
Response interpret(std::string response){
    std::vector<std::string> words;

    // Set all lower to upper
    char mask = 0b11011111;
    for(int j = 0; j < response.length(); ++j){
        response[j] = response[j]&mask;
    }

    // Seporate into words
    std::string temp;
    std::stringstream check1(response);
    while(std::getline(check1, temp, '\000'))
    {
        words.push_back(temp);
    }

    // Find matches
    for(std::vector<std::string>::iterator it = words.begin(); it != words.end(); ++it){
        for(int i = 0; i != DEFAULT; ++i){
            if(!(*it).compare(ToString(static_cast<Response>(i)))) return (Response)i;
        }
    }

    // No match, calculate similarity
    int bestGuess = DEFAULT;
    int best = INT_MAX;
    int distance, tollerance; // Tollerance (.5 * distance + 1) is used to prevent "gjkladsfdskljafgkl" from evaluating to "tear"
    for(std::vector<std::string>::iterator it = words.begin(); it != words.end(); ++it){
        for(int i = 0; i != DEFAULT; ++i){
            distance = damerau_levenshtein_distance(*it, ToString(static_cast<Response>(i)));
            tollerance = (0.5 * static_cast<std::string>(ToString(static_cast<Response>(i))).length())+1;
            if(best>distance && distance<tollerance){
                bestGuess = (Response)i;
                best = distance;
            }
        }
    }

    return static_cast<Response>(bestGuess);
}

// Ripped from SO
int damerau_levenshtein_distance(std::string p_string1, std::string p_string2)
{
    int l_string_length1 = p_string1.length();
    int l_string_length2 = p_string2.length();
    int d[l_string_length1+1][l_string_length2+1];

    int i;
    int j;
    int l_cost;

    for (i = 0;i <= l_string_length1;i++)
    {
        d[i][0] = i;
    }
    for(j = 0; j<= l_string_length2; j++)
    {
        d[0][j] = j;
    }
    for (i = 1;i <= l_string_length1;i++)
    {
        for(j = 1; j<= l_string_length2; j++)
        {
            if( p_string1[i-1] == p_string2[j-1] )
            {
                l_cost = 0;
            }
            else
            {
                l_cost = 1;
            }
            d[i][j] = std::min(
            d[i-1][j] + 1,                  // delete
            std::min(d[i][j-1] + 1,         // insert
            d[i-1][j-1] + l_cost)           // substitution
            );
            if( (i > 1) && 
            (j > 1) && 
            (p_string1[i-1] == p_string2[j-2]) && 
            (p_string1[i-2] == p_string2[j-1])
            ) 
            {
            d[i][j] = std::min(
            d[i][j],
             d[i-2][j-2] + l_cost   // transposition
            );
            }
        }
    }
    return d[l_string_length1][l_string_length2];
}