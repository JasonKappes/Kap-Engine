#include "VisualizeRegistrationCommand.h"
#include "VisualizerAttorney.h"
#include "CollisionVolumeBSphere.h"
#include "VolumeShow.h"

VisualizeRegistrationCommand::VisualizeRegistrationCommand() : m_world(Matrix(IDENTITY)), m_color(Vect()) {}

void VisualizeRegistrationCommand::Initialize(const Matrix& t_world, const Vect& t_color, const VolumeShow* t_vs)
{
	this->m_world = t_world;
	this->m_color = t_color;
	this->m_renderVolume = t_vs;
}

void VisualizeRegistrationCommand::Execute()
{
	this->m_renderVolume->ShowCollisionVolume(m_world, m_color);
}
