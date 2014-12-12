// KUKRAL_PPR_2014.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "libs/simpleini-master/SimpleIni.h"
#include "Database.h"
#include "RandomNumber.h"
#include "DifferentialEvolution.h"
#include <iostream>

static void dbTest(); //dekladace fce


int _tmain(int argc, _TCHAR* argv[])
{
	DifferentialEvolution * df;
	
	/*RandomNumber * r;
	r = new RandomNumber();
	r->generate();
	delete(r);*/

	df = new DifferentialEvolution();
	df->start();
	delete(df);


	//dbTest();

	printf("Pro ukonèení programu stisknìte libovolnou klávesu.");
	getchar();
	return 0;
}




/************* test ppøipojení db **************/

static void dbTest() {
	Database * d;

	//CSimpleIniA ini;

	//// Should result in file with contents:
	////   [section]
	////   param=123

	//ini.LoadFile("bounds.ini");
	//const char * pVal = ini.GetValue("Bounds", "cmax", "default");

	//printf("value=%s", pVal); // vytiskne hodnotu na obrazovku

	d = new Database("data.sqlite3");
	d->execute("SELECT * from subject");
}

//static int callback(void *data, int argc, char **argv, char **azColName){
//	int i;
//	fprintf(stderr, "%s: ", (const char*)data);
//	for (i = 0; i<argc; i++){
//		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
//	}
//	printf("\n");
//	return 0;
//}



