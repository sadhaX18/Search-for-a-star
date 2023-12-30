#include "Engine/IShader.h"
#include "Engine/IGraphics.h"
#include "Resources.h"

Resources::Resources() : playerSprite(nullptr), spikeSprite(nullptr), doorSprite(nullptr) {
	tileMap = std::make_shared<std::map<TileSet, IShader*>>();
}
Resources::~Resources() {} // All shaders will be deleted by IGraphics

void Resources::loadResources(IGraphics* graphics) {
	ITexture* TopTileTexture = graphics->CreateTexture(L"Resource/Textures/TileSet/Top.dds");
	ITexture* BottomTileTexture = graphics->CreateTexture(L"Resource/Textures/TileSet/Bottom.dds");
	ITexture* LeftTileTexture = graphics->CreateTexture(L"Resource/Textures/TileSet/Left.dds");
	ITexture* RightTileTexture = graphics->CreateTexture(L"Resource/Textures/TileSet/Right.dds");
	ITexture* MiddleTileTexture = graphics->CreateTexture(L"Resource/Textures/TileSet/Middle.dds");
	ITexture* TopLeftTileTexture = graphics->CreateTexture(L"Resource/Textures/TileSet/TopLeft.dds");
	ITexture* TopRightTileTexture = graphics->CreateTexture(L"Resource/Textures/TileSet/TopRight.dds");
	ITexture* BottomLeftTileTexture = graphics->CreateTexture(L"Resource/Textures/TileSet/BottomLeft.dds");
	ITexture* BottomRightTileTexture = graphics->CreateTexture(L"Resource/Textures/TileSet/BottomRight.dds");
	
	ITexture* playerTexture = graphics->CreateTexture(L"Resource/Textures/InnerRing.dds");
	ITexture* spriteTexture = graphics->CreateTexture(L"Resource/Textures/Spike.dds");
	ITexture* doorTexture = graphics->CreateTexture(L"Resource/Textures/Door.dds");

	IShader* TopTileShader = graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", TopTileTexture);
	IShader* BottomTileShader = graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", BottomTileTexture);
	IShader* LeftTileShader = graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", LeftTileTexture);
	IShader* RightTileShader = graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", RightTileTexture);
	IShader* MiddleTileShader = graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", MiddleTileTexture);
	IShader* TopLeftTileShader = graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", TopLeftTileTexture);
	IShader* TopRightTileShader = graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", TopRightTileTexture);
	IShader* BottomLeftTileShader = graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", BottomLeftTileTexture);
	IShader* BottomRightTileShader = graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", BottomRightTileTexture);

	playerSprite = graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", playerTexture);
	spikeSprite = graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", spriteTexture);
	doorSprite = graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", doorTexture);

	tileMap->insert({ TileSet::TOP, TopTileShader });
	tileMap->insert({ TileSet::BOTTOM, BottomTileShader });
	tileMap->insert({ TileSet::LEFT, LeftTileShader });
	tileMap->insert({ TileSet::RIGHT, RightTileShader });
	tileMap->insert({ TileSet::MIDDLE, MiddleTileShader });
	tileMap->insert({ TileSet::TOP_LEFT, TopLeftTileShader });
	tileMap->insert({ TileSet::TOP_RIGHT, TopRightTileShader });
	tileMap->insert({ TileSet::BOTTOM_LEFT, BottomLeftTileShader });
	tileMap->insert({ TileSet::BOTTOM_RIGHT, BottomRightTileShader });
}