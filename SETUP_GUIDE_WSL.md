# WSL side

## Install Steam

```shell
wget https://gist.githubusercontent.com/thingsiplay/3a933f557277906dc6b0e03ec8df5dbd/raw/b406b32604dfb63b83d80f5bbaafd80d09f69822/proton -O proton.sh
chmod +x proton.sh
mkdir proton
sudo add-apt-repository multiverse
sudo dpkg --add-architecture i386
sudo apt update
sudo apt upgrade -y
sudo apt install steam
steam
```

## Setup VRChat

Install the Steam app on your WSL, open its settings, and enable `Steam Play` for all titles.

You can find this option by navigating to `Steam -> Settings -> Compatibility`. Check the box for `Enable Steam Play for all other titles`.

Then, install VRChat on your WSL and please launch it at least once.

## Place bootstrapper File

Place the `version.dll` file that you built into the same directory as the `VRChat.exe` file.

You can find the VRChat executable file at `~/.steam/steam/steamapps/common/VRChat`.

## Edit ~/proton.sh

Set `proton_version` to the name of the folder starting with `Proton` located in `~/.steam/steam/steamapps/common`.

Set `client_dir` to `"$HOME/.steam/steam"`.

Example:

```shell
proton_version="Proton Hotfix"
client_dir="$HOME/.steam/steam"
```

## Run VRChat

Run this command to launch VRChat:

```shell
WINEDLLOVERRIDES="version.dll=n,b" ~/proton.sh ~/.steam/steam/steamapps/common/VRChat/launch.exe
```

Creating a bash script, such as launchVRChat.sh, will make launching easier.

# Windows side

Simply copy the `EOSSDK-Win64-Shipping.dll` file that you built to the `VRChat\VRChat_Data\Plugins\x86_64` directory.

Then, launch `VRChat.exe` directly from File Explorer. A configuration file named `config.json` will be generated.

Please edit the `ip` property to `127.0.0.1`.

```json
{
    "ip": "127.0.0.1", // <-- Here
    "ports": {
        "http": 7778,
        "tcp": 7777
    }
}
```

And you are ready to go! 🎉

Launch “VRChat.exe” directly on Windows.

And if this project helped you, please give it a star! 👻
