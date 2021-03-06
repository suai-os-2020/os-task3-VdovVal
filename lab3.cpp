#include <windows.h>
#include <iostream>
#include "lab3.h"

using namespace std;

#define THREAD_COUNT 11
#define SEMAPHORE_COUNT 3

DWORD ThreadID;
HANDLE Threads[THREAD_COUNT];
HANDLE sem_B, sem_C, sem_D, inter, cont;
HANDLE Mutex_s;

DWORD WINAPI thread_a(LPVOID);
DWORD WINAPI thread_b(LPVOID);
DWORD WINAPI thread_c(LPVOID);
DWORD WINAPI thread_d(LPVOID);
DWORD WINAPI thread_e(LPVOID);
DWORD WINAPI thread_f(LPVOID);
DWORD WINAPI thread_g(LPVOID);
DWORD WINAPI thread_h(LPVOID);
DWORD WINAPI thread_i(LPVOID);
DWORD WINAPI thread_k(LPVOID);
DWORD WINAPI thread_m(LPVOID);


DWORD WINAPI thread_d(LPVOID lpParam)
{
	// step 1 
	// start a
	Threads[0] = CreateThread(NULL, 0, thread_a, NULL, 0, &ThreadID);
	if (Threads[0] == NULL) {
		return GetLastError();
	}

	// start b
	Threads[1] = CreateThread(NULL, 0, thread_b, NULL, 0, &ThreadID);
	if (Threads[1] == NULL) {
		return GetLastError();
	}

	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(Mutex_s, INFINITE);
		cout << "d" << flush;
		computation();
		ReleaseMutex(Mutex_s);
	}

	// wait a
	WaitForSingleObject(Threads[0], INFINITE);
	// wait b
	WaitForSingleObject(inter, INFINITE);


	// step 2 

	// start c
	Threads[2] = CreateThread(NULL, 0, thread_c, NULL, 0, &ThreadID);
	if (Threads[2] == NULL) {
		return GetLastError();
	}
	// continue b
	ReleaseSemaphore(cont, 1, NULL);

	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(sem_D, INFINITE);
		WaitForSingleObject(Mutex_s, INFINITE);
		cout << "d" << flush;
		computation();
		ReleaseMutex(Mutex_s);
		ReleaseSemaphore(sem_B, 1, NULL);
	}

	// wait b
	WaitForSingleObject(Threads[1], INFINITE);
	// wait c
	WaitForSingleObject(Threads[2], INFINITE);

	// step 3 

	// start h
	Threads[7] = CreateThread(NULL, 0, thread_h, NULL, 0, &ThreadID);
	if (Threads[7] == NULL) {
		return GetLastError();
	}

	// start f
	Threads[6] = CreateThread(NULL, 0, thread_f, NULL, 0, &ThreadID);
	if (Threads[6] == NULL) {
		return GetLastError();
	}

	// start e
	Threads[4] = CreateThread(NULL, 0, thread_e, NULL, 0, &ThreadID);
	if (Threads[4] == NULL) {
		return GetLastError();
	}

	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(Mutex_s, INFINITE);
		cout << "d" << flush;
		computation();
		ReleaseMutex(Mutex_s);
	}

	// wait h
	WaitForSingleObject(inter, INFINITE);
	// wait f
	WaitForSingleObject(inter, INFINITE);
	// wait e
	WaitForSingleObject(Threads[4], INFINITE);

	// step 4 


	// start g
	Threads[5] = CreateThread(NULL, 0, thread_g, NULL, 0, &ThreadID);
	if (Threads[5] == NULL) {
		return GetLastError();
	}

	// wait g 
	WaitForSingleObject(Threads[5], INFINITE);

	return 0;
}

DWORD WINAPI thread_b(LPVOID lpParam)
{
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(Mutex_s, INFINITE);
		cout << "b" << flush;
		computation();
		ReleaseMutex(Mutex_s);
	}
	//2
	//interval 
	ReleaseSemaphore(inter, 1, NULL);
	//continue
	WaitForSingleObject(cont, INFINITE);

	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(sem_B, INFINITE);
		WaitForSingleObject(Mutex_s, INFINITE);
		cout << "b" << flush;
		computation();
		ReleaseMutex(Mutex_s);
		ReleaseSemaphore(sem_C, 1, NULL);
	}
	return 0;
}


DWORD WINAPI thread_c(LPVOID lpParam)
{
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(sem_C, INFINITE);
		WaitForSingleObject(Mutex_s, INFINITE);
		cout << "c" << flush;
		computation();
		ReleaseMutex(Mutex_s);
		ReleaseSemaphore(sem_D, 1, NULL);
	}

	return 0;
}

DWORD WINAPI thread_a(LPVOID lpParam)
{
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(Mutex_s, INFINITE);
		cout << "a" << flush;
		computation();
		ReleaseMutex(Mutex_s);
	}

	return 0;
}

DWORD WINAPI thread_e(LPVOID lpParam)
{
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(Mutex_s, INFINITE);
		cout << "e" << flush;
		computation();
		ReleaseMutex(Mutex_s);
	}

	return 0;
}


