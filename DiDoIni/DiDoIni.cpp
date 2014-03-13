#include "DiDoIni.h"
#include <Windows.h> // for GetPrivateProfileString, WritePrivateProfileString

DiDo::CIniSection& DiDo::CIniSection::operator[]( const tchar* szKey )
{
	if( NULL==szKey ){
		throw DiDo::CIniException(CIniException::Err_Key_Cannot_Be_NULL);
	}

	_strIniKey = szKey;

	return *this;
}

const tstring& DiDo::CIniSection::operator()( const tchar* pszKey )
{
	if( NULL==pszKey ){
		throw DiDo::CIniException(CIniException::Err_Key_Cannot_Be_NULL);
	}

	if( _strIniSection.empty()||_strIniKey.empty()||_strIniFile.empty() ){
		throw DiDo::CIniException(CIniException::Err_FileName_and_Section_and_Key_Cannot_Be_NULL);
	}

	tchar* pszVal = new tchar[_uiMaxKeyVal];
	ZeroMemory( pszVal, _uiMaxKeyVal );
	GetPrivateProfileString( _strIniSection.c_str(), _strIniKey.c_str(), _T(""),pszVal , _uiMaxKeyVal, _strIniFile.c_str() );
	_strVal = pszVal;
	delete [] pszVal;

	return _strVal;
}

DiDo::CIniSection& DiDo::CIniSection::operator=( const tchar* pszKeyVal )
{
	if( NULL==pszKeyVal ){
		return *this;
	}

	if( _strIniSection.empty()||_strIniKey.empty()||_strIniFile.empty() ){
		throw DiDo::CIniException(CIniException::Err_FileName_and_Section_and_Key_Cannot_Be_NULL);
	}

	tstring strVal(pszKeyVal);
	if( tstring::npos!=strVal.find(_T('\n')) ){

	}

	WritePrivateProfileString( _strIniSection.c_str(), _strIniKey.c_str(), pszKeyVal, _strIniFile.c_str() );

	return *this;
}

DiDo::CIniSection::CIniSection():_uiMaxKeyVal(256)
{

}

void DiDo::CIniSection::SetIniFileName( const tchar* szFileName )
{

	if( NULL==szFileName ){
		throw DiDo::CIniException(CIniException::Err_FileName_Cannot_Be_NULL);
	}

	_strIniFile = szFileName;
};

void DiDo::CIniSection::SetIniSection( const tchar* szSection )
{

	if( NULL==szSection ){
		throw DiDo::CIniException(CIniException::Err_Section_Cannot_Be_NULL);
	}

	_strIniSection = szSection;
}

void DiDo::CIniSection::SetMaxKeyVal( unsigned int uiMaxKeyVal )
{
	_uiMaxKeyVal = uiMaxKeyVal;
}

DiDo::CIniFile::CIniFile( const tchar* szIniFileName, unsigned int uiMaxString/*=255 */ )
{
	_Section.SetMaxKeyVal( uiMaxString+1 );

	_Section.SetIniFileName( szIniFileName ); // _Section会检查szIniFileName的合法性
}

void DiDo::CIniFile::SetIniFileName( const tchar* szIniFileName )
{
	_Section.SetIniFileName( szIniFileName );
}

void DiDo::CIniFile::SetMaxKeyVal( unsigned int uiMaxString )
{
	_Section.SetMaxKeyVal( uiMaxString );
}

DiDo::CIniSection& DiDo::CIniFile::operator[]( const tchar* szSection )
{
	_Section.SetIniSection( szSection ); // _Section会检查szSection的合法性
	return _Section;
}



