#include "CollidableManager.h"
#include "CollisionTestCommandBase.h"
#include "CollidableGroup.h"

CollidableManager::PWTypeID CollidableManager::TypeIDNextNumber = 0;

void CollidableManager::SetGroupForTypeID(CollidableManager::PWTypeID ind)
{
	if (this->m_CollidableGroupCol[ind] == nullptr) {
		this->m_CollidableGroupCol[ind] = new CollidableGroup();
		DebugMsg::out(" \n COLLIDABLE MANAGER MADE ");
	}
}

void CollidableManager::ProcessCollisions() const
{

	for (int x = 0; x < this->TypeIDNextNumber; ++x)
	{
		m_CollidableGroupCol[x]->CalculateGroupAABB();	
	}

	for (CollisionTestCommands::const_iterator it2 = this->m_colTestCommands.begin();
		it2 != this->m_colTestCommands.end(); it2++)
	{
		(*it2)->Execute();
	}
}

void CollidableManager::VisualizeAllVolumes()
{
	for (int x = 0; x < this->TypeIDNextNumber; ++x)
	{
		m_CollidableGroupCol[x]->VisualizeCollidableMembers();
	}
}

CollidableManager::~CollidableManager()
{
	CollidableManager::CollidableGroupCollection::iterator colGroup_it;
	CollidableManager::CollisionTestCommands::iterator colCommands_it;

	for (colGroup_it = this->m_CollidableGroupCol.begin(); colGroup_it != this->m_CollidableGroupCol.end();)
	{
		delete (*colGroup_it++);
	}
	this->m_CollidableGroupCol.clear();
	DebugMsg::out(" \n COLLIDABLE MANAGER DESTRUCTOR  ----> collidable groups left: %d ", this->m_CollidableGroupCol.size());

	for (colCommands_it = this->m_colTestCommands.begin(); colCommands_it != this->m_colTestCommands.end();)
	{
		delete (*colCommands_it++);
	}
	this->m_colTestCommands.clear();
	DebugMsg::out(" \n COLLIDABLE MANAGER DESTRUCTOR  ----> collision commands left: %d ", this->m_CollidableGroupCol.size());
}

CollidableGroup* CollidableManager::GetCollisionGroup(CollidableManager::PWTypeID t_CollidableGroupId)
{
	return this->m_CollidableGroupCol[t_CollidableGroupId];
}

