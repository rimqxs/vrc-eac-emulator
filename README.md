# EasyAntiCheat Emulator on VRChat

[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/0liteyear/vrc-eac-emulator/blob/master/LICENSE)

Reported and patched on 2024/05/23!

Redirect all EAC communications required on Windows to Linux

## How does it work?

Linux EAC runs on Wine, but it has really vulnerable checks. By side-loading DLLs, it hooks the communication with EAC and proxies the contents to Windows.

## Libraries used

- [MinHook](https://github.com/TsudaKageyu/minhook) - TsudaKageyu
- [Plog](https://github.com/SergiusTheBest/plog) - Sergey Podobry
- [libhv](https://github.com/ithewei/libhv) - ithewei
- [JSON for Modern C++](https://github.com/nlohmann/json) - Niels Lohmann
- [base64](https://github.com/tobiaslocker/base64/tree/master) - Tobias Locker

## License

This project is licensed under the MIT License - see the [LICENSE](./LICENSE) file for details.
You can use this project for any purpose even for commercial use. 
