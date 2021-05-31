#include "MiniginPCH.h"
#include "ToggleDebugWindowCommand.h"
#include "Renderer.h"

void dae::ToggleDebugCommand::Execute()
{
	dae::Renderer::GetInstance().ToggleDemo();
}
