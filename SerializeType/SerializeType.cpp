// SerializeType.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"

#include <iostream>
#include <fstream>

#include "../GameEngine/MoveCamera_Component.h"

int main()
{


	std::ofstream write_file;
	write_file.open("typeinfo_name.txt");

	int a = 1;
	
	write_file << typeid(a).raw_name();
	write_file.close();
	

    return 0;
}

