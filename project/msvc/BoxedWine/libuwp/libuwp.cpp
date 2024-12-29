/*
    Various helpers for UWP apps, add a new function if you need to interop between a dll and UWP calls
*/
#include "pch.h"
#include "libuwp.h"

#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.Gaming.Input.h>
#include <winrt/Windows.UI.Composition.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.Foundation.h>
#include "winrt/Windows.Foundation.Collections.h"
#include <winrt/Windows.Graphics.Display.Core.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.AccessCache.h>
#include <winrt/Windows.Storage.Pickers.h>
#include <winrt/Windows.Storage.Pickers.Provider.h>
#include <winrt/Windows.UI.ViewManagement.h>


static int width = 0;
static int height = 0;

using namespace winrt::Windows;
using namespace ApplicationModel::Core;
using namespace Foundation;
using namespace Graphics::Display::Core;
using namespace Storage;
using namespace Storage::AccessCache;
using namespace UI::Core;
using namespace UI::ViewManagement;


void uwp_GetBundlePath(char* buffer)
{
    sprintf_s(buffer, 256, "%s", winrt::to_string(ApplicationModel::Package::Current().InstalledPath()).c_str());
}

void uwp_GetBundleFilePath(char* buffer, const char *filename)
{
    sprintf_s(buffer, 256, "%s\\%s", winrt::to_string(ApplicationModel::Package::Current().InstalledPath()).c_str(), filename);
}

// TODO: Restrict types?
void uwp_PickAFile(char* buffer)
{
    std::string out = "";

    Pickers::FileOpenPicker filePicker;

    filePicker.SuggestedStartLocation(Pickers::PickerLocationId::ComputerFolder);
    filePicker.FileTypeFilter().ReplaceAll({ L"*" });

    StorageFile file = filePicker.PickSingleFileAsync().get();

    if (file != nullptr) {
        auto selected = file.Path();
        out = std::string(selected.begin(), selected.end());
    }

    sprintf_s(buffer, 256, "%s", out.c_str());
}

// Inspired by aerisarns impl in the gzdoom port
void uwp_PickAFolder(char* buffer)
{
    std::string out = "";

    Pickers::FolderPicker folderPicker;

    folderPicker.SuggestedStartLocation(Pickers::PickerLocationId::ComputerFolder);
    folderPicker.FileTypeFilter().ReplaceAll({ L"*" });

    StorageFolder folder = folderPicker.PickSingleFolderAsync().get();

    if (folder != nullptr) {
        // Application now has read/write access to all contents in the picked file
        Storage::AccessCache::StorageApplicationPermissions::FutureAccessList().AddOrReplace(L"PickedFolderToken", folder);
        auto selected = folder.Path();
        out = std::string(selected.begin(), selected.end());
    }

    sprintf_s(buffer, 256, "%s", out.c_str());
}


void uwp_GetScreenSize(int* x, int* y)
{
    if (width == 0) {
        HdmiDisplayInformation hdi = HdmiDisplayInformation::GetForCurrentView();
        width = hdi.GetCurrentDisplayMode().ResolutionWidthInRawPixels();
        height = hdi.GetCurrentDisplayMode().ResolutionHeightInRawPixels();
    }

    *x = width;
    *y = height;
}

float uwp_GetRefreshRate()
{
    return HdmiDisplayInformation::GetForCurrentView().GetCurrentDisplayMode().RefreshRate();
}

void* uwp_GetWindowReference()
{
    return reinterpret_cast<void*>(winrt::get_abi(CoreWindow::GetForCurrentThread()));
}

void uwp_ProcessEvents()
{
    CoreWindow::GetForCurrentThread().Dispatcher().ProcessEvents(CoreProcessEventsOption::ProcessAllIfPresent);
}

// Register gamepad event hooks to method inside of calling program
void uwp_RegisterGamepadCallbacks(void (*callback)(void))
{
    namespace WGI = winrt::Windows::Gaming::Input;

    try
    {
        WGI::Gamepad::GamepadAdded([callback](auto&&, const WGI::Gamepad) {
            callback();
        });

        WGI::Gamepad::GamepadRemoved([callback](auto&&, const WGI::Gamepad) {
            callback();
        });
    }
    catch (winrt::hresult_error)
    {
    }

}
