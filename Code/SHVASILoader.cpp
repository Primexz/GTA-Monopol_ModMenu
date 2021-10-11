#include "SHVASILoader.h"
#include "SHVUtility.h"
#include "SHVPEImage.h"
#include <queue>
#include <filesystem>
#include "Functions.h"
using namespace Utility;
void Features::LoadPlugins(fs::path asi_path)
{
	PEImage pluginImage;
	if (!pluginImage.Load(asi_path.string().data())) {

		g_Logger->Info("Failed to load image...");
	}
	// Image not compatible, needs patching
	if (!pluginImage.IsOpenVHookCompatible()) {

		g_Logger->Info("Incompatible image identified, patching...");

		if (pluginImage.PatchCompatibility()) {
			g_Logger->Info("Patching complete...");
		}
		else {

			g_Logger->Info("Failed to patch image...");
		}
	}
	g_Logger->Info("Loading \"%s\"", asi_path.string().data());

	auto module = LoadLibraryA(asi_path.string().data());
	if (!module)
	{
		DWORD error = ::GetLastError();
		g_Logger->Info(to_string(error).c_str());
		LPSTR messageBuffer = nullptr;
		FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);
	}
	ScriptEventLog(asi_path.filename().string() + " Has been loaded successfully.");
	return;
}
void Initialize()
{
}
//