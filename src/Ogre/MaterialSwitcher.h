#ifndef _Ogre_MaterialSwitcher_H
#define _Ogre_MaterialSwitcher_H

namespace Ogre
{

	class SelectionBuffer;


	class MaterialSwitcher : public MaterialManager::Listener
	{
	private:

		struct cmp_ColourValue
		{
			bool operator()(const ColourValue &a, const ColourValue &b) const
			{
				return a.getAsBGRA() < b.getAsBGRA();
			}
		};

		typedef std::map<ColourValue, String, cmp_ColourValue> ColorMap;
		typedef std::map<ColourValue, String, cmp_ColourValue>::const_iterator ColorMapConstIter;

		String       mEmptyString;
		ColourValue  mCurrentColor;
		String       mLastEntity;
		Technique   *mLastTechnique;
		MaterialSwitcher::ColorMap mColorDict;

		void getNextColor();

		friend SelectionBuffer;
	public:
		MaterialSwitcher();
		~MaterialSwitcher();

		virtual Technique *handleSchemeNotFound(unsigned short schemeIndex, const String &schemeName, 
			Material *originalMaterial, unsigned short lodIndex, 
			const Renderable *rend);
		const String &getEntityName(const ColourValue &color) const;
		void reset();
	};
}

#endif