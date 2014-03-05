#include "TwoWayList.h"
#include "Record.h"
#include "Schema.h"
#include "File.h"
#include "Comparison.h"
#include "ComparisonEngine.h"
#include "GenDBFile.h"
#include "DBFile.h"
#include "Defs.h"

using namespace std;
#include <fstream>
#include <iostream>
#include <string.h>

GenDBFile::GenDBFile () {
#if 0
  pageReadInProg = 0;
  currPageIndex = 0;
#endif
}
GenDBFile::~GenDBFile () {
}

int GenDBFile::Create (char *f_path, fType f_type, void *startup) {
#if 0
  /*
   * Create .bin file if doesn't exist
   * Open .bin file
   */
  checkIsFileOpen.open(f_path,ios_base::out | ios_base::in);

  if(checkIsFileOpen.is_open()) {
    currFile.Open(1, f_path);
  }
  else {
    currFile.Open(0, f_path);
  }
  return 1;
#endif
}

void GenDBFile::Load (Schema &f_schema, char *loadpath) {
#if 0

  /*
   * Open .tbl file
   */
  tblFile = fopen(loadpath, "rb");

  if(!tblFile) {
    cout << "\nFailed to Open the file: %s" << loadpath;
    return;
  }

  currRecord = new (std::nothrow) Record;

  int appendStatus = 1;

  /*
   * Read record(s) from .tbl file One at a time
   * till EOF is reached
   */
  while(currRecord->SuckNextRecord(&f_schema, tblFile)) {

      /*
       * Append the sucked record to page
       */
      appendStatus = currPage.Append(currRecord);

      /*
       * If page is full, write the page to file
       */
      if(0 == appendStatus) {


        currFile.AddPage(&currPage, currFile.GetLength());

        appendStatus = 1;

        /*
         * Flush the page to re-use it to store further records
         */
        currPage.EmptyItOut();
        currPage.Append(currRecord);
      }
  }

  /*
   * Wri te this page to file although not full because,
   * we have sucked all records from file
   */
  currFile.AddPage(&currPage, currFile.GetLength());

  /*
   * Free temporary buffer
   */
  delete currRecord;
#endif
}

int GenDBFile::Open (char *f_path) {
#if 0
  /*
   * Create .bin file if doesn't exist
   * Open .bin file
   */
  checkIsFileOpen.open(f_path,ios_base::out | ios_base::in);

  if(checkIsFileOpen.is_open()) {
    currFile.Open(1, f_path);
  }
  else {
    currFile.Open(0, f_path);
  }

  return 1;
#endif
}

int GenDBFile::Close () {
#if 0
  /*
   * Close .bin file
   */
  currFile.Close();
#endif
}

void GenDBFile::MoveFirst () {
#if 0

  /*
   * Check if file really contain any records
   */

//	cout << " Move First";
  if(currFile.GetLength()==0){
    cout << "Bad operation , File Empty" ;
  }
  else{
//	  cout << " Inside DB FIle Move First currPageIndex : "<<currPageIndex<<endl;
    currPageIndex = 0;
    currFile.MoveFirst();
    currFile.GetPage(&currPage, currPageIndex++);
    pageReadInProg = 1;
  }
#endif
}

void GenDBFile::Add (Record &rec) {
#if 0

  if(pageReadInProg==0) {
    // currPageIndex = 460;
    currFile.AddPage(&currPage, currFile.GetLength());
    pageReadInProg = 1;
  }


  if(currFile.GetLength()>0) //existing page
  {
    currFile.GetPage(&currPage,currFile.GetLength()-2);
    currPageIndex = currFile.GetLength()-2;
  }
  if(!currPage.Append(&rec)) //full page
  {
    currPage.EmptyItOut();
    currPage.Append(&rec);
    currPageIndex++;
  }

  currFile.AddPage(&currPage,currPageIndex);
#endif
}

int GenDBFile::GetNext (Record &fetchme)
{
#if 0
//  cout<< " current page index :" << currPageIndex << endl;
//  cout<< " current page length :" << currFile.GetLength() << endl;

	//cout << " Inside DB FIle GetNExt Page" << endl;

  if(pageReadInProg==0) {
    // currPageIndex = 460;
//	  cout << "GetPage 1"<< currPageIndex << endl;
    currFile.GetPage(&currPage, currPageIndex);
    currPageIndex= currPageIndex +1;
    pageReadInProg = 1;
  }


  //fetch page

  if(currPage.GetFirst(&fetchme) ) {
    return 1;
  }
  else{

    if(!(currPageIndex > currFile.GetLength()-2))
    {//cout << "GetPage 2  page index :"<< currPageIndex << endl;
      currFile.GetPage(&currPage, currPageIndex++);
      pageReadInProg++;
      currPage.GetFirst(&fetchme);
      return 1;
    }
    else{
      return 0;
    }
  }
#endif
}

int GenDBFile::GetNext (Record &fetchme, CNF &myComparison, Record &literal) {
#if 0

	/*
   * now open up the text file and start procesing it
   * read in all of the records from the text file and see if they match
	 * the CNF expression that was typed in
   */
	 ComparisonEngine comp;

	 while(GetNext(fetchme)){
		if(comp.Compare (&fetchme, &literal, &myComparison)==1)
			return 1;
	}

  return 0;

#endif
}