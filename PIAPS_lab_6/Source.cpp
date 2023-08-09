#include <string>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
//#include "Observer.h"
#include "Observable.h"

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Rus");

	Database database;  
	Teacher* teacher1 = new Teacher("Teacher1", &database);
	Teacher* teacher2 = new Teacher("Teacher2", &database);
	Teacher* teacher3 = new Teacher("Teacher3", &database);
	Teacher* teacher4 = new Teacher("Teacher4", &database);
	Deanery deanery(&database);
	database.EndOfTheWeek();

	system("pause");
	return 0;
}