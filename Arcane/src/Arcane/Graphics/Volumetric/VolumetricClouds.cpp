#include "arcpch.h"
#include "VolumetricClouds.h"

#include <Arcane/Graphics/Texture/Texture3D.h>
#include <Arcane/Graphics/Noise/PerlinNoise.h>
#include <Arcane/Graphics/Renderer/Renderer.h>
#include <Arcane/Graphics/Renderer/GLCache.h>
#include <Arcane/Graphics/Shader.h>
#include <Arcane/Scene/Components.h>
#include <Arcane/Util/Loaders/ShaderLoader.h>

namespace Arcane
{
	VolumetricClouds::VolumetricClouds()
	{
		m_VolumetricCloudShader = ShaderLoader::LoadShader("Skybox.glsl");

		m_GLCache = GLCache::GetInstance();
	}

	void VolumetricClouds::DrawClouds(const VolumetricCloudComponent* volumetricComponent)
	{
		if (volumetricComponent->GeneratedNoiseTexture3D == nullptr)
		{
			return;
		}

		m_GLCache->SetShader(m_VolumetricCloudShader);

		volumetricComponent->GeneratedNoiseTexture3D->Bind(0);
		m_VolumetricCloudShader->SetUniform("noiseTexture3D", 0);

		//m_SkyboxShader->SetUniform("view", camera->GetViewMatrix());
		//m_SkyboxShader->SetUniform("projection", camera->GetProjectionMatrix());

		m_GLCache->SetDepthTest(false);
		m_GLCache->SetFaceCull(true);
		m_GLCache->SetCullFace(GL_BACK);

		Renderer::DrawNdcPlane();

		volumetricComponent->GeneratedNoiseTexture3D->Unbind();
	}

	Texture3D* VolumetricClouds::Generate3DNoiseTexture(NoiseTextureParams& params)
	{
		Texture3D* texture3D = new Texture3D();

		const unsigned int width = 256;
		const unsigned int height = 256;
		const unsigned int depth = 256;

		const glm::vec3 scale = glm::vec3(params.NoiseScale.x / width, params.NoiseScale.y / height, params.NoiseScale.z / depth);

		const siv::PerlinNoise::seed_type seed = params.Seed;
		const siv::PerlinNoise perlin{ seed };

		std::vector<unsigned char> textureData(width * height * depth * 3); // 3 bytes per pixel (RGB)
		for (unsigned int z = 0; z < depth; z++)
		{
			for (unsigned int y = 0; y < height; y++)
			{
				for (unsigned int x = 0; x < width; x++)
				{
					size_t index = (z * width * height + y * width + x) * 3;

					if (params.NoiseAlgorithm == CloudNoiseAlgorithm::CloudNoiseAlgorithm_Worley)
					{
						textureData[index + 0] = 255;
						textureData[index + 1] = 255;
						textureData[index + 2] = 255;
					}
					else if (params.NoiseAlgorithm == CloudNoiseAlgorithm::CloudNoiseAlgorithm_Perlin)
					{
						const float noise = (float)perlin.octave3D_01(x * scale.x, y * scale.y, z * scale.z, params.Octaves);
						textureData[index + 0] = noise * 255.0f;
						textureData[index + 1] = noise * 255.0f;
						textureData[index + 2] = noise * 255.0f;
					}
				}
			}
		}

		Texture3DSettings textureSettings;
		texture3D->SetTextureSettings(textureSettings);
		texture3D->Generate3DTexture(width, height, depth, GL_RGB, GL_UNSIGNED_BYTE, textureData.data());
		return texture3D;
	}
}
