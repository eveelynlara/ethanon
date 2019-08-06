#include "ETHScriptWrapper.h"
#include "../Drawing/ETHParticleDrawer.h"

Vector2 ETHScriptWrapper::ComputeCarretPosition(const str_type::string &font, const str_type::string &text, const unsigned int pos)
{
	return m_provider->GetVideo()->ComputeCarretPosition(font, text, pos);
}

Vector2 ETHScriptWrapper::ComputeTextBoxSize(const str_type::string &font, const str_type::string &text)
{
	return m_provider->GetVideo()->ComputeTextBoxSize(font, text);
}

void ETHScriptWrapper::DrawText(const Vector2 &v2Pos, const str_type::string &text, const str_type::string &font, const uint32_t color, const float scale)
{
	m_drawableManager.Insert(boost::shared_ptr<ETHDrawable>(new ETHTextDrawer(m_provider, v2Pos, text, font, color, 0x0, scale)));
}

str_type::string ETHScriptWrapper::AssembleColorCode(const uint32_t color)
{
	return gs2d::BitmapFont::AssembleColorCode(color);
}

void ETHScriptWrapper::LoadSprite(const str_type::string& name)
{
	if (WarnIfRunsInMainFunction(GS_L("LoadSprite")))
		return;
	LoadAndGetSprite(name);
}

bool ETHScriptWrapper::ReleaseSprite(const str_type::string& name)
{
	if (WarnIfRunsInMainFunction(GS_L("ReleaseSprite")))
		return false;
	return m_provider->GetGraphicResourceManager()->ReleaseResource(name);
}

SpritePtr ETHScriptWrapper::LoadAndGetSprite(const str_type::string &name)
{
	const ETHGraphicResourceManager::SpriteResource* resource = LoadAndGetResource(name);
	if (resource)
	{
		return resource->GetSprite();
	}
	else
	{
		return 0;
	}
}

const ETHGraphicResourceManager::SpriteResource* ETHScriptWrapper::LoadAndGetResource(const str_type::string &name)
{
	str_type::string resourceDirectory = m_provider->GetFileIOHub()->GetResourceDirectory();
	str_type::string path = resourceDirectory + name;

	return m_provider->GetGraphicResourceManager()->AddFile(
		m_provider->GetFileManager(),
		m_provider->GetVideo(),
		path,
		resourceDirectory,
		false);
}

Vector2 ETHScriptWrapper::GetSpriteSize(const str_type::string &name)
{
	const ETHGraphicResourceManager::SpriteResource* resource = LoadAndGetResource(name);
	if (resource)
	{
		SpritePtr pSprite = resource->GetSprite();
		return pSprite->GetSize(Rect2D());
	}
	else
	{
		return Vector2(0,0);
	}
}

Vector2 ETHScriptWrapper::GetSpriteFrameSize(const str_type::string& name)
{
	const ETHGraphicResourceManager::SpriteResource* resource = LoadAndGetResource(name);
	if (resource)
	{
		SpritePtr pSprite = resource->GetSprite();
		if (resource->packedFrames)
		{
			return pSprite->GetSize(resource->packedFrames->GetRect(resource->frame));
		}
		else
		{
			return pSprite->GetSize(Rect2D());
		}
	}
	else
	{
		return Vector2(0,0);
	}
}

void ETHScriptWrapper::SetupSpriteRects(const str_type::string& name, const unsigned int columns, const unsigned int rows)
{
	ETHGraphicResourceManager::SpriteResource* resource =
		m_provider->GetGraphicResourceManager()->GetSpriteResource(Platform::GetFileName(name));
	if (resource)
	{
		if (!resource->packedFrames)
		{
			resource->packedFrames = SpriteRectsPtr(new SpriteRects());
			resource->packedFrames->SetRects(columns, rows);
		}
	}
}

void ETHScriptWrapper::SetSpriteRect(const str_type::string& name, const unsigned int frame)
{
	ETHGraphicResourceManager::SpriteResource* resource =
		m_provider->GetGraphicResourceManager()->GetSpriteResource(Platform::GetFileName(name));
	if (resource)
	{
		resource->frame = frame;
	}
}

