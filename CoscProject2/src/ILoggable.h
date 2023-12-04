#ifndef ILOGGABLE_H
#define ILOGGABLE_H

#include <random>
#include <string>

class ILoggable {
protected:
    int id;
public:
    ILoggable() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(1, 500000); // very high prob that we get unique ids
        id = distrib(gen);
    }
    ILoggable(int id) : id(id) {}

    int getId() { return id; }

    virtual std::string getClassName() = 0;

    virtual void createNew() = 0;
    virtual std::string createLogString() = 0;
};

#endif