
#include "individual.h"
#include "struct.h"

int isDigitsIncreasing(int num) {
    int lastDigit = num % 10;  // Получаем последнюю цифру числа
    num /= 10;  // Убираем последнюю цифру из числа

    if(num == 0)
    {
        return 2; // число состоит из одной цифры
    }
    while (num > 0) {
        int currentDigit = num % 10;  // Получаем текущую цифру числа
        if (currentDigit >= lastDigit) {
            return 1;  // Если текущая цифра больше или равна предыдущей, числа не возрастают
        }
        lastDigit = currentDigit;
        num /= 10;
    }

    return 0;  // Все цифры удовлетворяют условию возрастания
}

int isDigitsDecreasing(int num) {
    int lastDigit = num % 10;  // Получаем последнюю цифру числа
    num /= 10;  // Убираем последнюю цифру из числа

    if(num == 0)
    {
        return 2;
    }
    while (num > 0) {
        int currentDigit = num % 10;  // Получаем текущую цифру числа
        if (currentDigit <= lastDigit) {
            return 1;  // Если текущая цифра меньше или равна предыдущей, числа не убывают
        }
        lastDigit = currentDigit;
        num /= 10;
    }

    return 0;  // Все цифры удовлетворяют условию убывания
}


void balance_j(Lists &lists)
{
    List *ptr = lists.head;
    while(ptr)
    {
        int j = 0;
        Elem *el = ptr->elems;
        while(el)
        {
            el->j = j;
            el = el->next;
            j++;
        }
        ptr = ptr->next;
    }
}

void input_elem_individual(Lists &lists, List &ptr, int j, int info, int flag, int pos)
{
    Elem *elem = new Elem;
    elem->info = info;
    elem->j = j;
    elem->next = nullptr;

    if(flag == 1) // head == nullptr
    {
        lists.head->elems = elem;
        lists.head->next = nullptr;
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
    if(pos == 0)
    {
        elem->next = el_ptr;
        ptr.elems = elem;
        return;
    }
    if(pos == 1)
    {
        el_ptr = el_ptr->next;
        while(el_ptr)
        {
            el_ptr = el_ptr->next;
            el_ptr_prev = el_ptr_prev->next;
        }
        el_ptr_prev->next = elem;
    }
}

void input_list_individual(Lists &lists, int i, int j, int info, int pos)
{
    int flag = 0;
    if(lists.head == nullptr)
    {
        List *_new = new List;
        _new->i = i;
        lists.head = _new;
        flag = 1;
        input_elem_individual(lists, *_new, j, info, flag, pos);

        return;
    } else {
        List *ptr = lists.head;
        List *ptr_prev = ptr;

        if(ptr->i == i)
        {
            input_elem_individual(lists, *ptr, j, info, flag, pos);
            return;
        }

        ptr = ptr->next;
        while(ptr)
        {
            if(i == ptr->i){
                input_elem_individual(lists, *ptr, j, info, flag, pos);
                return;
            }
            ptr = ptr->next;
            ptr_prev = ptr_prev->next;
        }
        List *_new = new List;
        _new->i = i;
        ptr_prev->next = _new;
        _new->next = nullptr;
        input_elem_individual(lists, *_new, j, info, 3, pos);
    }
}

void individual_func(Lists &lists)
{
    Lists *lists_2 = new Lists;
    lists_2->m = lists.m;
    lists_2->n = lists.n;
    lists_2->head = nullptr;

    int i = INT_MIN;
    int j;
    int info = INT_MIN;
    int pos = 0; // 0 = push_head
    // 1 = push_tail
    int x;
    List *ptr = lists.head;

    while(ptr)
    {
        i = ptr->i;
        j = 0;
        Elem *el = ptr->elems; // elems->head
        while(el)
        {
            info = el->info;
            x = isDigitsIncreasing(info);
            if(x == 2)
            {
                pos = 0;
                input_list_individual(*lists_2, i, j, info, pos);
                j++;
                el = el->next;
                continue;
            } else if(x == 0){
                pos = 0;
                input_list_individual(*lists_2, i, j, info, pos);
                j++;
            }
            x = isDigitsDecreasing(info);
            if(x == 0){
                pos = 1;
                input_list_individual(*lists_2, i, j, info, pos);
                j++;
            }
            el = el->next;
        }

        ptr = ptr->next;
    }
    balance_j(*lists_2);
    output_2(*lists_2);
    deleteLists(*lists_2);
}
