#ifndef ILOGGABLE_H
#define ILOGGABLE_H

#include <random>

class ILoggable {
protected:
    int id;
public:
    ILoggable() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(1, 50000); // this will make id a number between 1 and 50000 which should be unique

        id = distrib(gen);
    }
    ILoggable(int id) : id(id) {}

    int getId() { return id; }
    virtual std::string getClassName() = 0;
};

#endif