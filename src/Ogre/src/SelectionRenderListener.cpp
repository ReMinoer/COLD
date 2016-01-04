#include <stdafx.h>

#include <Ogre/SelectionRenderListener.h>
#include <Ogre/MaterialSwitcher.h>

namespace Ogre
{

	SelectionRenderListener::SelectionRenderListener(MaterialSwitcher *switcher) : mMaterialListener(switcher)
	{
	}

	SelectionRenderListener::~SelectionRenderListener()
	{
		delete mMaterialListener;
	}

	void SelectionRenderListener::preRenderTargetUpdate(const RenderTargetEvent &evt)
	{
		MaterialManager::getSingleton().addListener(mMaterialListener);
	}

	void SelectionRenderListener::postRenderTargetUpdate(const RenderTargetEvent &evt)
	{
		MaterialManager::getSingleton().removeListener(mMaterialListener);
	}
}
