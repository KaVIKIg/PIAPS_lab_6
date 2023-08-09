#pragma once
#include <string>
#include <iostream>
#include <string>
//#include "Observer.h"
#include <vector>
#include <map>
#include <ctime>
#include <cstdlib>

class IObserver;
class Teacher;

class IObservable
{
public:
    virtual void RegisterObserver(IObserver* o) = 0;
    virtual  void RemoveObserver(IObserver* o) = 0;
    virtual void NotifyObservers() = 0;
   // virtual ~IObservable() {};
};


class IObserver
{
public:
    virtual void Update(std::map<std::string, int> report_) = 0;

};

class Deanery : public IObserver
{
private:
    //Deanery();
    IObservable* database;


public:
    Deanery(IObservable* obs) : database(obs)
    {
        //database = obs;
        database->RegisterObserver(this);

        
    }

    void Update(std::map<std::string, int> report_)
    {
        std::cout << "---------------------------------------------------------" << std::endl;
        std::cout << "Доклад от Деканата о текущей отчетности:" << std::endl;
        std::cout << "---------------------------------------------------------" << std::endl;
        std::map<std::string, int> ::iterator it = report_.begin();
        for (int i = 0; it != report_.end(); it++, i++)
        {
            
            if (it->second == 1)
            {
                std::cout << it->first << " подготовил отчет по текущей успеваемости." << std::endl << std::endl;
            }

            if (it->second == 0)
            {
                std::cout << it->first << "  не подготовил отчет по текущей успеваемости." << std::endl << std::endl;
            }

        }

        std::cout << "---------------------------------------------------------" << std::endl;
    }
};



class Database : public IObservable
{
public:
     
    Database() {}

    std::vector<IObserver*> observers;
    std::vector<Teacher*> teacher;
    std::map<std::string, int> report_;
    void EndOfTheWeek();


    void RegisterObserver(IObserver* o) 
    {
        observers.push_back(o);
    }

    void RemoveObserver(IObserver* o) 
    {
        observers.erase(remove(observers.begin(), observers.end(), o), observers.end());
    }

    void NotifyObservers() 
    {
        for (int i = 0; i < observers.size(); ++i)
        {
            observers[i]->Update(report_);
        }
    }

    void RegisterTeacher(Teacher* t) 
    {
        teacher.push_back(t);
    }

 
};



class Teacher
{
public:

    Database* database;
    std::string name;
    int report;

    
    Teacher(std::string name, Database* database)
    {
        this->name = name;
        this->database = database;
        database->RegisterTeacher(this);
    }

    std::string GetName()
    {
        return name;
    }

    int  WriteReport()
    {
        report = 0 + rand() % (1 + 1);
        
        return report;
    }

};



void Database :: EndOfTheWeek()
{
    std::string name;
    for (int i = 0; i < teacher.size(); ++i)

    {
        name = teacher[i]->GetName();
        report_[name] = teacher[i]->WriteReport();

    }

    NotifyObservers();
}