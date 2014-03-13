#pragma once

/*
 * 
 * @file    DiDoIni.h
 * @brief   包含3个类:CIniFile,CIniSection,CIniException,用于方便的读写INI文件
 * @details 基于Win32的GetPrivateProfileString和WritePrivateProfileString

常见问题:
	1. 为什么有的用[]有的用()?
		DiDo::CIniFile ChenIni(_T("c:\\chen.ini"));
		ChenIni[""][""]="xx";
		std::string str = ChenIni[""]("");
		因为如果ChenIni[""][""]既能用于读也能用于写,则每次写之前都会先读,效率差,所以用ChenIni[""][""]代表写,ChenIni[""]("")代表读

	2. 为什么不提供读写int,float,结构体.....
		因为简单更重要,需要类型转换可以用sstream.或std::stoi等

 * @author  ChenGuangXing
 * @version 2014a(alpha)
 * @date    2014年3月12日
 * @code
 #ifdef _UNICODE
	#define COUT std::wcout
 #else
	#define COUT std::cout
 #endif // _UNICODE

 try
 {
	 DiDo::CIniFile ChenIni(_T("c:\\chen.ini"));

	 ChenIni[_T("Hello")][_T("World")] = _T("Hello world!");

	 COUT << ChenIni[_T("Hello")](_T("World"));
 }
 catch ( int e )
 {
	 switch(e){
		 case DiDo::CIniException::Err_FileName_Cannot_Be_NULL: COUT << _T("Err_FileName_Cannot_Be_NULL"); break;
		 case DiDo::CIniException::Err_Section_Cannot_Be_NULL: COUT  << _T("Err_Section_Cannot_Be_NULL");  break;
		 case DiDo::CIniException::Err_Key_Cannot_Be_NULL: COUT      << _T("Err_Key_Cannot_Be_NULL");      break;
		 default:
			throw e;
	}
 }
 * @endcode

 * @todo    
 * @see     
 */

#include <STRING>
#ifdef _UNICODE
	typedef std::wstring tstring;
#else
	typedef std::string tstring;
#endif // _UNICODE

#ifdef _UNICODE
	typedef wchar_t tchar;
#else
	typedef char tchar;
#endif // _UNICODE

#ifndef _T
#ifdef _UNICODE
#define _T(x)      L ## x
#else
#define _T(x)      x
#endif // _UNICODE
#endif // _T

namespace DiDo{

class CIniException{

private:
	int _ErrCode;

public:
	CIniException( int e ){ _ErrCode=e; }

	int GetErrCode(void){ return _ErrCode; }

	enum{ Err_Section_Cannot_Be_NULL  // Section不能为NULL
		,Err_FileName_Cannot_Be_NULL  // FileName不能为NULL
		,Err_Key_Cannot_Be_NULL       // Key不能为NULL
		,Err_FileName_and_Section_and_Key_Cannot_Be_NULL // FileName,Section,Key都不能为空
		,Err_KeyVal_Cannot_Contain_Multiline // Key值不能包含换行
	};
};

//////////////////////////////////////////////////////////////////////////

/** 
* @brief      用于读写Ini通常作为CIniFile的组成部分使用,尽管单独用也可以.
* @note       
* @attention  
* @warning    
* @author     ChenGuangXing
* @date       2014年3月12日
* @version    2014a(alpha)
* Note the following example code: 
* @code 
* @endcode
* @bug        
* @todo       
*/ 
class CIniSection{
private:
	tstring _strIniFile;   // Ini文件名
	tstring _strIniSection;// Section
	tstring _strIniKey;    // Key
	tstring _strVal;       // 从Ini中读出来的Val
	unsigned int _uiMaxKeyVal; // 值最长可以是多少个字符.默认256
	CIniSection(const CIniSection&);
	const CIniSection& CIniSection::operator= (const CIniSection& );
public:
	CIniSection();

	/** 
	* @brief      重载[]获得Key名
	* @param      const tchar* szKey Key名
	*/
	CIniSection&   operator[]( const tchar* szKey );

	/** 
	* @brief      重载()获得Key,名并读出对应的Val
	* @param      const tchar* szKey Key名
	* @return     返回Key对应的Val
	*/
	const tstring& operator()( const tchar* szKey );

	/** 
	* @brief      重载=,为Key赋值
	* @param      const tchar* szKeyVal Key值
	*/
	CIniSection&   operator=( const tchar* szKeyVal );

	/** 
	* @brief      构造,用ini文件名初始化CIniFile
	* @param      const tchar* szIniFileName Ini文件名
	*/
	void SetIniFileName( const tchar* szFileName );

	/** 
	* @brief      设置Section名
	* @param      const tchar* szSection Section名
	*/
	inline void SetIniSection( const tchar* szSection );

	/** 
	* @brief      值字符串最长可以是多少字符
	* @param      unsigned int uiMaxKeyVal 字符数
	*/
	inline void SetMaxKeyVal( unsigned int uiMaxKeyVal );
};



//////////////////////////////////////////////////////////////////////////

/** 
* @brief      用于方便的读写INI
* 
* @details    具体用法参考 @code
* 
* @note       

* @attention  
* @warning    
* @author     ChenGuangXing
* @date       2014年3月12日
* @version    2014a(alpha)
* @bug        Division by zero does not work. 
* @todo       Finish writing the class.
*/ 
class CIniFile{
private:
	const CIniFile& CIniFile::operator= (const CIniFile& );
	CIniFile(const CIniFile&);
public:
	/** 
	* @brief      构造,用ini文件名初始化CIniFile
	* @param      const tchar* szIniFileName Ini文件名,不能为NULL
	*/
	CIniFile( const tchar* szIniFileName, unsigned int uiMaxString=255 );

	inline void SetIniFileName( const tchar* szIniFileName );

	inline void SetMaxKeyVal( unsigned int uiMaxString);

	/** 
	* @brief      重载[]操作符,
	* @param      const tchar* szSection Section名,不能为NULL
	* @return     CIniSection& 
	*/
	CIniSection& operator[](const tchar* szSection );

	/** 
	* @brief   小节类
	*/
	CIniSection _Section;
};

}//namespace DiDo
