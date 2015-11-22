//
// Created by jakub on 11/22/15.
//

#ifndef AC_LOGGER2_H
#define AC_LOGGER2_H

#include "error.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

namespace logger
{
    extern std::ofstream ofs1;

    /*
     * Initiates the log functionality.
     */
    void initLog();

    /*
     * Gets current date in string
     */
    std::string currentDateString();


    template <typename T>
    void log(T t)
    {
        std::cout << t << std::endl ;

        ofs1 << t << std::endl;
    }

    template<typename T, typename... Args>
    void log(T t, Args... args) // recursive variadic function
    {


        std::cout << t << " ";
        ofs1 << t << " ";

        log(args...) ;
    }


}

class Logger
{
private:
public:
    /*
    friend std::ostream& operator<<(std::ostream& os, const Logger& l){
        std::cout << "Inside stream" <<os;
    }*/
    friend std::ostream& operator<<(const char*, const Logger& l){
        //std::cout << "Inside stream" <<os;
    }

};

#endif //AC_LOGGER2_H
