#pragma once

namespace GameEngine {

	class TimeStep
	{
	public:
		TimeStep(float time = 0.0f) : m_Time(time)
		{

		}

		operator float() const { return m_Time; }

		float GetSeconds() const { return m_Time; }
		float GetMillseconds() const { return m_Time * 1000.0f; }
	private:
		float m_Time;
	};

}