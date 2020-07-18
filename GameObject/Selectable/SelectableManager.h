#ifndef _selectablemanager
#define _selectablemanager
#include <vector>
#include <list>
#include "SelectionTestCommand.h"

class Selectable;
class Touchable;

class SelectableManager
{
public:
    using SelectableColl = std::list<SelectionTestCommand*>;
    using SelectableCollRef = SelectableColl::iterator;

public:
    SelectableManager() = default;
    SelectableManager(const SelectableManager&) = delete;
    SelectableManager operator=(const SelectableManager&) = delete;
    ~SelectableManager();

    void Register(Selectable* up, SelectableCollRef&);
    void Deregister(SelectableCollRef&);

public:

    void ProcessSelections(Touchable* clickerobj)
    {
        for (SelectionTestCommand* command : this->m_selectableColl)
        {
             command->Execute(clickerobj);
        }
    }

private:
    SelectableColl m_selectableColl;
};

#endif _selectablemanager
#pragma once
