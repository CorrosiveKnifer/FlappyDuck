//Local include:
#include "PipeQueue.h"
#include "pipes.h"

PipeQueue::PipeQueue()
{

}
PipeQueue::~PipeQueue()
{

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
			return;
		}
	}
}

void 
PipeQueue::Clear()
{
	m_queue.clear();
}