#pragma once

/*
 * 
 * @file    DiDoIni.h
 * @brief   ����3����:CIniFile,CIniSection,CIniException,���ڷ���Ķ�дINI�ļ�
 * @details ����Win32��GetPrivateProfileString��WritePrivateProfileString

��������:
	1. Ϊʲô�е���[]�е���()?
		DiDo::CIniFile ChenIni(_T("c:\\chen.ini"));
		ChenIni[""][""]="xx";
		std::string str = ChenIni[""]("");
		��Ϊ���ChenIni[""][""]�������ڶ�Ҳ������д,��ÿ��д֮ǰ�����ȶ�,Ч�ʲ�,������ChenIni[""][""]����д,ChenIni[""]("")�����

	2. Ϊʲô���ṩ��дint,float,�ṹ��.....
		��Ϊ�򵥸���Ҫ,��Ҫ����ת��������sstream.��std::stoi��

 * @author  ChenGuangXing
 * @version 2014a(alpha)
 * @date    2014��3��12��
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

	enum{ Err_Section_Cannot_Be_NULL  // Section����ΪNULL
		,Err_FileName_Cannot_Be_NULL  // FileName����ΪNULL
		,Err_Key_Cannot_Be_NULL       // Key����ΪNULL
		,Err_FileName_and_Section_and_Key_Cannot_Be_NULL // FileName,Section,Key������Ϊ��
		,Err_KeyVal_Cannot_Contain_Multiline // Keyֵ���ܰ�������
	};
};

//////////////////////////////////////////////////////////////////////////

/** 
* @brief      ���ڶ�дIniͨ����ΪCIniFile����ɲ���ʹ��,���ܵ�����Ҳ����.
* @note       
* @attention  
* @warning    
* @author     ChenGuangXing
* @date       2014��3��12��
* @version    2014a(alpha)
* Note the following example code: 
* @code 
* @endcode
* @bug        
* @todo       
*/ 
class CIniSection{
private:
	tstring _strIniFile;   // Ini�ļ���
	tstring _strIniSection;// Section
	tstring _strIniKey;    // Key
	tstring _strVal;       // ��Ini�ж�������Val
	unsigned int _uiMaxKeyVal; // ֵ������Ƕ��ٸ��ַ�.Ĭ��256
	CIniSection(const CIniSection&);
	const CIniSection& CIniSection::operator= (const CIniSection& );
public:
	CIniSection();

	/** 
	* @brief      ����[]���Key��
	* @param      const tchar* szKey Key��
	*/
	CIniSection&   operator[]( const tchar* szKey );

	/** 
	* @brief      ����()���Key,����������Ӧ��Val
	* @param      const tchar* szKey Key��
	* @return     ����Key��Ӧ��Val
	*/
	const tstring& operator()( const tchar* szKey );

	/** 
	* @brief      ����=,ΪKey��ֵ
	* @param      const tchar* szKeyVal Keyֵ
	*/
	CIniSection&   operator=( const tchar* szKeyVal );

	/** 
	* @brief      ����,��ini�ļ�����ʼ��CIniFile
	* @param      const tchar* szIniFileName Ini�ļ���
	*/
	void SetIniFileName( const tchar* szFileName );

	/** 
	* @brief      ����Section��
	* @param      const tchar* szSection Section��
	*/
	inline void SetIniSection( const tchar* szSection );

	/** 
	* @brief      ֵ�ַ���������Ƕ����ַ�
	* @param      unsigned int uiMaxKeyVal �ַ���
	*/
	inline void SetMaxKeyVal( unsigned int uiMaxKeyVal );
};



//////////////////////////////////////////////////////////////////////////

/** 
* @brief      ���ڷ���Ķ�дINI
* 
* @details    �����÷��ο� @code
* 
* @note       

* @attention  
* @warning    
* @author     ChenGuangXing
* @date       2014��3��12��
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
	* @brief      ����,��ini�ļ�����ʼ��CIniFile
	* @param      const tchar* szIniFileName Ini�ļ���,����ΪNULL
	*/
	CIniFile( const tchar* szIniFileName, unsigned int uiMaxString=255 );

	inline void SetIniFileName( const tchar* szIniFileName );

	inline void SetMaxKeyVal( unsigned int uiMaxString);

	/** 
	* @brief      ����[]������,
	* @param      const tchar* szSection Section��,����ΪNULL
	* @return     CIniSection& 
	*/
	CIniSection& operator[](const tchar* szSection );

	/** 
	* @brief   С����
	*/
	CIniSection _Section;
};

}//namespace DiDo
