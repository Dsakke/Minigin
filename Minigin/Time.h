#pragma once
#include <chrono>

namespace dae
{
	class Time
	{
	public:
		static Time* GetInstance();
		static void DestroyInstance();

		void UpdateTime();
		float GetElapsed();
	private:
		Time();
		~Time()= default;

		static Time* m_pInstance;
		std::chrono::high_resolution_clock::time_point m_Prevtime;
		float m_Elapsed;
	};
	
}

