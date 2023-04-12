// imaged.cpp : Defines the entry point for the console application.
//
// Copy file from internet onto local file
//      Uses Wininet API
//    program takes 1 mandatory command line argument - URL string
//    it downloads ito the current directory, or whatever is passed
//    as the second parameter to DownloadURLImage.
//    optional parameter, the name of the file (excluding path), by default it uses the
//    filename from the URL string.

#include "stdafx.h"
#include <iostream>
#include <windows.h> 
#include <WinInet.h>  // from SDK
#include "string.h"
//#include<TCHAR.H>
//#include "Tchar.h"
using namespace std;

int convertURLtofname ( TCHAR* szURL, TCHAR* szname )
// extract the filename from the URL 
{
	char aszfilename[100];
	HRESULT result;
	char achar[3], aszURL[100];
	size_t nchars, i, j;
	int fresult;

	fresult = 0;

	nchars = _tcslen ( szURL );
	i = nchars - 1;
	while ((i > 0) && (szURL[i] != '/') && (szURL[i] != '\\')) { i--; }
	j = 0; i++;
	while (i < nchars) { szname[j++] = szURL[i++]; }
	szname[j] = _T ( '\0' );

	//  wcstombs ( aszfilename, szname, 100 );
	//     cout << aszfilename << endl;
	//----------------------------------------------
	return fresult;
}

int determinepathfilename ( TCHAR* szURL, TCHAR* szpath, TCHAR* szname, TCHAR* szpathfilename )
{
	// use path and filename when supplied.  If filename (e.g. funkypic.jpg) is not supplied, then the
	// filename will be extracted from the last part of the URL
	int result;
	result = 0;
	TCHAR szname_copy[100];

	if ((szname == NULL) || (szname[0] == '\0'))
		convertURLtofname ( szURL, szname_copy );
	else
		_tcscpy ( szname_copy, szname );

	if ((szpath == NULL) || (szpath[0] == '\0'))
		_tcscpy ( szpathfilename, szname_copy );
	else
	{
		_tcscpy ( szpathfilename, szpath );
		_tcscat ( szpathfilename, szname_copy );
	}
	return result;
}

bool GetFile ( HINTERNET hOpen, // Handle from InternetOpen()
	TCHAR* szURL,        // Full URL
	TCHAR* szpath,
	TCHAR* szname )
{
	DWORD dwSize;
	TCHAR szHead[15];
	BYTE* szTemp[1024];
	HINTERNET  hConnect;
	FILE* pFile;
	TCHAR  szpathfilename[100];

	szHead[0] = '\0';

	if (!(hConnect = InternetOpenUrl ( hOpen, szURL, szHead, 15, INTERNET_FLAG_DONT_CACHE, 0 )))
	{
		std::cout << "Error: InternetOpenUrl" << std::endl;
		return 0;
	}

	determinepathfilename ( szURL, szpath, szname, szpathfilename );

	if (!(pFile = _tfopen ( szpathfilename, _T ( "wb" ) )))
	{
		std::cerr << "Error _tfopen" << std::endl;
		return false;
	}
	do
	{
		// Keep copying in 1024 bytes chunks, while file has any data left.
		// Note: bigger buffer will greatly improve performance.
		if (!InternetReadFile ( hConnect, szTemp, 1024, &dwSize ))
		{
			fclose ( pFile );
			std::cerr << "Error InternetReadFile" << std::endl;
			return FALSE;
		}
		if (!dwSize)
			break;  // Condition of dwSize=0 indicate EOF. Stop.
		else
			fwrite ( szTemp, sizeof ( BYTE ), dwSize, pFile );
	}   // do
	while (TRUE);
	fflush ( pFile );
	fclose ( pFile );

	return TRUE;
}

int DownloadURLImage ( TCHAR* szURL, TCHAR* szpath, TCHAR* szname )
{
	int result;

	HINTERNET hInternet;

	result = 0;

	hInternet = InternetOpen ( _T ( "imaged" ),
		INTERNET_OPEN_TYPE_DIRECT,  //__in  DWORD dwAccessType
		NULL,                       //__in  LPCTSTR lpszProxyName,
		NULL,                       //__in  LPCTSTR lpszProxyBypass,
		NULL                        //_in   DWORD dwFlags
	);

	GetFile ( hInternet, szURL, szpath, szname );
	InternetCloseHandle ( hInternet );
	return result;
}

int _tmain ( int argc, _TCHAR* argv[] )
{
	if (argc == 2)
	{
		DownloadURLImage ( argv[1], NULL, NULL );
		//DownloadURLImage (argv[1], _T"C:/", NULL);
	}
	else if (argc == 3)
	{
		DownloadURLImage ( argv[1], NULL, argv[2] );
		//DownloadURLImage (argv[1], _T"C:/", argv[2]);
	}
	else
	{
		cout << "Usage: imaged <image URL>" << endl;
	}
	system ( "pause" );
	return 0;
}