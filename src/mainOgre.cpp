#include <stdafx.h>

#include <OgreFramework/MainApplication.h>
#include <direct.h>
//#include <tbb/tbbmalloc_proxy.h>

int main(int argc, char ** argv)
{
	char currentDirectory[1024] ;
	_getcwd(currentDirectory, 1024) ; 
	std::cout<<"Current directory: "<<currentDirectory<<::std::endl ;
	// Create application object
	OgreFramework::MainApplication app;

	try {
		app.go();
	} 
	catch( Ogre::Exception& e )
	{
		std::cerr << "An Ogre exception has occurred: " <<e.getFullDescription().c_str() << std::endl;
	}
	catch(::std::exception & e)
	{
		::std::cerr << "An exception occurred: "<<e.what()<<::std::endl ;
	}
}

