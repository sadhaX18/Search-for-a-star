
#pragma once

#include <map>
#include <list>
#include <memory>

class IRenderable;
class IShader;
class ITexture;

class IGraphics
{
public:

	IGraphics();
	virtual ~IGraphics();

	virtual void Update() = 0;
	virtual bool IsValid() = 0;

	virtual ITexture* CreateTexture(const wchar_t* filepath) = 0;
	virtual IShader* CreateShader(const wchar_t* filepath, const char* vsentry, const char* vsshader, const char* psentry, const char* psshader, ITexture* TextureIn) = 0;
	virtual std::shared_ptr<IRenderable> CreateBillboard(IShader* ShaderIn) = 0;

	void deleteRenderable(std::shared_ptr<IRenderable> renderable);

protected:

	std::map<IShader*, std::list<std::shared_ptr<IRenderable>>> Renderables;
	std::list<ITexture*> Textures;

};

