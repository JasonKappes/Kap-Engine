#include "SelectableManager.h"
#include "DebugOut.h"
#include "SelectionTestCommand.h"

void SelectableManager::Register(Selectable* t_selectable, SelectableCollRef& t_iterator)
{
	t_iterator = this->m_selectableColl.insert(this->m_selectableColl.end(), new SelectionTestCommand(t_selectable));
	DebugMsg::out("\n NEW Selectable registered, there are %d drawables ", this->m_selectableColl.size());
}

void SelectableManager::Deregister(SelectableCollRef& t_iterator)
{
	this->m_selectableColl.erase(t_iterator);
	DebugMsg::out("\n Selectable DEREGISTERED, there are %d selectables ", this->m_selectableColl.size());
}

SelectableManager::~SelectableManager()
{
	while (this->m_selectableColl.empty() == false)
	{
		delete this->m_selectableColl.front();
		this->m_selectableColl.pop_front();
	}

	this->m_selectableColl.clear();
	DebugMsg::out("\n SELECTABLE MANAGER Destructor: there are %d selectables ", this->m_selectableColl.size());
}