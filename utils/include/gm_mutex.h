#ifndef _GM_MUTEX_H_
#define _GM_MUTEX_H_

namespace gm {
/*int QuickCreateFile(wstring filepath, int size);
string GenerateGUID();
string GetCPUID();

int  Random();
// */

//#ifndef HANDLE
//#define HANDLE			void*
//#endif

class Mutex
{
public:
	Mutex();
	~Mutex();

	bool	Lock();
	void	Unlock();

protected:
#if defined(WIN32) || defined(_WIN32)
	HANDLE	_mutex;
#else
	pthread_mutex_t _mutex
#endif
};

}

#endif