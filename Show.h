#include <iostream>

using namespace std;

class Show
{
public:
    void FileMenu()
    {
        cout << "1 - Создать ПИФ" << endl;
        cout << "2 - Показать ПИФы" << endl;
        cout << "3 - Выбрать ПИФ" << endl;
        cout << "4 - Вернуться в главное меню" << endl; 
    }

    void MainMenu()
    {
        cout << "1 - Загрузить файл" << endl;
        cout << "2 - Создать файл" << endl;
        cout << "3 - Выйти" << endl;
    }

    void SelectedPIF()
    {
        cout << "1 - Удалить ПИФ" << endl;
        cout << "2 - Изменить ПИФ" << endl;
        cout << "3 - Назад" << endl;
    }

    void ErrorMsg()
    {
        cout << "Что-то пошло не так..." << endl;
    }

    void Warning()
    {
        cout << "!WARNING!\n" << endl;
    }
};