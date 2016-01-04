#include <Math/Matrix3x3.h>
#include <System/MessageEmitter.h>
#include <System/MessageListener.h>
#include <System/CallbackMessageListener.h>
#include <GameElements/LocalizedEntity2D.h>
#include <System/ActiveObject.h>
#include <System/Controller.h>
#include <iostream>
#include <boost/bind.hpp>
#include <Triggers/CollisionObject.h>
#include <Triggers/BasicCollisionDetector.h>
#include <Triggers/SweepAndPrune.h>
#include <Triggers/Shape.h>

template <> class Math::Matrix3x3<double> ;

void receiver(double const & value)
{
	::std::cout<<"received: "<<value<<std::endl ;
}

class Toto 
{
public:
	void print(double const & value)
	{
		::std::cout<<"received in Toto instance: "<<value<<std::endl ;
	}
};

void isConstructed(const System::ConstructionMessage<GameElements::LocalizedEntity2D> & msg)
{
	::std::cout<<"Constructed LocalizedEntity: "<<&msg.m_object<<::std::endl ;
}

void isDestroyed(const System::DestructionMessage<GameElements::LocalizedEntity2D> & msg)
{
	::std::cout<<"Destroyed LocalizedEntity: "<<&msg.m_object<<::std::endl ;
}

class LocalizedEntityLifeListener
{
protected:
	System::CallbackMessageListener<System::ConstructionMessage<GameElements::LocalizedEntity2D> > m_constructListener ;
	System::CallbackMessageListener<System::DestructionMessage<GameElements::LocalizedEntity2D> > m_destroyListener ;

public:
	LocalizedEntityLifeListener()
		: m_constructListener(System::ConstructionDestructionEmitter<GameElements::LocalizedEntity2D>::getConstructionEmitter(), this, &LocalizedEntityLifeListener::onCreate),
		m_destroyListener(System::ConstructionDestructionEmitter<GameElements::LocalizedEntity2D>::getDestructionEmitter(), this, &LocalizedEntityLifeListener::onDestroy)

		//: m_constructListener(System::ConstructionDestructionEmitter<GameElements::LocalizedEntity2D>::getConstructionEmitter(),
		//						::boost::bind(&LocalizedEntityLifeListener::onCreate, this, _1)),
		//  m_destroyListener(System::ConstructionDestructionEmitter<GameElements::LocalizedEntity2D>::getDestructionEmitter(),
		//						 ::boost::bind(&LocalizedEntityLifeListener::onDestroy, this, _1))
	{

	}

	void onCreate(const System::ConstructionMessage<GameElements::LocalizedEntity2D> & msg)
	{
		::std::cout<<"Constructed LocalizedEntity: "<<&msg.m_object<<::std::endl ;
	}

	void onDestroy(const System::DestructionMessage<GameElements::LocalizedEntity2D> & msg)
	{
		::std::cout<<"Destroyed LocalizedEntity: "<<&msg.m_object<<::std::endl ;
	}
};

class TestActiveObject1 : public System::ActiveObject
{
public:

	virtual void update(Config::Real const & dt)
	{
		::std::cout<<"Updating an instance of TestActiveObject1"<<::std::endl ;
	}
};

class TestActiveObject2 : public System::ActiveObject
{
	virtual void update(Config::Real const & dt)
	{
		::std::cout<<"Updating an instance of TestActiveObject2"<<::std::endl ;
	}
};

int testController()
{
	Toto test2 ;
	System::MessageEmitter<double> senderTest ;
	senderTest.connect(&receiver) ;
	senderTest.connect(boost::bind(&Toto::print, &test2, _1)) ;

	senderTest.send(10.0) ;

	System::ConstructionDestructionEmitter<GameElements::LocalizedEntity2D>::getConstructionEmitter()->connect(&isConstructed) ;
	System::ConstructionDestructionEmitter<GameElements::LocalizedEntity2D>::getDestructionEmitter()->connect(&isDestroyed) ;

	LocalizedEntityLifeListener flop ;

	GameElements::LocalizedEntity2D foo ;

	System::Controller controller ;
	TestActiveObject1 * tmp = new TestActiveObject1 ;
	TestActiveObject2 * tmp2 = new TestActiveObject2 ;

	for(int cpt=0 ; cpt<10 ; ++cpt)
	{
		std::cout<<"-----------------------------Step: "<<cpt<<std::endl ;
		if(cpt==5)
		{
			delete tmp2 ;
		}
		if(cpt==7)
		{
			delete tmp ;
		}
		if(cpt==2) { tmp->setActive(false) ; }
		if(cpt==4) { tmp->setActive(true) ; }
		controller.update(Config::Real(0.1)) ;
	}

	return 0 ;
}

int nbCollisions = 0 ;

class TestCollisionObject : public Triggers::CollisionObject
{
public:
	virtual void onCollision(const CollisionMessage & message) 
	{
		++nbCollisions ;
		//::std::cout<<"Collision detected between "<<&message.m_object1<<" ,"<<&message.m_object2<<::std::endl ;
	}
}; 

int main(int argc, char ** argv)
{
	//Triggers::BasicCollisionDetector collisionDetector ;		
	Triggers::SweepAndPrune collisionDetector ;		

	::std::vector<TestCollisionObject*> m_objects ;

	int extent = 1000 ;
	for(int cpt=0 ; cpt<20000 ; ++cpt)
	{
		TestCollisionObject * tmp = new TestCollisionObject ;
		tmp->addShape(Triggers::Shape(Math::Vector2<Config::Real>(0.0, 0.0), rand()%5+1)) ;
		tmp->setTransform(Math::Matrix3x3<Config::Real>::getTranslationHomogeneous(Math::Vector2<Config::Real>(rand()%extent,rand()%extent))) ;
		m_objects.push_back(tmp) ;
	}
	//m_objects[0]->setType(Triggers::CollisionObject::trigger) ;
	//TestCollisionObject obj1, obj2 ;
	//obj1.addShape(Triggers::Shape(Math::Vector2<Config::Real>(1.0,1.0), 3.0)) ;
	//obj2.addShape(Triggers::Shape(Math::Vector2<Config::Real>(0.0,0.0), 3.0)) ;
	//obj3.addShape(Triggers::Shape(Math::Vector2<Config::Real>(0.0,-5.5), 3.0)) ;
	//obj2.setType(Triggers::CollisionObject::trigger) ;
	collisionDetector.update(Config::Real(0.05)) ;
	::std::cout<<"Collisions reported: "<<nbCollisions<<std::endl ;
}