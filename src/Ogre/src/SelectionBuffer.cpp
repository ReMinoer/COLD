#include <stdafx.h>

#include <Ogre/MaterialSwitcher.h>
#include <Ogre/SelectionRenderListener.h>
#include <Ogre/SelectionBuffer.h>

namespace Ogre
{

	SelectionBuffer::SelectionBuffer(SceneManager *sceneMgr, Camera * camera, RenderTarget *renderTarget) : mSceneMgr(sceneMgr),
		mCamera(camera),
		mRenderTarget(renderTarget),
		mBuffer(0),
		mPixelBox(0)
	{
		//mCamera = mSceneMgr->getCamera("MainCamera");

		mMaterialSwitchListener = new MaterialSwitcher();

		mSelectionTargetListener = new SelectionRenderListener(mMaterialSwitchListener);

		unsigned int width = mRenderTarget->getWidth();
		unsigned int height = mRenderTarget->getHeight();

		mTexture = TextureManager::getSingleton().createManual("SelectionPassTex", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			TEX_TYPE_2D, width, height, 0, PF_R8G8B8, TU_RENDERTARGET);

		mRenderTexture = mTexture->getBuffer()->getRenderTarget();
		mRenderTexture->setAutoUpdated(false);
		mRenderTexture->setPriority(0);
		mRenderTexture->addViewport(mCamera);
		mRenderTexture->getViewport(0)->setOverlaysEnabled(false);
		mRenderTexture->getViewport(0)->setClearEveryFrame(true);
		mRenderTexture->addListener(mSelectionTargetListener);
		mRenderTexture->getViewport(0)->setMaterialScheme("aa");

		HardwarePixelBufferSharedPtr pixelBuffer = mTexture->getBuffer();
		size_t bufferSize = pixelBuffer->getSizeInBytes();

		mBuffer = new uint8[bufferSize];
		mPixelBox = new PixelBox(pixelBuffer->getWidth(), pixelBuffer->getHeight(), 
			pixelBuffer->getDepth(), pixelBuffer->getFormat(), mBuffer);

		CreateRTTOverlays();
	}

	SelectionBuffer::~SelectionBuffer()
	{
		TextureManager::getSingleton().unload("SelectionPassTex");
		delete mPixelBox;
		delete[] mBuffer;
		delete mSelectionTargetListener;
		delete mMaterialSwitchListener;
	}

	void SelectionBuffer::Update()
	{
		UpdateBufferSize();

		mMaterialSwitchListener->reset();
		mRenderTexture->update();

		mRenderTexture->copyContentsToMemory(*mPixelBox, RenderTarget::FB_FRONT);
	}

	void SelectionBuffer::UpdateBufferSize()
	{
		unsigned int width = mRenderTarget->getWidth();
		unsigned int height = mRenderTarget->getHeight();

		if(width != mRenderTexture->getWidth() || height != mRenderTexture->getHeight())
		{
			TextureManager::getSingleton().unload("SelectionPassTex");
			delete[] mBuffer;
			delete mPixelBox;

			mTexture = TextureManager::getSingleton().createManual("SelectionPassTex", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
				TEX_TYPE_2D, width, height, 0, PF_R8G8B8, TU_RENDERTARGET);

			mRenderTexture = mTexture->getBuffer()->getRenderTarget();
			mRenderTexture->setAutoUpdated(false);
			mRenderTexture->setPriority(0);
			mRenderTexture->addViewport(mCamera);
			mRenderTexture->getViewport(0)->setOverlaysEnabled(false);
			mRenderTexture->getViewport(0)->setClearEveryFrame(true);
			mRenderTexture->addListener(mSelectionTargetListener);
			mRenderTexture->getViewport(0)->setMaterialScheme("aa");

			HardwarePixelBufferSharedPtr pixelBuffer = mTexture->getBuffer();
			size_t bufferSize = pixelBuffer->getSizeInBytes();

			mBuffer = new uint8[bufferSize];
			mPixelBox = new PixelBox(pixelBuffer->getWidth(), pixelBuffer->getHeight(), 
				pixelBuffer->getDepth(), pixelBuffer->getFormat(), mBuffer);
		}
	}

	Entity *SelectionBuffer::OnSelectionClick(int x, int y)
	{
		Update();

		size_t posInStream = (mPixelBox->getWidth() * y) * 4;
		posInStream += x * 4;

		BGRA color(0);
		memcpy((void *)&color, mBuffer+posInStream, 4);
		ColourValue cv;
		cv.setAsARGB(color);
		cv.a = 1.0f;
		const String &entName = mMaterialSwitchListener->getEntityName(cv);
		if(entName.empty())
			return 0;
		else
			return mSceneMgr->getEntity(entName);
	}

	void SelectionBuffer::CreateRTTOverlays()
	{
		MaterialPtr baseWhite = MaterialManager::getSingleton().getDefaultSettings();
		MaterialPtr selectionBufferTexture = baseWhite->clone("SelectionDebugMaterial");
		TextureUnitState *textureUnit = selectionBufferTexture->getTechnique(0)->getPass(0)->createTextureUnitState();

		textureUnit->setTextureName("SelectionPassTex");

		OverlayManager *mgr = OverlayManager::getSingletonPtr();
		mSelectionDebugOverlay = mgr->create("SelectionDebugOverlay");

		OverlayContainer *panel = static_cast<OverlayContainer *>(mgr->createOverlayElement("Panel", "SelectionDebugPanel"));
		panel->setMetricsMode(GMM_PIXELS);
		panel->setPosition(10, 10);
		panel->setDimensions(400, 280);
		panel->setMaterialName("SelectionDebugMaterial");
		mSelectionDebugOverlay->add2D(panel);

		mSelectionDebugOverlay->hide();
	}

	void SelectionBuffer::ShowOverlay(bool show)
	{
		if(show)
			mSelectionDebugOverlay->show();
		else
			mSelectionDebugOverlay->hide();
	}
}
