/* XCFrameworkEngine
 * Copyright (C) Abhishek Porwal, 2016
 * Any queries? Contact author <https://github.com/abhishekp314>
 * This program is complaint with GNU General Public License, version 3.
 * For complete license, read License.txt in source root directory. */


#if !defined(_REGISTRAR_H)
#define _REGISTRAR_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "stdio.h"

class CRegistrar
{
protected:
	CRegistrar() {};

	BOOL SetInRegistry(HKEY hRootKey, LPCSTR subKey, LPCSTR keyName,LPCSTR keyValue)
	{
		HKEY hKeyResult;
		DWORD dataLength;
		DWORD dwDisposition;
		if (RegCreateKeyEx( hRootKey, subKey, 0, NULL, REG_OPTION_NON_VOLATILE, 
							KEY_WRITE | KEY_WOW64_32KEY , NULL, &hKeyResult, &dwDisposition) != ERROR_SUCCESS)
		{
			return FALSE;
		}
		dataLength = strlen(keyValue);
		DWORD retVal = RegSetValueEx( hKeyResult, keyName, 0, REG_SZ,(const BYTE *) keyValue, dataLength);
		RegCloseKey(hKeyResult);
		return (retVal == ERROR_SUCCESS) ? TRUE:FALSE;
	}

	BOOL DelFromRegistry(HKEY hRootKey, LPCTSTR subKey)
	{
		long retCode;
		retCode = RegDeleteKey(hRootKey, subKey);
		if (retCode != ERROR_SUCCESS)
			return false;
		return true;
	}

	bool StrFromCLSID(REFIID riid,LPSTR strCLSID)
	{
		LPOLESTR pOleStr = NULL;
		HRESULT hr = ::StringFromCLSID(riid,&pOleStr);
		if(FAILED(hr))
			return false;
		int bytesConv = ::WideCharToMultiByte(CP_ACP,0,pOleStr,wcslen(pOleStr),strCLSID,MAX_PATH,NULL,NULL);
		CoTaskMemFree(pOleStr);
		strCLSID [ bytesConv ] = '\0';
		if(!bytesConv)
		{
			return false;
		}
		return true;
	}
public:
	bool RegisterObject(REFIID riid,LPCSTR LibId,LPCSTR ClassId)
	{
		char strCLSID [ MAX_PATH ];
		char Buffer [ MAX_PATH ];
		
		if(!strlen(ClassId))
			return false;

		if(!StrFromCLSID(riid,strCLSID))
			return false;
		
		if(!strlen(LibId) && strlen(ClassId))
			sprintf(Buffer,"%s.%s\\CLSID",ClassId,ClassId);
		else
			sprintf(Buffer,"%s.%s\\CLSID",LibId,ClassId);

		BOOL result;
		result = SetInRegistry(HKEY_CLASSES_ROOT,Buffer,"",strCLSID);
		if(!result)
			return false;
		sprintf(Buffer,"CLSID\\%s",strCLSID);
		char Class [ MAX_PATH ];
		sprintf(Class,"%s Class",ClassId);
		if(!SetInRegistry(HKEY_CLASSES_ROOT,Buffer,"",Class))
			return false;
		sprintf(Class,"%s.%s",LibId,ClassId);
		strcat(Buffer,"\\ProgId");

		return SetInRegistry(HKEY_CLASSES_ROOT,Buffer,"",Class) ? true:false;
	}

	bool UnRegisterObject(REFIID riid,LPCSTR LibId,LPCSTR ClassId)
	{
		char strCLSID [ MAX_PATH ];
		char Buffer [ MAX_PATH ];
		if(!StrFromCLSID(riid,strCLSID))
			return false;
		sprintf(Buffer,"%s.%s\\CLSID",LibId,ClassId);
		if(!DelFromRegistry(HKEY_CLASSES_ROOT,Buffer))
			return false;
		sprintf(Buffer,"%s.%s",LibId,ClassId);
		if(!DelFromRegistry(HKEY_CLASSES_ROOT,Buffer))
			return false;
		sprintf(Buffer,"CLSID\\%s\\ProgId",strCLSID);
		if(!DelFromRegistry(HKEY_CLASSES_ROOT,Buffer))
			return false;
		sprintf(Buffer,"CLSID\\%s",strCLSID);
		return DelFromRegistry(HKEY_CLASSES_ROOT,Buffer) ? true:false;
	}
};

class CDllRegistrar : public CRegistrar
{
public:
	bool RegisterObject(REFIID riid,LPCSTR LibId,LPCSTR ClassId,LPCSTR Path)
	{
		if(! CRegistrar::RegisterObject(riid,LibId,ClassId))
			return false;

		char strCLSID [ MAX_PATH ];
		char Buffer [ MAX_PATH ];
		if(!StrFromCLSID(riid,strCLSID))
			return false;
		sprintf(Buffer,"CLSID\\%s\\InProcServer32",strCLSID);
		return SetInRegistry(HKEY_CLASSES_ROOT,Buffer,"",Path) ? true:false;
	}

	bool UnRegisterObject(REFIID riid,LPCSTR LibId,LPCSTR ClassId)
	{
		char strCLSID [ MAX_PATH ];
		char Buffer [ MAX_PATH ];
		if(!StrFromCLSID(riid,strCLSID))
			return false;
		sprintf(Buffer,"CLSID\\%s\\InProcServer32",strCLSID);
		if(!DelFromRegistry(HKEY_CLASSES_ROOT,Buffer))
			return false;
		return CRegistrar::UnRegisterObject(riid,LibId,ClassId);
	}

};

#endif

#if 0

#include <windows.h>
#include <stdio.h>

#pragma comment(lib, "advapi32.lib")

// Define application constants.
#if defined(_WIN64)

