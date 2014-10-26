#include "HelloWorldScene.h"

#if( CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
	#include <jni.h>
	#include "platform/android/jni/JniHelper.h"
#endif

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create( closeItem, nullptr );
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("JNI Return Output", "Arial", 24);

    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height ) );
    // add the label as a child to this layer
    this->addChild(label, 1);

    debugLabel = LabelTTF::create("...", "Arial", 24);
    Vec2 tLabelPosition = Vec2( label->getPosition() );
    tLabelPosition.y -= 40;
	debugLabel->setPosition( tLabelPosition );
	this->addChild( debugLabel );

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    // FYI: Opacity range is 0-255
    // label->setString( StringUtils::format( "%hhu", sprite->getOpacity() ) );
    sprite->setOpacity( 128 );

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

#if( CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
    makeMenu();
#endif

    return true;
}

#if( CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
void HelloWorld::makeMenu()
{
		Vector<MenuItem*> tMenuItems;

		MenuItem* tBtnBasicCall = MenuItemFont::create(
														"Basic JNI call",
														CC_CALLBACK_1( HelloWorld::menuBasicCallCallback, this ) );
		tMenuItems.pushBack( tBtnBasicCall );

		MenuItem* tBtnPassInt = MenuItemFont::create(
														"Pass Int with JNI call",
														CC_CALLBACK_1( HelloWorld::menuPassIntCallback, this ) );
		tMenuItems.pushBack( tBtnPassInt );

		MenuItem* tBtnStringReturn = MenuItemFont::create(
														"Return String from JNI call",
														CC_CALLBACK_1( HelloWorld::menuStringReturnCallback, this ) );
		tMenuItems.pushBack( tBtnStringReturn );

		MenuItem* tBtnSayHello = MenuItemFont::create(
														"Say Hello JNI call",
														CC_CALLBACK_1( HelloWorld::menuSayHelloCallback, this ) );
		tMenuItems.pushBack( tBtnSayHello );

		Menu* tMenu = Menu::createWithArray( tMenuItems );
		tMenu->alignItemsVerticallyWithPadding( 40 );

		this->addChild(tMenu, 1);
}

// Demonstrates calling a Java method from C++
void HelloWorld::menuBasicCallCallback( Ref* pSender )
{
	JniMethodInfo t;
	if( JniHelper::getStaticMethodInfo( t,
										"com.roguish.MyAwesomeJavaClass",
										"doMeAFavour",
										"()V" ) )
	{
		t.env->CallStaticVoidMethod( t.classID, t.methodID );
		t.env->DeleteLocalRef( t.classID );
	}
}

// Demonstrates passing an int from C++ to Java method
void HelloWorld::menuPassIntCallback( Ref* pSender )
{
	JniMethodInfo t;
	int tTimes = 4;
	// signatures (I;)V or (I;)V; result in runtime errors:
	// Bogus method descriptor: (I;)V or (I;)V;
	// (I)V instead works
	// http://journals.ecs.soton.ac.uk/java/tutorial/native1.1/implementing/method.html
	// The semicolon at the end of the class type L expression is the terminator of the type expression, not a separator between expressions.
	// http://www.ibm.com/developerworks/java/tutorials/j-jni/j-jni.html#appendixa
	if( JniHelper::getStaticMethodInfo( t,
										"com.roguish.MyAwesomeJavaClass",
										"doMeAFavourInt",
										"(I)V" ) )
	{
		t.env->CallStaticVoidMethod( t.classID, t.methodID, tTimes );
		t.env->DeleteLocalRef( t.classID );
	}
}

// Demonstrates passing an int from C++ to Java method and receiving a String return
void HelloWorld::menuStringReturnCallback( Ref* pSender )
{
	JniMethodInfo t;
	int tParamTimes = 5;
	if( JniHelper::getStaticMethodInfo( t,
										"com.roguish.MyAwesomeJavaClass",
										"doMeAFavourString",
										"(I)Ljava/lang/String;" ) )
	{
		jstring s = ( jstring ) t.env->CallStaticObjectMethod( t.classID, t.methodID, tParamTimes );
		// convert it to std::string
		std::string str = JniHelper::jstring2string( s );
		t.env->DeleteLocalRef( t.classID );
		debugLabel->setString( str );
	}
}

// Demonstrates passing a String and an int from C++ to Java method and receiving a String return
void HelloWorld::menuSayHelloCallback( Ref* pSender )
{
	JniMethodInfo t;
	int tParamTimes = 6;
	if( JniHelper::getStaticMethodInfo( t,
										"com.roguish.MyAwesomeJavaClass",
										"sayHello",
										"(Ljava/lang/String;I)Z" ) )
	{
		const char* tMyName = "Beautiful Name";
		jstring tStringArg1 = t.env->NewStringUTF( tMyName );

		jboolean tBool = (bool) t.env->CallStaticBooleanMethod( t.classID, t.methodID, tStringArg1, tParamTimes );
		// convert it to std::string
		std::string tStr = tBool ? "Return from sayHello: true" : "Return from sayHello: false";
		t.env->DeleteLocalRef( t.classID );
		debugLabel->setString( tStr );
	}
}
#endif

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
