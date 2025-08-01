#pragma once
#include <string>
#include <utility>

struct Task {
    unsigned long long ID;
    unsigned long long priority;
    std::string name;

    Task(unsigned long long ID, unsigned long long priority, std::string name) : ID(ID), priority(priority), name(std::move(name)) {}
};