#define VIEW_DATA L"Hello! 64-bit World"
#define ALT_VIEW_DATA L"Hello! 32-bit World"
#define CROSS_ACCESS KEY_WOW64_32KEY

#else

#define VIEW_DATA L"Hello! 32-bit World"
#define ALT_VIEW_DATA L"Hello! 64-bit World"
#define CROSS_ACCESS KEY_WOW64_64KEY

#endif

// Create a registry key and set its value.
// Return TRUE if the function succeeds, FALSE if it fails.
BOOL
CreateRegistryKeyValue(
    HKEY hKeyParent,
    PWCHAR KeyName,
    REGSAM rsAccessMask,
    REGSAM rsSamViewFlag,
    PBYTE pValue,
    DWORD dwValueSize
)
{
    DWORD dwDisposition;
    HKEY  hKey;
    DWORD dwRet;

    dwRet =
        RegCreateKeyEx(
            hKeyParent,
            KeyName,
            0,
            NULL,
            REG_OPTION_NON_VOLATILE,
            rsAccessMask | rsSamViewFlag,
            NULL,
            &hKey,
            &dwDisposition);

    if (dwRet != ERROR_SUCCESS)
    {
        printf("Error opening or creating key.\n");
        return FALSE;
    }

    // Attempt to set the value of the key.
    // If the call fails, close the key and return.
    if (ERROR_SUCCESS !=
        RegSetValueEx(
            hKey,
            NULL,
            0,
            REG_SZ,
            pValue,
            dwValueSize))
    {
        printf("Could not set registry value.\n");
        RegCloseKey(hKey);
        return FALSE;
    }

    RegCloseKey(hKey);
    return TRUE;
}

// Access a registry key and print its value.
// Return TRUE if the function succeeds, FALSE if it fails.
BOOL
AccessRegistryKeyValue(
    HKEY hKeyParent,
    PWCHAR KeyName,
    REGSAM rsAccessMask,
    REGSAM rsSamViewFlag
)
{
    HKEY hKey;
    WCHAR Buffer[MAX_PATH];
    DWORD dwSize = sizeof(Buffer);
    DWORD dwType;
    DWORD dwRet;

    dwRet =
        RegOpenKeyEx(
            hKeyParent,
            KeyName,
            0,
            rsAccessMask | rsSamViewFlag,
            &hKey);

    if (dwRet != ERROR_SUCCESS)
    {
        printf("Error opening key!\n");
        return FALSE;
    }

    if (ERROR_SUCCESS !=
        RegQueryValueEx(
            hKey,
            NULL,
            0,
            &dwType,
            (PBYTE)Buffer,
            &dwSize))
    {
        printf("Could not read registry value.\n");
        RegCloseKey(hKey);
        return FALSE;
    }

    if (rsSamViewFlag != 0)
    {
        printf("Alternate view:   %S\n", Buffer);
    }
    else
    {
        printf("Default view:     %S\n", Buffer);
    }

    RegCloseKey(hKey);
    return TRUE;
}

int
main()
{
    BOOL Res;

    // Define the list of keys to work with.
    typedef struct {
        HKEY hkRoot;
        LPWSTR szRootName;
        LPWSTR szName;
    }KEYDATA;

    KEYDATA Keys[] =
    {
        { HKEY_LOCAL_MACHINE, L"HKLM", L"Software\\Hello World" },
        { HKEY_CLASSES_ROOT,  L"HKCR", L"Hello" },
        { HKEY_CLASSES_ROOT,  L"HKCR", L"CLSID\\{00000000-0000-0000-0000-ABCD00000000}" },
        { HKEY_CLASSES_ROOT,  L"HKCR", L"CLSID\\{00000000-0000-0000-0000-ABCD00000000}\\InprocServer32" },
        { HKEY_CLASSES_ROOT,  L"HKCR", L"CLSID\\{00000000-0000-0000-0000-ABCD00000000}\\LocalServer32" }
    };

    // Now create the keys.
    for (int i = 0; i < _countof(Keys); i++)
    {
        // Create the keys in the alternate view of the registry.
        Res =
            CreateRegistryKeyValue(
                Keys[i].hkRoot,
                Keys[i].szName,
                KEY_READ | KEY_WRITE,
                CROSS_ACCESS,
                (PBYTE)ALT_VIEW_DATA,
                sizeof(ALT_VIEW_DATA));
        if (Res == FALSE)
        {
            printf("Could not create keys in alternate view of the registry.\n");
            return 1;
        }

        // Create the keys in the default view of the registry.
        Res =
            CreateRegistryKeyValue(
                Keys[i].hkRoot,
                Keys[i].szName,
                KEY_READ | KEY_WRITE,
                0,
                (PBYTE)VIEW_DATA,
                sizeof(VIEW_DATA));
        if (Res == FALSE)
        {
            printf("Could not create keys in default view of the registry.\n");
            return 1;
        }
    }

    // Access the registry and print key values.
    printf("Application string: %S\n", VIEW_DATA);

    for (int i = 0; i < _countof(Keys); i++)
    {
        printf("%S\\%S\n", Keys[i].szRootName, Keys[i].szName);
        Res =
            AccessRegistryKeyValue(
                Keys[i].hkRoot,
                Keys[i].szName,
                KEY_READ,
                0);
        if (Res == FALSE)
        {
            printf("Unable to access default view of registry.\n");
            return 1;
        }

        // Calls with CROSS_ACCESS explicitly access the alternate registry view.
        Res =
            AccessRegistryKeyValue(
                Keys[i].hkRoot,
                Keys[i].szName,
                KEY_READ,
                CROSS_ACCESS);
        if (Res == FALSE)
        {
            printf("Unable to access alternate view of registry.\n");
            return 1;
        }
    }
    return 0;
}

#endif