#include <stdafx.h>		
#include <Ext/Ogre/ComputeBoundingBox.h>

static void computeBoundingBox(::Ogre::SceneNode* node, ::Ogre::Vector3& minimum, ::Ogre::Vector3& maximum/*, int level=0*/)
{
	//node->_update(true,true) ;

	const ::Ogre::AxisAlignedBox& boundingbox = node->_getWorldAABB();

	// current node boundss
	::Ogre::Vector3 bbox_min = boundingbox.getMinimum();
	::Ogre::Vector3 bbox_max = boundingbox.getMaximum();

	//::std::string indent = "";
	//for (int i=0; i<level; i++)
	//	indent += "  ";


	// SubNodes
	::Ogre::SceneNode::ChildNodeIterator child_it = node->getChildIterator();
	while (child_it.hasMoreElements())
	{
		::Ogre::SceneNode* subnode = dynamic_cast<::Ogre::SceneNode*>(child_it.getNext());
		if (subnode != 0)
		{
			computeBoundingBox(subnode,minimum,maximum/*,level+1*/);
		}
	}

	// Entities
	//indent += "  ";
	::Ogre::SceneNode::ObjectIterator attch_obj_it = node->getAttachedObjectIterator();
	while (attch_obj_it.hasMoreElements())
	{
		const ::Ogre::Entity* ent = dynamic_cast<::Ogre::Entity*>(attch_obj_it.getNext());
		if (ent != 0)
		{
			::Ogre::AxisAlignedBox  box = ent->getMesh()->getBounds();
			//const ::Ogre::AxisAlignedBox  & box = ent->getMesh()->getBounds();

			if(box.isInfinite() || box.isNull()) { continue ; }

			box.transform(ent->getParentSceneNode()->_getFullTransform()) ;

			::Ogre::Vector3 box_min = box.getMinimum();
			::Ogre::Vector3 box_max = box.getMaximum();

			//box_min = ent->getParentSceneNode()->_getFullTransform() * box_min;
			//box_max = ent->getParentSceneNode()->_getFullTransform() * box_max;

			//::std::cout << indent << "Entity: " << ent->getName() << "\n";
			//::std::cout << indent << box_min[0] << " " << box_min[1] << " " <<  box_min[2] << "\n";
			//::std::cout << indent << box_max[0] << " " << box_max[1] << " " <<  box_max[2] << "\n";

			for (int i=0; i<3; i++)
			{
				minimum[i] = ::std::min(minimum[i], box_min[i]);
				maximum[i] = ::std::max(maximum[i], box_max[i]);
			}
		}
	}

	//::std::cout << indent << "Node: " << node->getName() << "\n";
	//::std::cout << indent << minimum[0] << " " << minimum[1] << " " <<  minimum[2] << "\n";
	//::std::cout << indent << maximum[0] << " " << maximum[1] << " " <<  maximum[2] << "\n";
}


::Ogre::AxisAlignedBox Ext::Ogre::computeBoundingBox(::Ogre::SceneNode* node) 
{
	::Ogre::Real maxValue = ::std::numeric_limits<::Ogre::Real>::max() ;
	::Ogre::Real minValue = -maxValue ;
	::Ogre::Vector3 min(maxValue, maxValue, maxValue), max(minValue,minValue,minValue) ;
	::computeBoundingBox(node, min, max) ;
	//::std::cout<<min<<" "<<max<<::std::endl ;
	//char c; 
	//std::cin>> c;
	return ::Ogre::AxisAlignedBox(min, max) ;
}