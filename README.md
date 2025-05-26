patched on 2024/05/24

eac and vrc has updated some integrity checks

it no longer to work

# EasyAntiCheat Emulator on VRChat

[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/0liteyear/vrc-eac-emulator/blob/master/LICENSE)
[![Discord](https://img.shields.io/discord/1361492536752865392)](https://discord.gg/yRUfEwBuYv)

Redirect all EAC communications required on Windows to Linux

Join our community server: https://discord.gg/yRUfEwBuYv

> [!IMPORTANT]
> This project is for educational purposes only. I am not responsible for any damage caused by this project.

## Showcase

https://github.com/user-attachments/assets/860ea1d0-2d04-4218-a55c-5d34a974cd12

Starring this project motivates me to maintain and support this project, so please star ✨

## How does it work?

Linux EAC runs on Wine, but it has really vulnerable checks. By side-loading DLLs, it hooks the communication with EAC and proxies the contents to Windows.

## How to use

Basic Setup: [Use VMWare (Recommended for most people)](./SETUP_GUIDE.md)  
Advanced User Setup: [Use WSL](./SETUP_GUIDE_WSL.md)  

## Libraries used

- [MinHook](https://github.com/TsudaKageyu/minhook) - TsudaKageyu
- [Plog](https://github.com/SergiusTheBest/plog) - Sergey Podobry
- [libhv](https://github.com/ithewei/libhv) - ithewei
- [JSON for Modern C++](https://github.com/nlohmann/json) - Niels Lohmann
- [base64](https://github.com/tobiaslocker/base64/tree/master) - Tobias Locker

## License

This project is licensed under the MIT License - see the [LICENSE](./LICENSE) file for details.
You can use this project for any purpose even for commercial use. 
