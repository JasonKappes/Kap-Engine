#ifndef _visualizeregistrationcommand
#define _visualizeregistrationcommand
#include "VisualizeTestCommandBase.h"

class CollisionVolumeBSphere;
class VolumeShow;

class VisualizeRegistrationCommand : public VisualizeTestCommandBase
{
public:
	VisualizeRegistrationCommand();
	VisualizeRegistrationCommand(const VisualizeRegistrationCommand&) = delete;
	VisualizeRegistrationCommand operator=(const VisualizeRegistrationCommand&) = delete;
	~VisualizeRegistrationCommand() = default;

	void Initialize(const Matrix& world, const Vect& color, const VolumeShow* volumeshow);
	void Execute() override;

private:
	const VolumeShow* m_renderVolume;
	Matrix m_world;
	Vect m_color;
};
#endif _visualizeregistrationcommand
#pragma once
