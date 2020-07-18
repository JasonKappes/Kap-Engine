#include "Visualizer.h"
#include "VisualizeRegistrationCommand.h"
#include "VisualizerFactory.h"
#include "VisualizeTestCommandBase.h"
#include "ShaderManager.h"
#include "ModelManager.h"
#include "CollisionVolumeBSphere.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeOBB.h"
#include "GraphicsObject_WireframeConstantColor.h"
#include "SceneManager.h"
#include <DebugOut.h>
#include "Color.h"
#include "AABBRender.h"
#include "OBBRender.h"
#include "BSphereRender.h"

Vect Visualizer::DEFAULT_COLOR = Color::White;

Visualizer::Visualizer()
{
	Vect Blue(0.0f, 0.0f, 1.0f, 1.0f);

	this->m_WFUnitSphere = new GraphicsObject_WireframeConstantColor(ModelManager::Get(Model::PreMadeModels::UnitSphere), 
		ShaderManager::Get("colorConstantRender"), Blue);

	this->m_WFUnitBox = new GraphicsObject_WireframeConstantColor(ModelManager::Get(Model::PreMadeModels::UnitBox_WF),
		ShaderManager::Get("colorConstantRender"), Blue);

	this->m_VisualizerFactory	= new VisualizerFactory();
	this->m_aabbRender			= new AABBRender();
	this->m_obbRender			= new OBBRender();
	this->m_bsphereRender		= new BSphereRender();
}

void Visualizer::VisualizeAll() { Instance().privVisualizeAll(); }

void Visualizer::privVisualizeAll()
{
	for (it = this->m_VisualizeColl.begin(); it != this->m_VisualizeColl.end();)
	{
		(*it)->Execute();
		this->m_VisualizerFactory->RecycleCommand(*it);
		this->m_VisualizeColl.erase(it++); //remove commands after they are executed
	}
}

void Visualizer::ShowAABB(const CollisionVolumeAABB& S, const Vect& col)
{
	Instance().privShowAABB(S, col);
}

void Visualizer::RenderAABB(Matrix& S, const Vect& col)
{
	Instance().privRenderAABB(S, col);
}

void Visualizer::ShowOBB(const CollisionVolumeOBB& S, const Vect& col)
{
	Instance().privShowOBB(S, col);
}

void Visualizer::RenderOBB(Matrix& S, const Vect& col)
{
	Instance().privRenderOBB(S, col);
}

void Visualizer::privShowOBB(const CollisionVolumeOBB& obb, const Vect& t_color)
{
	Matrix t_world = Matrix(SCALE, obb.GetScale()) * Matrix(obb.GetWorld());

	//push back a command that will render an AABB+
	this->m_VisualizeColl.push_back(this->m_VisualizerFactory->CreateRegistrationCommand(t_world, t_color, m_obbRender));
}

void Visualizer::privRenderOBB(Matrix& t_world, const Vect& t_color)
{
	Instance().m_WFUnitBox->SetWorld(t_world);
	Instance().m_WFUnitBox->SetColor(t_color);
	Instance().m_WFUnitBox->Render(SceneManager::Get3DCamera());
}

void Visualizer::privShowAABB(const CollisionVolumeAABB& aabb , const Vect& t_color)
{
	Matrix t_world = Matrix(SCALE, aabb.GetScale()) * Matrix(IDENTITY) * Matrix(TRANS, aabb.GetTrans());

	//push back a command that will render an AABB+
	this->m_VisualizeColl.push_back(this->m_VisualizerFactory->CreateRegistrationCommand(t_world, t_color, m_aabbRender));
}

void Visualizer::privRenderAABB(Matrix& t_world, const Vect& t_color)
{
	Instance().m_WFUnitBox->SetWorld(t_world);
	Instance().m_WFUnitBox->SetColor(t_color);
	Instance().m_WFUnitBox->Render(SceneManager::Get3DCamera());
}

void Visualizer::RenderBSphere(Matrix& S, const Vect& col)
{
	Instance().m_WFUnitSphere->SetWorld(S);
	Instance().m_WFUnitSphere->SetColor(col);
	Instance().m_WFUnitSphere->Render(SceneManager::Get3DCamera());
}

void Visualizer::ShowBSphere(const CollisionVolumeBSphere& t_sphere, const Vect& t_color)
{
	Instance().privShowBSphere(t_sphere, t_color);
}

void Visualizer::ShowBSphere(Vect center, float radius, const Vect& t_color)
{
	Instance().privShowBSphere(center, radius, t_color);
}

void Visualizer::privShowBSphere(const CollisionVolumeBSphere& t_sphere, const Vect& t_color)
{
	Vect vBSSize = t_sphere.GetRadius() * Vect(1, 1, 1);
	Vect vBSPos = t_sphere.GetCenter();

	// Adjust the Bounding Sphere's position and scale to fit the Ship's center and scale
	Matrix t_world = Matrix(SCALE, vBSSize) * Matrix(TRANS, vBSPos);

	//push back a command that will render a BSPHERE
	this->m_VisualizeColl.push_back(this->m_VisualizerFactory->CreateRegistrationCommand(t_world, t_color, m_bsphereRender));
}

void Visualizer::privShowBSphere(Vect center, float radius, const Vect& t_color)
{
	// Adjust the Bounding Sphere's position and scale to fit the Ship's center and scale
	Matrix t_world = Matrix(SCALE, radius * Vect(1, 1, 1)) * Matrix(TRANS, center);

	//push back a command that will render a BSPHERE
	this->m_VisualizeColl.push_back(this->m_VisualizerFactory->CreateRegistrationCommand(t_world, t_color, m_bsphereRender));
}

void Visualizer::Delete() { Instance().privDelete(); }

void Visualizer::privDelete()
{
	DebugMsg::out(" \n Visualizer command size %d ", Instance().m_VisualizeColl.size());
	for (it = this->m_VisualizeColl.begin(); it != this->m_VisualizeColl.end();)
	{
		this->m_VisualizeColl.erase(it++); //remove commands after they are executed
	}
	DebugMsg::out(" \n Visualizer size %d ", this->m_VisualizeColl.size());

	delete this->m_WFUnitSphere;
	delete this->m_WFUnitBox;
	delete this->m_VisualizerFactory;
	delete pInstance;
}

Visualizer* Visualizer::pInstance = nullptr;

Visualizer::~Visualizer() 
{ 
	delete this->m_aabbRender;
	delete this->m_bsphereRender;
	delete this->m_obbRender;
	pInstance = nullptr; 
	DebugMsg::out("\n VISUALIZER destructor");
}

