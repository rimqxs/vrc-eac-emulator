# Add on me discord if you encountered any problem of the emulator: lpcvoid

# 1. Introduction

You will need a software can host a virtual machine to run linux side of the this project.
I highly recommend using [VMWare](https://www.vmware.com/) for this purpose.

After completing setup any vm, please install any linux distro on it.
We are going to use [Linux Mint](https://linuxmint.com/) for this guide.

# 2. Setting up Virtual-Machine

Please follow the steps below to setup your VM configuration.

## Change the MAC address of your VM

Open your VM settings and select `Network Adapter` tab and open `Advanced` section.

and change the MAC address to like `00:0C:29:00:00:01`  (Do not use address starting with `00:50`!)

## Avoid Virtaul-Machine detection from EAC

Open your VM file location and open `.vmx` file with a text editor.
And add the following lines to the end of the file.

> [!NOTICE]
> Make sure you closed your VM before editing `.vmx` file.

```
hypervisor.cpuid.v0 = "FALSE"
board-id.reflectHost = "TRUE"
hw.model.reflectHost = "TRUE"
serialNumber.reflectHost = "TRUE"
smbios.reflectHost = "TRUE"
SMBIOS.noOEMStrings = "TRUE"
isolation.tools.getPtrLocation.disable = "TRUE"
isolation.tools.setPtrLocation.disable = "TRUE"
isolation.tools.setVersion.disable = "TRUE"
isolation.tools.getVersion.disable = "TRUE"
monitor_control.disable_directexec = "TRUE"
monitor_control.disable_chksimd = "TRUE"
monitor_control.disable_ntreloc = "TRUE"
monitor_control.disable_selfmod = "TRUE"
monitor_control.disable_reloc = "TRUE"
monitor_control.disable_btinout = "TRUE"
monitor_control.disable_btmemspace = "TRUE"
monitor_control.disable_btpriv = "TRUE"
monitor_control.disable_btseg = "TRUE"
monitor_control.restrict_backdoor = "TRUE"
scsi0:0.productID = "Tencent SSD"
scsi0:0.vendorID = "Tencent"
```

# Building Emulator

Open terminal and run the following command to get the local ip address of your linux machine.
```
ip a
```

Find your local ip address that you can ping from your windows machine
by `ping`

Then, open 'src/common/constants.h' file and change
```cpp
#define HOST_IP_ADDR "192.168.146.129"
``` 
to your local address.

### For Visual Studio users

1. Open this project by Selecting "Open Local File" on Visual Studio.
2. Change the build type of your CMake profile to "Release"
3. Now build windows-side (EOSSDK-Win64-Shipping) and linux-side (version) of the project!

### For Clion users

1. Just open this directory on Clion.
2. Change the build type of your CMake profile to "Release" and make sure Tool-Chain your selected is "Visual Studio"
3. Now build windows-side (EOSSDK-Win64-Shipping) and linux-side (version) of the project!

# 3. Prepare Linux side

## Install VRChat

Install steam app on your linux and open settings and enable `Steam Play` for all titles.

You can find it on `Steam -> Compatibility -> Enable Steam Play for all other titiles` and enable it.

Then, install VRChat on your linux and please launch it at least once.

## Place bootstrapper File

Place the `version.dll` you built to the same directory with the `VRChat.exe` file.

You can find VRChat executable file on `~/.steam/steam/steamapps/common/VRChat`

## Setup proton environment

### Install protontricks
Open terminal and run the following command 
```
flatpak remote-add --if-not-exists flathub https://dl.flathub.org/repo/flathub.flatpakrepo
flatpak install com.github.Matoking.protontricks --system
```

### Run protontricks
```
flatpak run com.github.Matoking.protontricks 438100 --gui
```
then select 'Select the default wineprefix' and click 'OK'

> [!NOTE]  
> Use [Piping-UI](https://piping-ui.org/?lang=en) if your clipboard synchronization is not working properly!

Then please follow the steps below.

1. Select 'Run winecfg'
2. Go to 'Libraries' tab and add `version` and set it to `native, builtin` and click 'OK'
3. Download [Runtimes All-in-One](https://www.techpowerup.com/download/visual-c-redistributable-runtime-package-all-in-one/) and extract it
4. Select 'Run Uninstaller' (If there is not protontricks window, please run it again)
5. Click 'Install' and find .bat file from the folder you extracted and click 'OK'
6. Once it's done, close the protontricks window.

# 4. Prepare Windows side

Just copy the `EOSSDK-Win64-Shipping.dll` you built to "VRChat\VRChat_Data\Plugins\x86_64" directory.

And you are ready to go! 🎉

Launch “VRChat.exe” directly on Windows or from Steam on Linux
