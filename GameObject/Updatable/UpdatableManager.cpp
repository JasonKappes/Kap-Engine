#include "UpdatableManager.h"
#include "Updatable.h"
#include "UpdatableAttorney.h"
#include <DebugOut.h>

void UpdatableManager::ProcessUpdates() const
{
	UpdatableManager::StorageList::const_iterator it = this->m_storageList.begin();
	for (it = this->m_storageList.begin(); it != this->m_storageList.end(); ++it)
	{
		UpdatableAttorney::GameLoop::Update(*it);
	}
}

void UpdatableManager::ProcessLateUpdates() const
{
	UpdatableManager::StorageList::const_iterator it = this->m_storageList.begin();
	for (it = this->m_storageList.begin(); it != this->m_storageList.end(); ++it)
	{
		UpdatableAttorney::GameLoop::LateUpdate(*it);
	}
}

void UpdatableManager::Register(Updatable* t_updatable, StorageListRef& t_iterator)
{
	t_iterator = this->m_storageList.insert(this->m_storageList.end(), t_updatable);
	DebugMsg::out("\n NEW Updatable registered, there are %d updatables ", this->m_storageList.size());

}

void UpdatableManager::Deregister(UpdatableManager::StorageListRef& t_iterator)
{
	this->m_storageList.erase(t_iterator);
	DebugMsg::out("\n Updatable DEREGISTERED, there are %d updatables ", this->m_storageList.size());
}

UpdatableManager::~UpdatableManager()
{
	this->m_storageList.clear();
	DebugMsg::out("\n UPDATABLE MANAGER Destructor: there are %d updatables ", this->m_storageList.size());
}
