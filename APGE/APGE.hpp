#ifndef APGE_HPP
#define APGE_HPP

//Core
#include "Core/CoreTypes.hpp"
#include "Core/Logger.hpp"
#include "Core/Application.hpp"

//Base Resources
#include "Core/Resource/IResourceFromMemoryData.hpp"
#include "Core/Resource/IResourceFromStreamData.hpp"
#include "Core/Resource/IResourceHandler.hpp"
#include "Core/Resource/TResourceHandler.hpp"
#include "Core/Resource/ResourceManager.hpp"

//Specific resource handlers
#include "Core/Resource/TextureResourceHandler.hpp"

//Messaging
#include "Core/Messaging/IMessageArguments.hpp"
#include "Core/Messaging/ISubscriber.hpp"
#include "Core/Messaging/IPublisher.hpp"

//Components
#include "Core/Component/IComponent.hpp"
#include "Core/Component/TComponentHandler.hpp"

//Entity
#include "Core/Entity/Entity.hpp"

#endif // APGE_HPP
