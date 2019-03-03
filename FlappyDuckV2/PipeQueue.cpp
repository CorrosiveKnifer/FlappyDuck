//Local include:
#include "PipeQueue.h"
#include "pipes.h"

PipeQueue::PipeQueue()
	: m_waitingPipes(0)
{

}
PipeQueue::~PipeQueue()
{
	std::vector<Pipes*>::iterator iter = m_queue.begin();
	while (iter != m_queue.end())
	{
		delete *iter;
		iter++;
	}
	m_queue.clear();
}

bool 
PipeQueue::Initialise()
{
	return true;
}

void 
PipeQueue::Push_to_back(Pipes* p)
{
	ptrdiff_t pos = std::find(m_queue.begin(), m_queue.end(), p) - m_queue.begin();
	if (pos >= m_queue.size())
	{
		m_queue.push_back(p);
		m_waitingPipes++;
	}
	else
	{
		//Contains
		auto it = m_queue.begin() + pos;
		std::rotate(it, it + 1, m_queue.end());
	}
}

std::vector<Pipes*> 
PipeQueue::GetVector()
{
	return m_queue;
}

void
PipeQueue::ActivateNextPipe()
{
	for (auto& pipes : m_queue)
	{
		if (pipes->IsDead())
		{
			pipes->SetDead(false);
			m_waitingPipes--;
			return;
		}
	}
}

void 
PipeQueue::ResetPipe(Pipes* p, int x, int y)
{
	p->SetDead(true);
	p->BeenScored(false);
	p->SetPipeX(x);
	p->SetGapHeight(y);
	m_waitingPipes++;
}

bool 
PipeQueue::HasPipeWaiting()
{
	return m_waitingPipes > 0;
}