DWORD WINAPI thread_h(LPVOID lpParam)
{
	//3
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(Mutex_s, INFINITE);
		cout << "h" << flush;
		computation();
		ReleaseMutex(Mutex_s);
	}

	//4
	//interval 
	ReleaseSemaphore(inter, 1, NULL);
	//continue
	WaitForSingleObject(cont, INFINITE);

	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(Mutex_s, INFINITE);
		cout << "h" << flush;
		computation();
		ReleaseMutex(Mutex_s);
	}

	//5
	//interval 
	ReleaseSemaphore(inter, 1, NULL);
	//continue
	WaitForSingleObject(cont, INFINITE);

	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(Mutex_s, INFINITE);
		cout << "h" << flush;
		computation();
		ReleaseMutex(Mutex_s);
	}
	return 0;
}

DWORD WINAPI thread_f(LPVOID lpParam)
{
	//3
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(Mutex_s, INFINITE);
		cout << "f" << flush;
		computation();
		ReleaseMutex(Mutex_s);
	}

	//4
	//interval 
	ReleaseSemaphore(inter, 1, NULL);
	//continue
	WaitForSingleObject(cont, INFINITE);

	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(Mutex_s, INFINITE);
		cout << "f" << flush;
		computation();
		ReleaseMutex(Mutex_s);
	}

	return 0;
}

DWORD WINAPI thread_g(LPVOID lpParam)
{
	// continue f
	ReleaseSemaphore(cont, 1, NULL);
	// continue h
	ReleaseSemaphore(cont, 1, NULL);


	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(Mutex_s, INFINITE);
		cout << "g" << flush;
		computation();
		ReleaseMutex(Mutex_s);
	}

	// wait f 
	WaitForSingleObject(Threads[6], INFINITE);

	// wait h
	WaitForSingleObject(inter, INFINITE);


	// step 5 

	// continue h
	ReleaseSemaphore(cont, 1, NULL);


	// start i
	Threads[8] = CreateThread(NULL, 0, thread_i, NULL, 0, &ThreadID);
	if (Threads[8] == NULL) {
		return GetLastError();
	}

	// start k
	Threads[9] = CreateThread(NULL, 0, thread_k, NULL, 0, &ThreadID);
	if (Threads[9] == NULL) {
		return GetLastError();
	}

	// wait h
	WaitForSingleObject(Threads[7], INFINITE);
	// wait i
	WaitForSingleObject(Threads[8], INFINITE);

	// wait k
	WaitForSingleObject(inter, INFINITE);

	// step 6

	// start m
	Threads[10] = CreateThread(NULL, 0, thread_m, NULL, 0, &ThreadID);
	if (Threads[10] == NULL) {
		return GetLastError();
	}

	// continue k
	ReleaseSemaphore(cont, 1, NULL);


	// wait m
	WaitForSingleObject(Threads[10], INFINITE);
	// wait k
	WaitForSingleObject(Threads[9], INFINITE);

	return 0;
}

DWORD WINAPI thread_i(LPVOID lpParam)
{
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(Mutex_s, INFINITE);
		cout << "i" << flush;
		computation();
		ReleaseMutex(Mutex_s);
	}

	return 0;
}

DWORD WINAPI thread_k(LPVOID lpParam)
{
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(Mutex_s, INFINITE);
		cout << "k" << flush;
		computation();
		ReleaseMutex(Mutex_s);
	}

	//6
	//interval 
	ReleaseSemaphore(inter, 1, NULL);
	//continue
	WaitForSingleObject(cont, INFINITE);

	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(Mutex_s, INFINITE);
		cout << "k" << flush;
		computation();
		ReleaseMutex(Mutex_s);
	}

	return 0;
}

DWORD WINAPI thread_m(LPVOID lpParam)
{
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(Mutex_s, INFINITE);
		cout << "m" << flush;
		computation();
		ReleaseMutex(Mutex_s);
	}

	return 0;
}



unsigned int lab3_thread_graph_id()
{
	return 3;
}

const char* lab3_unsynchronized_threads()
{
	return "defh";
}

const char* lab3_sequential_threads()
{
	return "bcd";
}

int lab3_init()
{
	Mutex_s = CreateMutex(NULL, 0, NULL);
	if (Mutex_s == NULL) {
		cout << "Create_Mutex error: " << GetLastError();
		return 1;
	}

	inter = CreateSemaphore(NULL, 0, 4, NULL);
	if (inter == NULL) {
		cout << "Create_Semaphore error: " << GetLastError();
		return 1;
	}

	cont = CreateSemaphore(NULL, 0, 4, NULL);
	if (cont == NULL) {
		cout << "Create_Semaphore error: " << GetLastError();
		return 1;
	}

	sem_B = CreateSemaphore(NULL, 1, 1, NULL);
	if (sem_B == NULL) {
		cout << "Create_Semaphore error: " << GetLastError();
		return 1;
	}
	sem_C = CreateSemaphore(NULL, 0, 1, NULL);
	if (sem_C == NULL) {
		cout << "Create_Semaphore error: " << GetLastError();
		return 1;
	}
	sem_D = CreateSemaphore(NULL, 0, 1, NULL);
	if (sem_D == NULL) {
		cout << "Create_Semaphore error: " << GetLastError();
		return 1;
	}

	// start d
	Threads[3] = CreateThread(NULL, 0, thread_d, NULL, 0, &ThreadID);
	if (Threads[3] == NULL) {
		return GetLastError();
	}
	// wait d
	WaitForSingleObject(Threads[3], INFINITE);
	// close d
	CloseHandle(Threads[3]);

	CloseHandle(Mutex_s);

	// interval -----close //
	CloseHandle(cont);
	// continue-----close //
	CloseHandle(inter);

	CloseHandle(sem_B);
	CloseHandle(sem_C);
	CloseHandle(sem_D);



	return 0;
}
