#ifndef _sceneregistrationbroker
#define _sceneregistrationbroker
#include <list>

class CommandBase;

class SceneRegistrationBroker
{
	using CommandList = std::list<CommandBase*>;

public: // ---- > ENGINE METHODS
	void ExecuteCommands();
	void AddCommand(CommandBase* command);

public:
	SceneRegistrationBroker() = default;
	SceneRegistrationBroker(const SceneRegistrationBroker&) = delete;
	SceneRegistrationBroker operator=(SceneRegistrationBroker&) = delete;
	~SceneRegistrationBroker() = default;

private:
	CommandList m_CommandList;
};

#endif _sceneregistrationbroker
#pragma once
