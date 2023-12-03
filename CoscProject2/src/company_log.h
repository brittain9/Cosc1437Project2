#ifndef COMPANY_LOG_H
#define COMPANY_LOG_H

#include <fstream>
#include <vector>
#include <string>
#include "ILoggable.h"

class CompanyLog {
    std::fstream file;
    std::vector<std::string> lines;

    std::vector<ILoggable*> logs;


public:
    CompanyLog(const std::string& filename);
    ~CompanyLog();

    std::vector<std::string> getLines() { return lines; }
    std::vector<ILoggable*> getLogs() { return logs; }

    void readLines();
    void parseLines(); // fill up our vectors from the txt file
    void writeToFile(const std::string& data);
};

#endif