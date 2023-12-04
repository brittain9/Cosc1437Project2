#ifndef COMPANY_LOG_H
#define COMPANY_LOG_H

#include <fstream>
#include <vector>
#include <string>
#include "ILoggable.h"
#include "client.h"
#include "employee.h"
#include "manager.h"
#include "project.h"

void WriteToLog(ILoggable* toLog);

class CompanyLog {
    static std::fstream file;

    //read lines will get our lines
    std::vector<std::string> lines;

    // parse lines will fill up our vector
    static std::vector<ILoggable*> logs;

public:
    CompanyLog(const std::string& filename);
    ~CompanyLog();

    std::vector<std::string> getLines() { return lines; }
    static std::vector<ILoggable*> getLogs() { return logs; }
    static void addToLog(ILoggable* add);

    void readLines();
    void parseLines(); // fill up our vectors from the txt file

    static std::vector<ILoggable*> getInstancesFromIds(std::vector<int> ids);
    static std::vector<ILoggable*> getInstancesOfType(std::string type);
};

#endif