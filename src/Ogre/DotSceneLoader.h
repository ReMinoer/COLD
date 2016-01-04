#ifndef DOT_SCENELOADER_H
#define DOT_SCENELOADER_H
 
// Includes
#include <Ogre/OgreString.h>
#include <Ogre/OgreVector3.h>
#include <Ogre/OgreQuaternion.h>
#include <vector>
#include <TinyXML/tinyxml.h>
 
namespace Ogre
{
	// Forward declarations
	class SceneManager;
	class SceneNode;
 
	class nodeProperty
	{
	public:
		String nodeName;
		String propertyNm;
		String valueName;
		String typeName;
 
		nodeProperty(const String &node, const String &propertyName, const String &value, const String &type)
			: nodeName(node), propertyNm(propertyName), valueName(value), typeName(type) {}
	};
 
	class DotSceneLoader
	{
	public:
		DotSceneLoader() : mSceneMgr(0) {}
		virtual ~DotSceneLoader() {}
 
		void parseDotScene(const String &SceneName, const String &groupName, SceneManager *yourSceneMgr, SceneNode *pAttachNode = NULL, const String &sPrependNode = "");
		String getProperty(const String &ndNm, const String &prop);
 
		std::vector<nodeProperty> nodeProperties;
		std::vector<String> staticObjects;
		std::vector<String> dynamicObjects;
 
	protected:
		void processScene(TinyXML::TiXmlElement *XMLRoot);
 
		void processNodes(TinyXML::TiXmlElement *XMLNode);
		void processExternals(TinyXML::TiXmlElement *XMLNode);
		void processEnvironment(TinyXML::TiXmlElement *XMLNode);
		void processTerrain(TinyXML::TiXmlElement *XMLNode);
		void processUserDataReference(TinyXML::TiXmlElement *XMLNode, SceneNode *pParent = 0);
		void processUserDataReference(TinyXML::TiXmlElement *XMLNode, Entity *pEntity);
		void processOctree(TinyXML::TiXmlElement *XMLNode);
		void processLight(TinyXML::TiXmlElement *XMLNode, SceneNode *pParent = 0);
		void processCamera(TinyXML::TiXmlElement *XMLNode, SceneNode *pParent = 0);
 
		void processNode(TinyXML::TiXmlElement *XMLNode, SceneNode *pParent = 0);
		void processLookTarget(TinyXML::TiXmlElement *XMLNode, SceneNode *pParent);
		void processTrackTarget(TinyXML::TiXmlElement *XMLNode, SceneNode *pParent);
		void processEntity(TinyXML::TiXmlElement *XMLNode, SceneNode *pParent);
		void processParticleSystem(TinyXML::TiXmlElement *XMLNode, SceneNode *pParent);
		void processBillboardSet(TinyXML::TiXmlElement *XMLNode, SceneNode *pParent);
		void processPlane(TinyXML::TiXmlElement *XMLNode, SceneNode *pParent);
		void processSubEntities( TinyXML::TiXmlElement * XMLNode, Entity * pEntity ) ;
 
		void processFog(TinyXML::TiXmlElement *XMLNode);
		void processSkyBox(TinyXML::TiXmlElement *XMLNode);
		void processSkyDome(TinyXML::TiXmlElement *XMLNode);
		void processSkyPlane(TinyXML::TiXmlElement *XMLNode);
		void processClipping(TinyXML::TiXmlElement *XMLNode);
 
		void processLightRange(TinyXML::TiXmlElement *XMLNode, Light *pLight);
		void processLightAttenuation(TinyXML::TiXmlElement *XMLNode, Light *pLight);
 
		String getAttrib(TinyXML::TiXmlElement *XMLNode, const String &parameter, const String &defaultValue = "");
		Real getAttribReal(TinyXML::TiXmlElement *XMLNode, const String &parameter, Real defaultValue = 0);
		bool getAttribBool(TinyXML::TiXmlElement *XMLNode, const String &parameter, bool defaultValue = false);
 
		Vector3 parseVector3(TinyXML::TiXmlElement *XMLNode);
		Quaternion parseQuaternion(TinyXML::TiXmlElement *XMLNode);
		ColourValue parseColour(TinyXML::TiXmlElement *XMLNode);
 
 
		SceneManager *mSceneMgr;
		SceneNode *mAttachNode;
		String m_sGroupName;
		String m_sPrependNode;
	};
}
 
#endif // DOT_SCENELOADER_H