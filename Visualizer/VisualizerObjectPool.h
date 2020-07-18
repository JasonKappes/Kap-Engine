#ifndef _visualizerobjectpool
#define _visualizerobjectpool
#include <stack>

class VisualizeTestCommandBase;
class VisualizeRegistrationCommand;

class VisualizerObjectPool
{
public:
	VisualizerObjectPool() = default;
	VisualizerObjectPool(const VisualizerObjectPool&) = delete;
	VisualizerObjectPool& operator=(const VisualizerObjectPool&) = delete;
	~VisualizerObjectPool();

	VisualizeRegistrationCommand* GetRegistrationCommand();

	void ReturnRegistrationCommand(VisualizeRegistrationCommand*);

private:
	std::stack<VisualizeRegistrationCommand*> m_registrationCommands;
};
#endif _visualizerobjectpool
