#include "box2d/box2d.h"
#include "Engine/IRenderable.h"
#include "Engine/IShader.h"
#include "Engine/ITexture.h"
#include "WorldMap.h"

WorldMap::WorldMap(IGraphics* graphics) {
	ITexture* TopTileTexture = graphics->CreateTexture(L"Resource/Textures/InnerRing.dds");
	ITexture* BottomTileTexture = graphics->CreateTexture(L"Resource/Textures/MiddleRing.dds");
	ITexture* LeftTileTexture = graphics->CreateTexture(L"Resource/Textures/OuterRing.dds");
	ITexture* RightTileTexture = graphics->CreateTexture(L"Resource/Textures/Arrow.dds");
	ITexture* MiddleTileTexture = graphics->CreateTexture(L"Resource/Textures/InnerRing.dds");
	ITexture* TopLeftTileTexture = graphics->CreateTexture(L"Resource/Textures/InnerRing.dds");
	ITexture* TopRightTileTexture = graphics->CreateTexture(L"Resource/Textures/MiddleRing.dds");
	ITexture* BottomLeftTileTexture = graphics->CreateTexture(L"Resource/Textures/OuterRing.dds");
	ITexture* BottomRightTileTexture = graphics->CreateTexture(L"Resource/Textures/Arrow.dds");

	IShader* TopTileShader = graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", TopTileTexture);
	IShader* BottomTileShader = graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", BottomTileTexture);
	IShader* LeftTileShader = graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", LeftTileTexture);
	IShader* RightTileShader = graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", RightTileTexture);
	IShader* MiddleTileShader = graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", MiddleTileTexture);
	IShader* TopLeftTileShader = graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", TopLeftTileTexture);
	IShader* TopRightTileShader = graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", TopRightTileTexture);
	IShader* BottomLeftTileShader = graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", BottomLeftTileTexture);
	IShader* BottomRightTileShader = graphics->CreateShader(L"Resource/Shaders/UnlitColor.fx", "VS_Main", "vs_4_0", "PS_Main", "ps_4_0", BottomRightTileTexture);


	tileMap.insert({ TileSet::TOP, TopTileShader });
	tileMap.insert({ TileSet::BOTTOM, BottomTileShader });
	tileMap.insert({ TileSet::LEFT, LeftTileShader });
	tileMap.insert({ TileSet::RIGHT, RightTileShader });
	tileMap.insert({ TileSet::MIDDLE, MiddleTileShader });
	tileMap.insert({ TileSet::TOP_LEFT, TopLeftTileShader });
	tileMap.insert({ TileSet::TOP_RIGHT, TopRightTileShader });
	tileMap.insert({ TileSet::BOTTOM_LEFT, BottomLeftTileShader });
	tileMap.insert({ TileSet::BOTTOM_RIGHT, BottomRightTileShader });
}