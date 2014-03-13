// Test_DiDoIni.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include "..\DiDoIni\DiDoIni.h"

#include <STRING>
#ifdef _UNICODE
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif // _UNICODE

#ifdef _UNICODE
	#define COUT std::wcout
#else
	#define COUT std::cout
#endif // _UNICODE

const tchar szKeyVal[] = _T("KeyVal is: hello world!");
const tchar szIniFileName[] = _T(".\\Test_DiDoIni.ini");

void Case_Success(void){

	DiDo::CIniFile DiDoIni(szIniFileName);

	DiDoIni[_T("Section")][_T("Key")] = szKeyVal;

	tstring str;
	str = DiDoIni[_T("Section")](_T("Key"));

	if( 0==str.compare(szKeyVal) ){
		std::cout << ("Case_Success ²âÊÔ³É¹¦!");
	} else {
		std::cout << ("Case_Success ²âÊÔÊ§°Ü!");
	}
	std::wcout << _T("\n");
}

void Case_Err_FileName_Cannot_Be_NULL(){
	try
	{
		DiDo::CIniFile DiDoIni(NULL);
		std::cout << ("Case_Err_FileName_Cannot_Be_NULL ²âÊÔÊ§°Ü!");
		
	}
	catch ( DiDo::CIniException& e )
	{
		if( DiDo::CIniException::Err_FileName_Cannot_Be_NULL==e.GetErrCode() ){
			COUT << ("Case_Err_FileName_Cannot_Be_NULL ²âÊÔ³É¹¦!");
			std::wcout << _T("\n");
		} else {
			std::cout << ("Case_Err_FileName_Cannot_Be_NULL ²âÊÔÊ§°Ü!");
		}
		
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	
	Case_Success();
	Case_Err_FileName_Cannot_Be_NULL();

	getchar();

	return 0;
}

