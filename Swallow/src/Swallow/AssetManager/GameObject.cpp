#include "swpch.hpp"
#include "GameObject.hpp"

namespace Swallow {
    GameObject::GameObject ()
        :m_Transform(std::make_shared<Transform>()), m_VertexArray(VertexArray::Create())
    {
    }
}