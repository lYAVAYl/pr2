#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <iostream>
#include <sstream>

using namespace std;

class PIF{
    private:
        string _pifName, _companyName;
        double _openCost, _yearAvgCost;
        int _typeId, _id;
    public:
        void SetPIFName(const string& pifName) 
        {
           _pifName = pifName;
        }

        void SetTypeId(const int& typeId) 
        {
           _typeId = typeId; 
        }

        void SetOpenCost(const double& openCost) 
        {
           _openCost = openCost; 
        }

        void SetYearAvgCost(const double& yearAvgCost) 
        {
           _yearAvgCost = yearAvgCost; 
        }

        void SetCompanyName(const string& companyName) 
        {
           _companyName = companyName; 
        }


        string GetPIFName() 
        {
           return _pifName; 
        }

        string GetCompanyName()
        { 
           return _companyName; 
        }

        int GetTypeId() 
        { 
           return _typeId; 
        }

        string GetTypeDescr(int typeId)
        { 
           switch (typeId)
           {
           case 1:
               return "Интервальный";
               break;
           case 2:
               return "Открытый";
               break;
            case 3:
               return "Закрытый";
               break;
            default:
               return " -- ";
               break;
           }; 
        }

        double GetOpenCost() 
        { 
           return _openCost;
        }

        double GetYearAvgCost() 
        { 
           return _yearAvgCost;
        }
        
        int GetId() { 
           return _id; 
        }

        void PrintPIVES()
        {
            cout 
            << "ID: " << _id << "\n" 
            << "Название ПИФа: " << GetPIFName() << "\n" 
            << "Тип: " << GetTypeDescr(_typeId) << "\n" 
            << "Цена открытия: " << GetOpenCost() << "\n" 
            << "Средняя цена за год: " << GetYearAvgCost() << "\n" 
            << "Название компании: " << GetCompanyName() << "\n" 
            << endl; 
        };

        bool Exists()
        {
            return _id >= 0;
        };

        string ConvertToFileWriteFormat()
        {
            stringstream result;

            result << GetPIFName()<< "/" << GetTypeId() << "/" << GetOpenCost() << "/" << GetYearAvgCost() << "/" << GetCompanyName() << "/" << GetId() << "/" << endl;

            return result.str();
        };

        PIF ConverFromFileWriteFormat(char pif[NAME_MAX])
        {
            string stringPIF = pif;

            string pifName, typeId, openCost, yearAvgCost, companyName, id;

            int pointer = 0;

            for (size_t i = 0; i < stringPIF.length(); i++)
            {
                if (stringPIF[i] != '/' && pointer == 0)
                    pifName +=stringPIF[i];
                
                if (stringPIF[i] != '/' && pointer == 1)
                    typeId +=stringPIF[i];

                if (stringPIF[i] != '/' && pointer == 2)
                    openCost +=stringPIF[i];

                if (stringPIF[i] != '/' && pointer == 3)
                    yearAvgCost +=stringPIF[i];
                
                if (stringPIF[i] != '/' && pointer == 4)
                    companyName +=stringPIF[i];
                    
                if (stringPIF[i] != '/' && pointer == 5)
                    id +=stringPIF[i];

                if (stringPIF[i] == '/')
                    pointer++;
            }
            
            PIF resPIF(pifName, stoi(typeId), stod(openCost), stod(yearAvgCost), companyName, stoi(id));

            return resPIF;
        };


        PIF(const string& pifName, const int& typeId, const double& openCost, const double& yearAvgCost, const string& companyName, const int& id)
        :
            _pifName(pifName),
            _typeId(typeId),
            _openCost(openCost),
            _yearAvgCost(yearAvgCost),
            _companyName(companyName),
            _id(id)
        {};
        
        PIF(){};
};
