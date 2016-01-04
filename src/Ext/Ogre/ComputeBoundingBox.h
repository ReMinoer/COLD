#ifndef _Ext_Ogre_ComputeBoundingBox_H
#define _Ext_Ogre_ComputeBoundingBox_H

#include <Ogre/Ogre.h>
#include <Ogre/OgreVector3.h>
#include <Ogre/OgreAxisAlignedBox.h>
#include <iostream>
#include <string>

namespace Ext
{
	namespace Ogre
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	::Ogre::AxisAlignedBox computeBoundingBox(const ::Ogre::SceneNode* node);
		///
		/// \brief	Computes the bounding box of the given node.
		///
		/// \author	Fabrice Lamarche, university of Rennes 1
		/// \param	node	The node.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		::Ogre::AxisAlignedBox computeBoundingBox(::Ogre::SceneNode* node) ;
	}
}

#endif