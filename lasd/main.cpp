
#include "zlasdtest/test.hpp"
#include "zmytest/test.hpp"
#include "list/list.hpp"
#include "vector/vector.hpp"
#include "stack/lst/stacklst.hpp"
#include "stack/vec/stackvec.hpp"
#include "queue/lst/queuelst.hpp"
#include "queue/vec/queuevec.hpp"

/* ************************************************************************** */
#include <iostream>
#include <string>
/* ************************************************************************** */



int main()
{
  int scelta;
  std::cout << "Lasd Libraries 2021" << std::endl;

scelta:
  std::cout << std::endl <<  "Quale test desidera eseguire?" << std::endl
            << "1- lasdtest." << std::endl
            << "2- mytest" << std::endl
            << "0- uscita" << std::endl;
  std::cin >> scelta;
  
  switch (scelta)
  {
  case 1:
   lasdtest(); // To call in the menu of your library test!
    break;
  case 2:
    mytest();
    break;
  case 0:
    return 0;
  default:
    std::cout << "L'opzione inserita: " << scelta << "; non e` valida." << std::endl;
    goto scelta;
    break;
  }
}