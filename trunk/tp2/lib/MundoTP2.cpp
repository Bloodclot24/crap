#include "MundoTP2.h"
#include <iostream>

void MundoTP2::display(){
  std::cout << "Soy el mundo 2\n"; 
}

Mundo* MundoTP2::get_instance(){
  if(te_odio == NULL)
    te_odio=new MundoTP2();
    
  return te_odio;
}