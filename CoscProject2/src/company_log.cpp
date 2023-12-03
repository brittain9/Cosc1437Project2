#include "company_log.h"

#include "client.h"
#include "employee.h"

CompanyLog::CompanyLog(const std::string& filename) {
    file.open(filename, std::ios::in | std::ios::out | std::ios::app);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file");
    }
}

CompanyLog::~CompanyLog() {
    if (file.is_open()) {
        file.close();
    }
}

void CompanyLog::readLines() {
    std::vector<std::string> linesRead;
    std::string line;
    file.seekg(0, std::ios::beg);
    while (getline(file, line)) {
        linesRead.push_back(line);
    }
    lines = linesRead;
}

void CompanyLog::parseLines() {
    for (std::string line : lines) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "Client") {
            int id;
            std::string name;
            std::string industry;
            std::vector<int> projectIDs;
            int projectID;

            iss >> id;
            std::getline(iss, name, '\"'); // Discard the first quote
            std::getline(iss, name, '\"'); // Read the name
            std::getline(iss, industry, '\"'); // Discard the space and first quote
            std::getline(iss, industry, '\"'); // Read the industry

            while (iss >> projectID) {
                projectIDs.push_back(projectID);
            }
            Client* client = new Client(id, name, industry, projectIDs);
            logs.push_back(client);
        }
        else if (type == "Project") {
        
        }
        else if (type == "Employee") {
            int id;
            std::string name;
            std::string position;
            int age;
            double salary;
            int history;
            int performance;

            iss >> id;
            std::getline(iss, name, '\"'); // Discard the first quote
            std::getline(iss, name, '\"'); // Read the name
            std::getline(iss, position, '\"'); // Discard the space and first quote
            std::getline(iss, position, '\"'); // Read the industry

            iss >> age >> salary >> history >> performance;
            
            Employee* employee = new Employee(id, name, position, age, salary, history, performance);
            logs.push_back(employee);
        }
        else if (type == "Manager") {
           
        }
        else {
            
        }
    }
}

// Method to write to file
void CompanyLog::writeToFile(const std::string& data) {
    file.clear();
    file.seekp(0, std::ios::end);
    file << data << "\n";
    if (!file.good()) {
        throw std::runtime_error("Failed to write to file");
    }
}

