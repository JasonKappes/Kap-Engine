#include "SelectionTestCommand.h"
#include "Selectable.h"
#include "SelectionVolume.h"
#include "Touchable.h"
#include "VisualizerAttorney.h"
#include "Transform.h"

SelectionTestCommand::SelectionTestCommand(Selectable* t_s)
{
	m_selectable = t_s;
}

void SelectionTestCommand::Execute(Touchable* clickobj)
{
	if (m_selectable->GetSelectionVolume().MouseSelectionIntersection() == true)
	{
		//dispatch
		clickobj->Selection(this->m_selectable);
	}

}