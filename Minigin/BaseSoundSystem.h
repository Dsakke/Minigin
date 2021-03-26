#pragma once
#include <concurrent_queue.h>
#include <future>

namespace dae
{
	class BaseSoundSystem
	{
	public:
		virtual ~BaseSoundSystem() = default;
		virtual void AddSound(const std::string& fileName) = 0; // Add Sound to the queue
	};
}