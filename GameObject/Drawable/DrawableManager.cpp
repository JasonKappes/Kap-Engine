#include "DrawableManager.h"
#include "DrawableAttorney.h"
#include "Drawable.h"
#include <iostream>
#include <DebugOut.h>

void DrawableManager::ProcessElements() const
{
	std::list<Drawable*>::const_iterator it;

	for (it = this->m_storageList.begin(); it != this->m_storageList.end(); ++it)
	{
		DrawableAttorney::GameLoop::Draw(*it);
	}

	for (it = this->m_storageList.begin(); it != this->m_storageList.end(); ++it)
	{
		DrawableAttorney::GameLoop::Draw2D(*it);
	}
}

void DrawableManager::Register(Drawable* t_drawable, StorageListRef& t_iterator)
{
	t_iterator = this->m_storageList.insert(this->m_storageList.end(), t_drawable);
	DebugMsg::out("\n NEW Drawable registered, there are %d drawables ", this->m_storageList.size());
}

void DrawableManager::Deregister(DrawableManager::StorageListRef& t_iterator)
{
	this->m_storageList.erase(t_iterator);
	DebugMsg::out("\n Drawable DEREGISTERED, there are %d drawables ", this->m_storageList.size());
}

DrawableManager::~DrawableManager() 
{
	this->m_storageList.clear();
	DebugMsg::out("\n DRAWABLE MANAGER Destructor: there are %d drawables ", this->m_storageList.size());
}

