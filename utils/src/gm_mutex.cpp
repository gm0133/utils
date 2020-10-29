
#if defined(WIN32) || defined(_WIN32)
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <Objbase.h>
#else
#include <pthread.h>
#endif

#include <string>
#include <time.h>
using namespace std;

#include "../include/gm_mutex.h"
namespace gm {
/*
int QuickCreateFile(wstring filepath, int size)
{
	HANDLE hFile;
    hFile = CreateFile(
        filepath.c_str(),
        GENERIC_WRITE | GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL
        );
    if( hFile == INVALID_HANDLE_VALUE )
    {
        return -1;
    }
	int total = size;
    SetFilePointer(
        hFile,
        total,
        NULL,
        FILE_BEGIN
        );
    SetEndOfFile( hFile );
    CloseHandle( hFile );
	return 0;
}
*/
static string GenerateGUID()
{
	string result;
    char buf[64] = {0};
    GUID guid;
    CoInitialize(NULL);
    if (S_OK == ::CoCreateGuid(&guid))
    {
        _snprintf(buf, sizeof(buf),
            "{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
            guid.Data1,
            guid.Data2,
            guid.Data3,
            guid.Data4[0], guid.Data4[1],
            guid.Data4[2], guid.Data4[3],
            guid.Data4[4], guid.Data4[5],
            guid.Data4[6], guid.Data4[7]);
    }
    CoUninitialize();
	result = buf;
    return result;
}
/*
string GetCPUID()
{
	BYTE szCpu[16]  = { 0 };
    UINT uCpuID     = 0U;

	__asm{
			mov eax, 0
			cpuid
			mov dword ptr szCpu[0], ebx
			mov dword ptr szCpu[4], edx
			mov dword ptr szCpu[8], ecx
			mov eax, 1
			cpuid
			mov uCpuID, edx
    }
	
	string result;
	result.append((char*)szCpu, 16);
	return result;
}

int Random()
{
	srand(time(NULL));
	return rand();
}
*/
#if defined(WIN32) || defined(_WIN32)
Mutex::Mutex()
{
	_mutex = ::CreateMutexA(NULL, FALSE, GenerateGUID().c_str());
}

Mutex::~Mutex()
{
	if (_mutex) {
		::CloseHandle(_mutex);
		_mutex = NULL;
	}
}

bool		Mutex::lock()
{
	if (_mutex) {
		return WAIT_OBJECT_0 == ::WaitForSingleObject(_mutex, INFINITE);
	} else {
		return false;
	}
}

void		Mutex::unlock()
{
	if (_mutex) {
		::ReleaseMutex(_mutex);
	}
}
#else
Mutex::Mutex()
{
	pthread_mutex_init(&_mutex, NULL);
}

Mutex::~Mutex()
{
	pthread_mutex_destroy(&_mutex);
}

bool		Mutex::lock()
{
	pthread_mutex_lock(&_mutex);
}

void		Mutex::unlock()
{
	pthread_mutex_unlock(&_mutex);
}

#endif


}