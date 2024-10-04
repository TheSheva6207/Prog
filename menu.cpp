#include <iostream>
#include <limits>
#include <iomanip>

#include "menu.h"
#include "struct.h"
#include "individual.h"

int get_int(){
    int a = 0;
        cin >> a;
        if(cin.eof())
        {
            throw std::runtime_error("Sorry, EOF!!!");
        } else if(cin.bad()){

            throw std::runtime_error("Bad Input!!");
        } else if(cin.fail()) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Incorrect input, repeat!" << endl;
        }
    return a;
}

void menu(Lists &lists){
    int choose = -1;

    int i = -1;
    int j = -1;
    int info = 0;

    while(choose != 0)
    {
        choose = -1;
        cout << "1. Input elems" << endl;
        cout << "2. Output first matrix" << endl;
        cout << "3. Individual " << endl;
        cout << "0. Exit" << endl;
        try{
            while(choose < 0 || choose > 3)
            {
                choose = get_int();
            }
        }
        catch(std::runtime_error& e){
            cout << e.what() << endl;
            deleteLists(lists);
            throw;
        }
        switch (choose)
        {
            case 0:
                return;
            case 1:
                input_list(lists, i, j, info);
                break;
            case 2:
                output_2(lists);
                break;
            case 3:
                output_2(lists);
                individual_func(lists);
                break;
        }
    }
}

