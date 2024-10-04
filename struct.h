#include <iostream>
#include <limits>
#include <iomanip>
#include <stdexcept>

#ifndef OOP_LAB1_STRUCT_H
#define OOP_LAB1_STRUCT_H

using namespace std;
using std::cin;
using std::cout;
using std::endl;

struct Elem{
    int j;
    int info;
    Elem *next;
};

struct List{
    Elem *elems;
    int i;
    List *next;
};

struct Lists{
    int m;
    int n;
    List *head;
};

void output_2(Lists &lists);
Lists * create_lists();
void input_elem(Lists &lists, List &ptr, int j, int info, int flag);
void dialog_input(Lists &lists, int &i, int &j, int &info);
void input_list(Lists &lists, int i, int j, int info);
void deleteLists(Lists &listsToDelete);
int check_j(List &list, int j);

#endif //OOP_LAB1_STRUCT_H
