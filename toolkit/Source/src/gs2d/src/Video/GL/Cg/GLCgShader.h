#ifndef GS2D_GLCGSHADER_H_
#define GS2D_GLCGSHADER_H_

#include "../../../Shader.h"
#include "GLCgShaderContext.h"

#include <Cg/cg.h>

#include <map>
#include <list>

#include "../../../Utilities/RecoverableResource.h"

namespace gs2d {

class GLVideo;

class GLCgShader : public Shader, RecoverableResource
{
	CGprogram m_cgVsProgam;
    CGprogram m_cgPsProgam;

	CGprofile m_cgVsProfile;
    CGprofile m_cgPsProfile;

	std::string m_vsShaderName;
	std::string m_vsShaderCode;

	std::string m_psShaderName;
	std::string m_psShaderCode;

    std::string m_shaderPairName;

	std::string m_vsEntry;
    std::string m_psEntry;

	bool CheckForError(const std::string& situation, const std::string& additionalInfo);
	void Recover();

	GLVideo* m_video;
	GLCgShaderContextPtr m_shaderContext;
	CGcontext m_cgContext;

	CGcontext ExtractCgContext(ShaderContextPtr context);

	std::list<CGparameter> m_enabledTextures;

	bool CreateCgProgram(
		CGprogram* outProgram,
        const std::string& shaderCode,
        CGprofile profile,
        const std::string& shaderName,
        const std::string& entry);

	void DestroyCgProgram(CGprogram* outProgram);

	void DisableIfEnabled(CGparameter param);

public:
	GLCgShader(GLVideo* video);
	~GLCgShader();

	bool LoadShaderFromFile(
		ShaderContextPtr context,
        const std::string& vsFileName,
        const std::string& vsEntry,
        const std::string& psFileName,
        const std::string& psEntry);

	bool LoadShaderFromString(
		ShaderContextPtr context,
        const std::string& vsShaderName,
        const std::string& vsCodeAsciiString,
        const std::string& vsEntry,
        const std::string& psShaderName,
        const std::string& psCodeAsciiString,
        const std::string& psEntry);

	void SetConstant(const str_type::string& name, const math::Vector4 &v);
	void SetConstant(const str_type::string& name, const math::Vector3 &v);
	void SetConstant(const str_type::string& name, const math::Vector2 &v);
	void SetConstant(const str_type::string& name, const float x);
	void SetConstant(const str_type::string& name, const int n);
	void SetConstantArray(const str_type::string& name, unsigned int nElements, const math::Vector2* v);
	void SetConstantArray(const str_type::string& name, unsigned int nElements, const math::Vector4* v);
	void SetMatrixConstant(const str_type::string& name, const math::Matrix4x4 &matrix);
	void SetTexture(const str_type::string& name, TexturePtr pTexture, const unsigned int index);

	void SetShader();
	void UnbindShader();
	void DisableTextures();
};

typedef boost::shared_ptr<GLCgShader> GLCgShaderPtr;

}

#endif
