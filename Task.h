#pragma once
#include <string>
#include <utility>





struct Task {
    int ID;
    int priority;
    std::string name;

    Task() : ID(0), priority(0), name("") {}

    Task(int ID, int priority, std::string name) : ID(ID), priority(priority), name(std::move(name)) {}
};
