#ifndef ENUM_NAME_H
#define ENUM_NAME_H

struct EnumName
{
	enum Name
	{
		Stubb // needed for overloading
	};

	bool operator == (EnumName tmp )
	{
		return ( this->value == tmp.value);
	}

	int value;
};

struct SpriteBatchName: public EnumName
{
	SpriteBatchName( SpriteBatchName::Name n )
	{
		this->value = n;
	}

	enum Name
	{
		SpriteBatch_Birds = 10000,
		SpriteBatch_Debug,
		SpriteBatch_Blocks,
		SpriteBatch_Background,
		SpriteBatch_Layer2,
		SpriteBatch_Layer1,
		SpriteBatch_Trail,

		Not_Initialized
	};
};

struct SpriteName: public EnumName
{
	SpriteName( SpriteName::Name n )
	{
		this->value = n;
	}

	enum Name
	{
		Sprite_Bird = 20000,
		
		Sprite_Red,			 
		Sprite_Yellow,
		Sprite_Blue,
		Sprite_White,
		Sprite_Green,
		Sprite_Black,

		Sprite_Feather, 
	
		Sprite_SmokeRing,

		Sprite_Pig1,			
		Sprite_SlingRight,	    
		Sprite_SlingLeft,		
		Sprite_woodMiniPlank1,	
		Sprite_woodMiniPlank2,	
		Sprite_woodMiniPlank3,	
		Sprite_woodMiniPlank4,	
		Sprite_woodPlankShort1, 
		Sprite_woodPlankShort2, 
		Sprite_woodPlankShort3, 
		Sprite_woodPlankMed1,	
		Sprite_woodPlankMed2,	
		Sprite_woodPlankMed3,	
		Sprite_woodPlankMed4,	
		Sprite_woodPlankMed5,	
		Sprite_woodPlatform1,	
		Sprite_woodPlatform2,	
		Sprite_woodCube,
		Sprite_woodBlock,
		Sprite_StoneBlock,
		Sprite_GlassPlank,
		Sprite_GlassBlock,
		Sprite_Ground,

		Sprite_Egg,

		Sprite_Box_Bird,
		Sprite_Box_Block,
		Sprite_Box_Block2,

		Sprite_Poly,

		Sprite_BackgroundCloud,
		Sprite_BackgroundTrees, 
		Sprite_BackgroundGrass, 
		Sprite_BackgroundGround,

		Not_Initialized
	};
};

struct ImageName: public EnumName
{
	ImageName( ImageName::Name n )
	{
		this->value = n;
	}

	enum Name
	{
		Image_RedBird = 30000,
		Image_Pig,
		Image_YellowBird,
		Image_BlueBird,
		Image_WhiteBird,
		Image_GreenBird,
		Image_BlackBird,

		Image_RedBirdBlink,
		Image_YellowBirdBlink,
		Image_BlueBirdBlink, 
		Image_WhiteBirdBlink,
		Image_GreenBirdBlink,
		Image_BlackBirdBlink,

		Image_BlueBirdHurt,	
		Image_GreenBirdSmashed,
		Image_WhiteBirdPoop,	
		Image_YellowBirdAngry, 
		Image_RedBirdCaw,		
		Image_WhiteEgg,		

		Image_RedBirdFeather, 
		Image_YellowBirdFeather,
		Image_BlueBirdFeather,
		Image_WhiteBirdFeather,
		Image_GreenBirdFeather,
		Image_BlackBirdFeather,

		Image_GlassBlockFragment,
		Image_StoneBlockFragment,
		Image_WoodBlockFragment,
		Image_SmokeFragment,

		Image_WoodTriangle1,

		Image_PigHurt,
		Image_PigBlink,

		Image_HelmetPig,			
		Image_HelmetPigHurt1,		
		Image_HelmetPigHurt2,		
		Image_HelmetPigBlink,		
		Image_HelmetPigHurt1Blink, 
		Image_HelmetPigHurt2Blink,		

		Image_SmokeRing1,

		Image_SlingRight,
		Image_SlingLeft,

		Image_StoneBlock_1,
		Image_StoneBlock_2,
		Image_StoneBlock_3,
		Image_StoneBlock_4,

		Image_woodMiniPlank_1,
		Image_woodMiniPlank_2,
		Image_woodMiniPlank_3,
		Image_woodMiniPlank_4,
		
		Image_woodPlankShort_1,
		Image_woodPlankShort_2,
		Image_woodPlankShort_3,
		Image_woodPlankShort_4,

		Image_woodPlankMed_1,
		Image_woodPlankMed_2,
		Image_woodPlankMed_3,
		Image_woodPlankMed_4,

		Image_WoodBlock_1,
		Image_WoodBlock_2,
		Image_WoodBlock_3,
		Image_WoodBlock_4,

		Image_WoodCube_1,
		Image_WoodCube_2,
		Image_WoodCube_3,
		Image_WoodCube_4,

		Image_woodPlankLong_1,
		Image_woodPlankLong_2,
		Image_woodPlankLong_3,
		Image_woodPlankLong_4,

		Image_GlassPlank_1,
		Image_GlassPlank_2,
		Image_GlassPlank_3,
		Image_GlassPlank_4,

		Image_GlassBlock_1,
		Image_GlassBlock_2,
		Image_GlassBlock_3,
		Image_GlassBlock_4,

		Image_woodPlatform,	
		Image_Ground,

		Image_BackgroundCloud, 
		Image_BackgroundTrees, 
		Image_BackgroundGrass, 
		Image_BackgroundGround,
		Not_Initialized,
	};
};

struct TextName: public EnumName
{
	TextName( TextName::Name n )
	{
		this->value = n;
	}

	enum Name
	{
		Texture_Stone_Blocks = 3000,
		Texture_Wood_Blocks,
		Texture_Glass_Blocks,
		Texture_Birds,
		Texture_WoodPlat,
		Texture_GlassBlock,
		Texture_Ground,

		Texture_BackgroundCloud,
		Texture_BackgroundTrees,
		Texture_BackgroundGrass,
		Texture_BackgroundGround,
		Not_Initialized
	};
};



struct GameObjectName: public EnumName
{
	GameObjectName( GameObjectName::Name n )
	{
		this->value = n;
	}

	enum Name
	{
		GameObject_Block = 50000,
		GameObject_Block2,
		GameObject_Bird,
		GameObject_Egg,
		GameObject_Glass_Block,
		GameObject_Stone_Block,
		GameObject_Pig,
		GameObject_Ground,
		GameObject_Particle,

		GameObject_WoodPlat,
		Not_Initialized
	};
};

#endif
