#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "PIF.h"
#include "Show.h"

using namespace std;

char Filename[NAME_MAX];
vector <PIF> pives;
Show show;

//
//Открытие файла на запись
//
void OpenFileForWrite()
{
FILE *file;

if ((file = fopen(Filename, "w")) != NULL)
{
for (size_t i = 0; i < pives.size(); i++)
{
char convertedPIF[NAME_MAX];
strcpy(convertedPIF, pives[i].ConvertToFileWriteFormat().c_str());

fputs(convertedPIF, file);
}

fclose(file);
}
else
show.ErrorMsg();
}

//
//Открытие файла на чтение
//
bool OpenFileForRead()
{
FILE *file;

if ((file = fopen(Filename, "r")) != NULL)
{
while (!feof(file))
{
char fileString[NAME_MAX];

if (fgets(fileString, 255, file) != NULL)
{
PIF pif;

pives.push_back(pif.ConverFromFileWriteFormat(fileString));

strcpy(fileString, "");
}
}

fclose(file);

return true;
}

show.ErrorMsg();
return false;
}

//
//Проверка входящей строки на возможность конвертации в число
//
bool CheckDigit(string num)
{
bool result = true;

for(int i = 0; i < num.length(); i++)
{
if(!isdigit(num[i]))
result = false;
}

return result;
}

//
//Добавление затрат
//
void CreateUpdatePIF(int id = -1)
{
cout << "--Ввод данных--" << endl;

bool isError= false;

string pifName, typeId, openCost, yearAvgCost, companyName;

do{
if(isError)
cout << endl << "— Ошибка ввода! Попробуйте снова--" << endl;

cout << "Название ПИФа: ";
cin >> pifName;

isError = pifName == "";

}while(isError);
isError = false;

do{
if(isError)
cout << "— Выберите доступный тип ПИФа —" << endl;

cout << "Тип ПИФа:" << endl;
cout << "1. Интервальный" << endl;
cout << "2. Открытый" << endl;
cout << "3. Закрытый" << endl;
cin >> typeId;

isError = typeId != "1" && typeId != "2" && typeId != "3";

}while(isError);
isError = false;

do{
if(isError)
cout << endl << "— Ошибка ввода! Попробуйте снова--" << endl;

cout << "Цена открытия: ";
cin >> openCost;

isError = openCost == "" || !CheckDigit(openCost);

}while(isError);
isError = false;

do{
if(isError)
cout << endl << "— Ошибка ввода! Попробуйте снова--" << endl;

cout << "Средняя цена за год: ";
cin >> yearAvgCost;

isError = yearAvgCost == "" || !CheckDigit(yearAvgCost);

}while(isError);
isError = false;

do{
if(isError)
cout << endl << "— Ошибка ввода! Попробуйте снова--" << endl;

cout << "Название компании: ";
cin >> companyName;

isError = companyName == "";

}while(isError);

if(id == -1){
PIF pif(
pifName,
stoi(typeId),
stod(openCost),
stod(yearAvgCost),
companyName,
pives.size());

pives.push_back(pif);
}
else{
pives[id].SetPIFName(pifName);
pives[id].SetTypeId(stoi(typeId));
pives[id].SetOpenCost(stod(openCost));
pives[id].SetYearAvgCost(stod(yearAvgCost));
pives[id].SetCompanyName(companyName);
}

OpenFileForWrite();
}

//
//Вывод затрат
//
void ShowPIVES()
{
for (size_t i = 0; i < pives.size(); i++)
pives[i].PrintPIVES();

show.FileMenu();
}

//
//Удалить затрату
//
void DeletePIF(int id)
{
if (pives[id].Exists())
pives.erase(pives.begin() + id);

OpenFileForWrite();
}

void SelectedPIFActions(int id)
{
show.SelectedPIF();

bool isBack = false;

do
{
string chose;
cin >> chose;

if (chose[0] == '1' || chose[0] == '2' || chose[0] == '3')
{
int numChose = (int)chose[0] - 48;
cout << numChose << endl;

switch (numChose)
{
case 1:
{
DeletePIF(id);
isBack = true;
}
break;
case 2:
{
CreateUpdatePIF(id);
isBack = true;
}
break;
case 3: isBack = true;
break;
}
}
else
cout << "Wrong input, try again..." << endl;
} while (!isBack);

}

void SelectPIF()
{
bool isDigit = false;

cout << "Введите номер ПИФа: ";

do
{
string chose;
cin >> chose;

if (isdigit(chose[0]) || (isdigit(chose[0]) && isdigit(chose[1])) && chose.length() > 0 && chose.length() < 3)
{
isDigit = true;

pives[stoi(chose)].PrintPIVES();

SelectedPIFActions(stoi(chose));
}

} while (!isDigit);

}

void ShowFileMenu()
{
    show.FileMenu();

    bool isExit = false;
    do
    {
    string mainChose;
    cin >> mainChose;
    if (mainChose[0] == '1'
    || mainChose[0] == '2'
    || mainChose[0] == '3'
    || mainChose[0] == '4')
    {
    int numChose = (int)mainChose[0] - 48;

    switch (numChose)
    {
    case 1:
    {
    CreateUpdatePIF();
    show.FileMenu();
    }
    break;
    case 2: ShowPIVES();
    break;
    case 3:
    {
    SelectPIF();
    show.FileMenu();
    }
    break;
    case 4:
    {
    isExit = true;
    show.MainMenu();
    }
    break;
    }
    }
    else
    cout << "Wrong input, try again..." << endl;
    } while (!isExit);
    }

    void SelectFileFocused()
    {
    cout << "Input filename" << endl;
    cin >> Filename;

    if(OpenFileForRead())
    ShowFileMenu();
    else
    show.MainMenu();
    }

    void CreateFileFocused()
    {
    int result;

    do
    {
    cout << "Имя файла: ";
    cin >> Filename;

    result = creat(Filename, S_IREAD|S_IWRITE);

    if (result == -1)
    show.ErrorMsg();

    } while (result == -1);

    cout << result << endl;
    ShowFileMenu();
    }

    void ShowMainMenu()
    {
    show.MainMenu();

    bool isExit = false;

    do
    {
    string mainChose;
    cin >> mainChose;

    if (mainChose[0] == '1' || mainChose[0] == '2' || mainChose[0] == '3')
    {
    int numChose = (int)mainChose[0] - 48;

    switch (numChose)
    {
    case 1: SelectFileFocused();
    break;
    case 2: CreateFileFocused();
    break;
    case 3:
    {
    isExit = true;
    }
    break;
    }
    }
    else
    cout << "Wrong input, try again..." << endl;
    } while (!isExit);
    }

    int main()
    {
    ShowMainMenu();
    }