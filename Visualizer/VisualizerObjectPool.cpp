#include "VisualizerObjectPool.h"
#include "VisualizeTestCommandBase.h"
#include "VisualizeRegistrationCommand.h"
#include "Bullet.h"

VisualizerObjectPool::~VisualizerObjectPool()
{
	// forcefully delete all recycled gameobjects

	DebugMsg::out("\nDeleting %d---- > Visualizer registration commands", this->m_registrationCommands.size());
	while (!this->m_registrationCommands.empty())
	{
		delete this->m_registrationCommands.top();
		this->m_registrationCommands.pop();
	}
	DebugMsg::out("\n Visualizer reg object pool size: %d---- > Visualizer registration commands .... ALL CLEAN \n", this->m_registrationCommands.size());
}

VisualizeRegistrationCommand* VisualizerObjectPool::GetRegistrationCommand()
{
	//DebugMsg::out("\n VisualizeObjectPool: Getting registration command ");
	VisualizeRegistrationCommand* t_registrationCommand;

	if (this->m_registrationCommands.empty())
	{
		t_registrationCommand = new VisualizeRegistrationCommand();
	}
	else
	{
		//DebugMsg::out("\n VisualizeRegistrationObjectPool size: ------- > %d ", this->m_registrationCommands.size());
		t_registrationCommand = this->m_registrationCommands.top();
		this->m_registrationCommands.pop();	// Remember: top doesn't pop and pop returns void...
	}

	return t_registrationCommand;
}

void VisualizerObjectPool::ReturnRegistrationCommand(VisualizeRegistrationCommand* t_command)
{
	//DebugMsg::out("\n Registration Command returned ");
	this->m_registrationCommands.push(t_command);
	//DebugMsg::out("\n Registration CommandObjectPool size: after recycle ------- > %d ", this->m_registrationCommands.size());
}