#pragma once

#include <sqlite3.h>
class Database
{
public:
	Database(char * dbFile);
	~Database();
private:
	int connetct();
	int disconnect();
public:
	int execute(char * query);
	static int callback(void * data, int argc, char ** argv, char ** azColName);
private:

	sqlite3 *connection;
	char * dbFile;
};

