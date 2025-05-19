#include "hzpch.h"
#include "LayerStack.h"

namespace GameEngine {

	LayerStack::LayerStack()
	{
		
	}

	LayerStack::~LayerStack()
	{
		//逐层遍历，删除所有层
		for (Layer* layer : m_Layers)
		{
			delete layer;
		}
	}

	//普通层会被push到队列的最前面
	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
		layer->OnAttach();
	}

	//覆盖层会被push到队列的最后面，即：覆盖层永远在普通层后面
	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
		overlay->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, layer);
		if (it != m_Layers.end())
		{
			layer->OnDetach();
			m_Layers.erase(it); //仅移除，非删除。只有在析构函数中才会删除Layer
			m_LayerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), overlay);
		if (it != m_Layers.end())
		{
			overlay->OnDetach();
			m_Layers.erase(it);
		}
	}

}