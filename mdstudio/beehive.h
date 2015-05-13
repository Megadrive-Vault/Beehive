///////////////////////////////////////////////////////
// Beehive: A complete SEGA Mega Drive content tool
//
// (c) 2015 Matt Phillips, Big Evil Corporation
///////////////////////////////////////////////////////

#include <ion/core/bootstrap/Application.h>
#include <ion/core/Version.h>
#include <ion/core/debug/Debug.h>
#include <ion/core/thread/Thread.h>
#include <ion/core/time/Time.h>
#include <ion/io/Resource.h>
#include <ion/io/ResourceManager.h>
#include <ion/renderer/Material.h>

#include <vector>

#include "Project.h"

class BeehiveWxApp;

class Beehive : public ion::framework::Application
{
public:
	Beehive();
	virtual ~Beehive();

	virtual bool Initialise();
	virtual void Shutdown();
	virtual bool Update(float deltaTime);
	virtual void Render();

private:
	BeehiveWxApp* m_wxApp;
	Project* m_project;
};