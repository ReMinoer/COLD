#ifndef _Ogre_SelectionBuffer_H
#define _Ogre_SelectionBuffer_H

namespace Ogre
{
	class MaterialSwitcher;
	class SelectionRenderListener;

	class SelectionBuffer
	{
	private:
		SceneManager *mSceneMgr;
		Camera *mCamera;
		RenderTarget *mRenderTarget;

		// This is the material listener - Note: it is controlled by a separate
		// RenderTargetListener, not applied globally to all targets
		MaterialSwitcher *mMaterialSwitchListener;

		SelectionRenderListener *mSelectionTargetListener;

		TexturePtr mTexture;
		RenderTexture *mRenderTexture;
		uint8 *mBuffer;
		PixelBox *mPixelBox;
		Overlay *mSelectionDebugOverlay;

		void CreateRTTOverlays();
		void Update();
		void UpdateBufferSize();
	public:
		SelectionBuffer(SceneManager *sceneMgr, Camera * camera, RenderTarget *renderTarget);
		~SelectionBuffer();

		Entity *OnSelectionClick(int x, int y);
		void ShowOverlay(bool show);
	};
}

#endif