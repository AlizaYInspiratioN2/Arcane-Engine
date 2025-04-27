#include "arcpch.h"
#include "VolumetricManager.h"

#include <Arcane/Scene/Scene.h>
#include <Arcane/Scene/Components.h>
#include <Arcane/Graphics/Camera/ICamera.h>

namespace Arcane
{
	VolumetricManager::VolumetricManager(Scene* scene) : m_Scene(scene)
	{

	}

	VolumetricManager::~VolumetricManager()
	{

	}

	void VolumetricManager::Init()
	{
		FindClosestVolumetricCloud();
	}

	void VolumetricManager::Update()
	{
		FindClosestVolumetricCloud();
	}

	// TODO: Should use camera component's position (not the editor camera, after they are separated)
	void VolumetricManager::FindClosestVolumetricCloud()
	{
		// Reset our pointers since it is possible no volumetric cloud exists anymore
		m_ClosestVolumetricCloudComponent = nullptr;
		float closestDistance2 = std::numeric_limits<float>::max();

		auto group = m_Scene->m_Registry.view<TransformComponent, VolumetricCloudComponent>();
		for (auto entity : group)
		{
			auto& [transformComponent, volumetricCloudComponent] = group.get<TransformComponent, VolumetricCloudComponent>(entity);

			float currentDistance2 = glm::distance2(m_Scene->GetCamera()->GetPosition(), transformComponent.Translation);
			if (currentDistance2 < closestDistance2)
			{
				closestDistance2 = currentDistance2;
				m_ClosestVolumetricCloudComponent = &volumetricCloudComponent;
				m_ClosestVolumetricCloudTransform = &transformComponent;
			}
		}
	}
}
