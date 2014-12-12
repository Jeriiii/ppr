#include "stdafx.h"
#include "Database.h"
#include "libs/cpp-sqlite/CppSQLite3.h"
#include "libs/cpp-sqlite/CppSQLite3.cpp"
#include <sqlite3.h>
#include <iostream>

Database::~Database()
{
}


int Database::execute(char * query)
{
	int i, fld;
	time_t tmStart, tmEnd;
	CppSQLite3DB db;
	CppSQLite3Query q;

	try
	{
		db.open(dbFile);

		CppSQLite3Query q = db.execQuery(query);

		for (fld = 0; fld < q.numFields(); fld++)
		{
			std::cout << q.fieldName(fld) << "|";
		}
		std::cout << std::endl;

		while (!q.eof())
		{
			std::cout << q.fieldValue(0) << "|";
			std::cout << q.fieldValue(1) << "|" << std::endl;
			q.nextRow();
		}

		q.finalize();
		//clouse se zavola automaticky v destruktoru
	}
	catch (CppSQLite3Exception& e)
	{
		std::cerr << e.errorCode() << ":" << e.errorMessage() << std::endl;
	}

	return 0;
}


Database::Database(char * soutceDbFile)
{
	dbFile = soutceDbFile;
}
