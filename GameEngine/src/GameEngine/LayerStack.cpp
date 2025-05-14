#include "hzpch.h"
#include "LayerStack.h"

namespace GameEngine {

	LayerStack::LayerStack()
	{
		
	}

	LayerStack::~LayerStack()
	{
		//��������ɾ�����в�
		for (Layer* layer : m_Layers)
		{
			delete layer;
		}
	}

	//��ͨ��ᱻpush�����е���ǰ��
	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
		layer->OnAttach();
	}

	//���ǲ�ᱻpush�����е�����棬�������ǲ���Զ����ͨ�����
	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
		overlay->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it); //���Ƴ�����ɾ����ֻ�������������вŻ�ɾ��Layer
			m_LayerInsertIndex--;
			layer->OnDetach();
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			overlay->OnDetach();
		}
	}

}