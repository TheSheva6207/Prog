#include <iostream>
#include <limits>
#include <iomanip>

#include "struct.h"
#include "menu.h"

void output_2(Lists &lists)
{
    List *ptr = lists.head;
    cout << "Output Matrix" << endl;
    int m = lists.m;
    int n = lists.n;
    int index = 0;

    while(index < m)
    {
        if(ptr == nullptr)
        {
            for(int k = 0; k < n; k++)
            {
                cout << std::setw(5) << std::right << "0";
            }
            cout << endl;
            index++;
            continue;
        }
        if(ptr->i > index)
        {
            for(int k = 0; k < n; k++)
            {
                cout << std::setw(5) << std::right << "0";
            }
            cout << endl;
            index++;
            continue;
        } else {
            int temp_j = 0;
            Elem *el = ptr->elems;
            while(temp_j < n)
            {
                if(el == nullptr)
                {
                    cout << std::setw(5) << std::right << "0";
                    temp_j++;
                    continue;
                }
                if(el->j > temp_j)
                {
                    cout << std::setw(5) << std::right << "0";
                    temp_j++;
                    continue;
                } else{
                    cout << std::setw(5) << std::right << el->info;
                    el = el->next;
                    temp_j++;
                }
            }
        }
        cout << endl;
        ptr = ptr->next;
        index++;
    }
}

Lists * create_lists()
{
    int m = 0, n = 0;
    cout << "Enter m" << endl;

        try{
            while (m <= 0) {
                m = get_int();
            }
        }
        catch(std::runtime_error& e){
            cout << e.what() << endl;
            throw;
        }


    cout << "Enter n" << endl;

    try{
        while (n <= 0) {
            n = get_int();
        }
    }
    catch(std::runtime_error& e){
        cout << e.what() << endl;
        throw;
    }
    Lists *big_list = new Lists;
    big_list->m = m;
    big_list->n = n;
    big_list->head = nullptr;
    return big_list;
}

int check_j(Lists &lists, int j)
{
    Elem *ptr = lists.head->elems;
    while(ptr)
    {
        if(j > ptr->j)
        {
            ptr = ptr->next;
            continue;
        } else if (j < ptr->j){
            return 0;
        }
        if(j == ptr->j)
        {
            cout << "This item already exist" << endl;
            return 1;
        }
    }
    return 0;
}

void input_elem(Lists &lists, List &ptr, int j, int info, int flag)
{

    Elem *elem;

    elem = new Elem;
    elem->info = info;
    elem->j = j;
    elem->next = nullptr;

    if(flag == 1) // head == nullptr
    {
        lists.head->elems = elem;
        lists.head->next = nullptr;
        return;
    }

    if(flag == 2) // i < head->i
    {
        ptr.next = lists.head; // ptr_prev == lists->head
        ptr.elems = elem;
        ptr.elems->next = nullptr;
        lists.head = &ptr;
        return;
    }

    if(flag == 3) // ptr_prev->i < i < ptr->i
    {
        ptr.elems = elem;
        ptr.elems->next = nullptr;
        return;
    }

    Elem *el_ptr = ptr.elems;
    Elem *el_ptr_prev = el_ptr;

    if(elem->j < el_ptr->j)
    {
        elem->next = el_ptr;
        ptr.elems = elem;
        return;
    }

    el_ptr = el_ptr->next;
    while(el_ptr)
    {
        if(el_ptr->j > elem->j)
        {
            elem->next = el_ptr;
            el_ptr_prev->next = elem;
            return;
        }
        if(el_ptr->j == j)
        {
            el_ptr->info = elem->info;
            delete elem;
            return;
        }
        el_ptr = el_ptr->next;
        el_ptr_prev = el_ptr_prev->next;
    }
    el_ptr_prev->next = elem;
}

void dialog_input(Lists &lists, int &i, int &j, int &info)
{
    cout << "Enter i from 0 to " << lists.m - 1 << endl;
    try{
        while (i < 0 || i > (lists.m - 1)) {
            i = get_int();
        }
    }
    catch(std::runtime_error& e){
        cout << e.what() << endl;
        throw;
    }

    cout << "Enter j  from 0 to " << lists.n - 1 << endl;
    try{
        while (j < 0 || j > (lists.n - 1)) {
            j = get_int();
        }
    }
    catch(std::runtime_error& e){
        cout << e.what() << endl;
        throw;
    }

    cout << "Enter info" << endl;
    try{
        while (info == 0) {
            info = get_int();
        }
    }
    catch(std::runtime_error& e){
        cout << e.what() << endl;
        throw;
    }

}

void input_list(Lists &lists, int i, int j, int info)
{
    dialog_input(lists, i, j, info);

    int flag = 0;
    if(lists.head == nullptr)
    {
        List *_new = new List;
        _new->i = i;
        lists.head = _new;

        flag = 1;

        input_elem(lists, *_new, j, info, flag);

        return;

    } else if(i < lists.head->i){

        List *_new = new List;
        _new->i = i;

        flag = 2;

        input_elem(lists, *_new, j, info, flag);

        return;

    } else {

        List *ptr = lists.head;
        List *ptr_prev = ptr;

        if(ptr->i == i)
        {
            input_elem(lists, *ptr, j, info, flag);
            return;
        }

        ptr = ptr->next;
        while(ptr)
        {
            if(ptr->i > i)
            {
                List *_new = new List;
                _new->i = i;
                flag = 3;

                _new->next = ptr;
                ptr_prev->next = _new;

                input_elem(lists, *_new, j, info, flag);
                return;
            } else if(i == ptr->i){
                input_elem(lists, *ptr, j, info, flag);
                return;
            }
            ptr = ptr->next;
            ptr_prev = ptr_prev->next;
        }
        List *_new = new List;
        _new->i = i;
        ptr_prev->next = _new;
        _new->next = nullptr;
        input_elem(lists, *_new, j, info, 3);
    }
}

void deleteLists(Lists &listsToDelete) {
    List *currentList = listsToDelete.head;
    while (currentList) {
        List *nextList = currentList->next; // Сохраняем указатель на следующий элемент перед удалением текущего
        Elem *currentElem = currentList->elems;
        while (currentElem) {
            Elem *nextElem = currentElem->next; // Сохраняем указатель на следующий элемент перед удалением текущего
            delete currentElem;
            currentElem = nextElem;
        }
        delete currentList;
        currentList = nextList;
    }

    // Обнуляем указатель на голову, так как все элементы были удалены
    listsToDelete.head = nullptr;
    delete &listsToDelete;
}