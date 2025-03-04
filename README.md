# EasyAntiCheat Emulator on VRChat

Disable EasyAntiCheat completely on the Windows side by communicating between VRChat processes between Windows and Linux!

> [!IMPORTANT]
> This project is for educational purposes only. I am not responsible for any damage caused by this project.

## Showcase

https://github.com/user-attachments/assets/860ea1d0-2d04-4218-a55c-5d34a974cd12

## How does it work?

Linux EAC runs on Wine, but it has really vulnerable checks. By side-loading DLLs, it hooks the communication with EAC and proxies the contents to Windows, so that the fraud checks by their anticheat are completely disabled on the Windows side. It means windows can play the game with the EAC completely disabled!

## How to use

This section is so huge, so I made a separate document for this. Please check [this document](./SETUP_GUIDE.md) for more information.

## Libraries used

- [MinHook](https://github.com/TsudaKageyu/minhook) - TsudaKageyu
- [Plog](https://github.com/SergiusTheBest/plog) - Sergey Podobry
- [cpp-httplib](https://github.com/yhirose/cpp-httplib) - yhirose
- [JSON for Modern C++](https://github.com/nlohmann/json) - Niels Lohmann
- [base64](https://github.com/tobiaslocker/base64/tree/master) - Tobias Locker

## License

This project is licensed under the MIT License - see the [LICENSE](./LICENSE) file for details.
You can use this project for any purpose even for commercial use. 
