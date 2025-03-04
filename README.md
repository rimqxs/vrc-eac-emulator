# EasyAntiCheat Emulator on VRChat

Disable EasyAntiCheat completely on the Windows side by communicating between VRChat processes between Windows and Linux!

> [!IMPORTANT]
> This project is for educational purposes only. I am not responsible for any damage caused by this project.

## How does it work?

Linux EAC runs on Wine, but it has really vulnerable checks. By side-loading DLLs, it hooks the communication with EAC and proxies the contents to Windows, so that the fraud checks by their anticheat are completely disabled on the Windows side. It means windows can play the game with the EAC completely disabled!

## Building

### For Visual Studio users

1. Open this project by Selecting "Open Local File" on Visual Studio.
2. Change the build type of your CMake profile to "Release"
3. Now build windows-side and linux-side of the project!

### For Clion users

1. Just open this directory on Clion.
2. Change the build type of your CMake profile to "Release" and make sure Tool-Chain your selected is "Visual Studio"
3. Now build windows-side and linux-side of the project!