#include "VisualizerFactory.h"
#include "VisualizerObjectPool.h"
#include "VisualizeTestCommandBase.h"
#include "VisualizeRegistrationCommand.h"
#include "Bullet.h"
#include <algorithm>

VisualizerFactory::VisualizerFactory() : m_VisualizerObjectPool(new VisualizerObjectPool), m_activeRegistrationCommand(nullptr) {}

VisualizeRegistrationCommand* VisualizerFactory::CreateRegistrationCommand(const Matrix& t_world, const Vect& t_color, const VolumeShow* t_vs)
{
	this->m_activeRegistrationCommand = this->m_VisualizerObjectPool->GetRegistrationCommand();
	this->m_activeRegistrationCommand->Initialize(t_world, t_color, t_vs);
	return this->m_activeRegistrationCommand;
}

void VisualizerFactory::RecycleCommand(VisualizeRegistrationCommand* t_command)
{
	m_VisualizerObjectPool->ReturnRegistrationCommand(t_command);
}

VisualizerFactory::~VisualizerFactory()
{
	delete this->m_VisualizerObjectPool;
}


