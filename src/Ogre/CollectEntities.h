#include <Ogre/OgreNode.h>
#include <Ogre/OgreSceneNode.h>

namespace Ogre
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	void collectEntities(Ogre::Node * node, ::std::vector<Ogre::Entity*> & entities)
	///
	/// \brief	Collects all entities referenced in the scene graph which root is node.
	///
	/// \author	F. Lamarche, Université de Rennes 1
	/// \date	14/10/2014
	///
	/// \param [in,out]	node		If non-null, the node.
	/// \param [in,out]	entities	[in,out] If non-null, the entities.
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void collectEntities(Ogre::Node * node, ::std::vector<Ogre::Entity*> & entities);
}