#include "SceneChangeCommand.h"
#include "SceneManagerAttorney.h"

SceneChangeCommand::SceneChangeCommand() : m_scene(nullptr) {}

void SceneChangeCommand::SetScene(Scene* t_scene) { this->m_scene = t_scene; }

void SceneChangeCommand::Execute() 
{ 
	SceneManagerAttorney::Change::ChangeScene(this->m_scene); }
