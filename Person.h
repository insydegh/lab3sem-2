//
// Created by fokus on 12.11.2021.
//

#pragma once
#include "vector"
#include "fstream"
#include "string"
#include "sstream"

class Person {
private:
    int ID;
    string name;
    string surname;
    int age;
    string region;
    int income;
public:
    Person():ID(0),name(""),surname(""),age(0),region(""),income(0) {}
    Person(int ID, string name, string surname, int age, string region, int income):ID(ID),name(name),surname(surname),age(age), region(region), income(income) {}

    int GetID() { return this->ID; }
    string GetName() { return this->name; }
    string GetSurname() { return this->surname; };
    int GetAge() { return this->age; }
    string GetRegion() { return this->region; }
    int GetIncome() { return this->income; }

    void SetID(int ID) { this->ID = ID; }
    void SetName(string name) { this->name = name; }
    void SetSurname(string surname) { this->surname = surname; }
    void SetAge(int age) { this->age = age; }
    void SetRegion(string region) { this->region = region; }
    void SetIncome(int income) { this->income = income; }

};



Sequence<Person>* ParseFile() {
    Sequence<Person> *list = new ArraySequence<Person>();

    ifstream file("../data.csv");
    std::string line;
    while (std::getline(file, line)) {
        //line.replace(line.begin(), line.end(), ';', ' ');
        vector<string> words;
        std::stringstream ss(line);
        std::string word;

        while (std::getline(ss, word, ';')) {
            words.push_back(word);
        }
        Person pr = Person(stoi(words[0]), words[1], words[2], stoi(words[3]), words[4], stoi(words[5]));
        list->Append(pr);
    }
    return list;
}


int (Person::*id)() = &Person::GetID;
int (Person::*age)() = &Person::GetAge;
int (Person::*inc)() = &Person::GetIncome;
string (Person::*name)() = &Person::GetName;
string (Person::*sur)() = &Person::GetSurname;
string (Person::*reg)() = &Person::GetRegion;