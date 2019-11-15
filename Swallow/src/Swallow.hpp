#pragma once

#include "swpch.hpp"

// for external use by swallow applications

#include "Swallow/Application.hpp"
#include "Swallow/Layer.hpp"
#include "Swallow/Log.hpp"

#include "Swallow/Core/Timestep.hpp"

#include "Swallow/Input.hpp"
#include "Swallow/KeyCodes.hpp"
#include "Swallow/MouseButtonCodes.hpp"

#include "Swallow/ImGui/ImGuiLayer.hpp"

// ---------------Renderer--------------------
#include "Swallow/Renderer/Renderer.hpp"
#include "Swallow/Renderer/RenderCommand.hpp"

#include "Swallow/Renderer/Buffer.hpp"
#include "Swallow/Renderer/Shader.hpp"
#include "Swallow/Renderer/Texture.hpp"
#include "Swallow/Renderer/VertexArray.hpp"
// -------------------------------------------
// ---------------Audio--------------------
#include "Swallow/Audio/Audio.hpp"
#include "Swallow/Audio/AudioCommand.hpp"

#include "Swallow/Audio/AudioBuffer.hpp"
#include "Swallow/Audio/AudioSource.hpp"
// -------------------------------------------

// -------------Asset Manager-----------------
#include "Swallow/AssetManager/GameObject.hpp"
#include "Swallow/AssetManager/Primatives.hpp"
#include "Swallow/AssetManager/AnimationController.hpp"
// -------------------------------------------

#include "Swallow/Renderer/Camera.hpp"