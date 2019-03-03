#pragma once

// Library includes:
#include <vector>

class Pipes;

class PipeQueue
{
	//Member methods:
public:
	PipeQueue();
	~PipeQueue();
	bool Initialise();
	void Push_to_back(Pipes* p);
	std::vector<Pipes*> GetVector();
	void ActivateNextPipe();
	void ResetPipe(Pipes* p, int x, int y);
	bool HasPipeWaiting();

protected:
private:
	//Member Data:
public:
protected:
private:
	int m_waitingPipes;
	std::vector<Pipes*> m_queue;
};