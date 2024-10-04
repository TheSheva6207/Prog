#include <iostream>
#include <stdexcept>
#include "menu.h"

int main() {
    Lists *lists;
    try{
        lists = create_lists();
        menu(*lists);
        deleteLists(*lists);
    } catch(const std::bad_alloc &ba){
        std::cerr << "Not enough memory" << std::endl;
        //deleteLists(lists);
        return 1;
    }
    catch(const std::exception &e) { // в случае прочих исключений
        std::cerr << e.what() << std::endl;
        //deleteLists(lists);
        return 1;
    }
    return 0;
}
//выделение памяти:
//new
//new[]
//delete
//delete[]

//try
// {
//      int a = b / 0
// } catch (const std::exception&) {
//      a = 0
// }


