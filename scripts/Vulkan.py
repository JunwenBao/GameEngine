import os
import subprocess
import sys
from pathlib import Path

import Utils

VULKAN_SDK = os.environ.get('VULKAN_SDK')
VULKAN_SDK_INSTALLER_URL = 'https://sdk.lunarg.com/sdk/download/1.3.275.0/windows/VulkanSDK-1.3.275.0-Installer.exe'
HAZEL_VULKAN_VERSION = '1.3.275.0'
VULKAN_SDK_EXE_PATH = 'GameEngine/vendor/VulkanSDK/VulkanSDK-1.3.275.0-Installer.exe'

def InstallVulkanSDK():
    print(f'Downloading Vulkan SDK from {VULKAN_SDK_INSTALLER_URL} to {VULKAN_SDK_EXE_PATH}')
    Utils.DownloadFile(VULKAN_SDK_INSTALLER_URL, VULKAN_SDK_EXE_PATH)
    print("Download complete.")
    print("Running Vulkan SDK installer...")
    os.startfile(os.path.abspath(VULKAN_SDK_EXE_PATH))
    print("Please re-run this script after installing the Vulkan SDK.")

def InstallVulkanPrompt():
    print("Would you like to install the Vulkan SDK now?")
    install = Utils.YesOrNo()
    if install:
        InstallVulkanSDK()
        quit()

def CheckVulkanSDK():
    if VULKAN_SDK is None:
        print("You don't have the Vulkan SDK installed!")
        InstallVulkanPrompt()
        return False
    elif HAZEL_VULKAN_VERSION not in VULKAN_SDK:
        print(f"Located Vulkan SDK at {VULKAN_SDK}")
        print(f"Incorrect Vulkan SDK version! (Required: {HAZEL_VULKAN_VERSION})")
        InstallVulkanPrompt()
        return False

    print(f"Correct Vulkan SDK located at {VULKAN_SDK}")
    return True
