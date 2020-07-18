#include "SceneRegistrationBroker.h"
#include "CommandBase.h"

void SceneRegistrationBroker::AddCommand(CommandBase* t_command)
{
	this->m_CommandList.push_back(t_command);
}

void SceneRegistrationBroker::ExecuteCommands()
{
	std::list<CommandBase*>::iterator it;

	for (it = this->m_CommandList.begin(); it != this->m_CommandList.end();)
	{
		(*it)->Execute();
		++it;
		this->m_CommandList.pop_front(); //remove commands after they are executed
	}
}