#ifndef _visualizerfactory
#define _visualizerfactory
#include <list>

class VisualizerObjectPool;
class VisualizeTestCommandBase;
class VisualizeRegistrationCommand;
class CollisionVolumeBSphere;
class Vect;
class Matrix;
class VolumeShow;

class VisualizerFactory
{
public:
	 VisualizeRegistrationCommand* CreateRegistrationCommand(const Matrix& W, const Vect& C, const VolumeShow* VS);

	 void RecycleCommand(VisualizeRegistrationCommand* v);

	//constructors
	VisualizerFactory();
	VisualizerFactory(const VisualizerFactory& s) = delete;
	VisualizerFactory operator=(const VisualizerFactory& s) = delete;
	~VisualizerFactory();

private:
	VisualizerObjectPool* m_VisualizerObjectPool;

	VisualizeRegistrationCommand* m_activeRegistrationCommand;

};
#endif _visualizerfactory