void ETHScriptWrapper::SetSpriteOrigin(const str_type::string& name, const Vector2& origin)
{
	SpritePtr pSprite = LoadAndGetSprite(name);
	if (pSprite)
	{
		pSprite->SetOrigin(origin);
	}
}

void ETHScriptWrapper::SetSpriteFlipX(const str_type::string &name, const bool flip)
{
	ETHGraphicResourceManager::SpriteResource* resource =
		m_provider->GetGraphicResourceManager()->GetSpriteResource(Platform::GetFileName(name));

	if (resource)
	{
		resource->flipX = flip;
	}
}

void ETHScriptWrapper::SetSpriteFlipY(const str_type::string &name, const bool flip)
{
	ETHGraphicResourceManager::SpriteResource* resource =
		m_provider->GetGraphicResourceManager()->GetSpriteResource(Platform::GetFileName(name));

	if (resource)
	{
		resource->flipY = flip;
	}
}

void ETHScriptWrapper::DrawShapedFromResource(
	const ETHGraphicResourceManager::SpriteResource* resource,
	const Vector2 &v2Pos,
	const Vector2 &v2Size,
	const Vector4 &color,
	const float angle)
{
	m_drawableManager.Insert(boost::shared_ptr<ETHDrawable>(
		new ETHSpriteDrawer(
			m_provider,
			resource->GetSprite(),
			v2Pos,
			v2Size,
			color,
			angle,
			resource->packedFrames,
			resource->frame,
			resource->flipX,
			resource->flipY)));
}

void ETHScriptWrapper::DrawSprite(const str_type::string &name, const Vector2 &v2Pos, const uint32_t color, const float angle)
{
	ETHGraphicResourceManager::SpriteResource* resource =
		m_provider->GetGraphicResourceManager()->GetSpriteResource(Platform::GetFileName(name));
	DrawShapedFromResource(resource, v2Pos, Vector2(-1,-1), color, angle);
}

void ETHScriptWrapper::DrawShaped(const str_type::string &name, const Vector2 &v2Pos, const Vector2 &v2Size, const uint32_t color, const float angle)
{
	ETHGraphicResourceManager::SpriteResource* resource =
		m_provider->GetGraphicResourceManager()->GetSpriteResource(Platform::GetFileName(name));
	DrawShapedFromResource(resource, v2Pos, v2Size, Color(color), angle);
}

void ETHScriptWrapper::DrawSprite(const str_type::string &name, const Vector2 &v2Pos, const float alpha, const Vector3 &color, const float angle)
{
	ETHGraphicResourceManager::SpriteResource* resource =
		m_provider->GetGraphicResourceManager()->GetSpriteResource(Platform::GetFileName(name));
	DrawShapedFromResource(resource, v2Pos, Vector2(-1,-1), Vector4(color, alpha), angle);
}

void ETHScriptWrapper::DrawShaped(const str_type::string &name, const Vector2 &v2Pos, const Vector2 &v2Size, const float alpha, const Vector3 &color, const float angle)
{
	ETHGraphicResourceManager::SpriteResource* resource =
		m_provider->GetGraphicResourceManager()->GetSpriteResource(Platform::GetFileName(name));
	DrawShapedFromResource(resource, v2Pos, v2Size, Vector4(color, alpha), angle);
}

void ETHScriptWrapper::PlayParticleEffect(const str_type::string& fileName, const Vector2& pos, const float angle, const float scale)
{
	m_drawableManager.Insert(
		boost::shared_ptr<ETHDrawable>(
			new ETHParticleDrawer(
				m_provider,
				m_provider->GetGraphicResourceManager(),
				m_provider->GetShaderManager(),
				m_provider->GetFileIOHub()->GetResourceDirectory(),
				fileName,
				pos,
				angle,
				scale)));
}

void ETHScriptWrapper::DrawFadingText(const Vector2 &v2Pos, const str_type::string &text, const str_type::string &font, const uint32_t color, unsigned long time, const float scale)
{
	m_drawableManager.Insert(boost::shared_ptr<ETHDrawable>(
		new ETHTextDrawer(m_provider, v2Pos, text, font, color, time, scale)));
}
