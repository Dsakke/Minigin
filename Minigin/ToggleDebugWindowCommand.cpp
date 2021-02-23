#include "MiniginPCH.h"
#include "ToggleDebugWindowCommand.h"
#include "Renderer.h"

void ToggleDebugCommand::Execute()
{
	dae::Renderer::GetInstance().ToggleDemo();
}
