///////////////////////////////////////////////////////
// Beehive: A complete SEGA Mega Drive content tool
//
// (c) 2016 Matt Phillips, Big Evil Corporation
// http://www.bigevilcorporation.co.uk
// mattphillips@mail.com
// @big_evil_corp
//
// Licensed under GPLv3, see http://www.gnu.org/licenses/gpl-3.0.html
///////////////////////////////////////////////////////

#pragma once

#include <ion/core/Types.h>
#include <ion/beehive/GameObject.h>
#include <ion/beehive/SpriteSheet.h>

#include "UIBase.h"
#include "RenderResources.h"

class MainWindow;
class Project;

class GameObjectTypeDialog : public GameObjTypeDialogBase
{
public:
	GameObjectTypeDialog(MainWindow& mainWindow, Project& project, RenderResources& renderResources);

protected:
	virtual void OnToolGameObjAdd(wxCommandEvent& event);
	virtual void OnToolGameObjRemove(wxCommandEvent& event);
	virtual void OnToolVariableAdd(wxCommandEvent& event);
	virtual void OnToolVariableRemove(wxCommandEvent& event);
	virtual void OnToolOrderUp(wxCommandEvent& event);
	virtual void OnToolOrderDown(wxCommandEvent& event);
	virtual void OnSelectGameObjType(wxCommandEvent& event);
	virtual void OnSelectVariable(wxListEvent& event);
	virtual void OnBtnLoadSprite(wxCommandEvent& event);
	virtual void OnBtnApplyObjChanges(wxCommandEvent& event);
	virtual void OnBtnApplyVarChanges(wxCommandEvent& event);
	virtual void OnBtnImport(wxCommandEvent& event);
	virtual void OnBtnExport(wxCommandEvent& event);

private:
	void PopulateTypeList();
	void PopulateTypeFields(GameObjectType* gameObjType);
	void PopulateVarsList(GameObjectType* gameObjType);
	void PopulateVarsFields(GameObjectVariable* variable);

	MainWindow& m_mainWindow;
	Project& m_project;
	RenderResources& m_renderResources;
	GameObjectTypeId m_currentTypeId;
	GameObjectVariable* m_currentVariable;

	std::vector<std::pair<int, GameObjectTypeId>> m_gameObjIndexMap;
	std::vector<ActorId> m_actorCache;
};