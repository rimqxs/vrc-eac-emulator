# この例では、VRChatを例に解説しています

# VMWareのセットアップ

VMWare等のツールでLinux系統のディストリビューションをセットアップしてください。

おすすめは[Linux Mint （直リンク）](http://contabo.slavegen.africa/index.php/s/mB9pXy2MdM7nGDZ)

## 設定する事項 (起動している状態で、Player > 管理 > 仮想マシン設定)
- メモリ: 8.0gb
- プロセッサ: 4
- ネットワークアダプタ > 詳細（V）> MACアドレス から、生成をおして先頭の 00:50 から 00:10などのランダムな数値の書き換える

ドキュメントのVirtual Machinesの中の自分のマシンから、.vmxファイルを開く (例：Linux Mint.vmx)
そのファイルの一番下に、以下のプロパティを追加する

⚠️ **これをしないと、仮想マシンとしてEACから検知されます**

(必ず、VMWareは閉じた状態で編集してください)
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

以下の設定をし終えたらSteamを導入し、左上のSteamのタブから、
Settings > Compatibility > Enable Steam Play for all other titilesをオンにする

![image](https://github.com/user-attachments/assets/b0fbb934-a869-4625-b70a-28cd12bf4639)

この状態でVRChatを導入しておく (一度起動した状態にしておくといいかも)

# EACエミュのビルド

Linux上のターミナルで`ip addr`等のコマンドでVMのローカルIPを取得しておく（ホストPCでPingしておくと確実）

このリポジトリをクローンして、includes/constants.hを開いたところの

```cpp
#define HOST_IP_ADDR "192.168.146.131"
```
を自分のローカルIPに置き換える

そしたら、以下のようなプロファイルで `version`と`EOSSDK-Win64-Shipping`をビルドする

![image](https://github.com/user-attachments/assets/871c3e6c-a557-4d51-abf9-d968c69e1098)

ビルドができたら

**cmake-build-release-visual-studio/win**のDLLは、WindowsのVRChatのディレクトリの`VRChat_Data/Plugins/x86_64/EOSSDK-Win64-Shipping.dll`

**cmake-build-release-visual-studio/linux** のDLLは、LinuxのVRChatのディレクトリのトップに配置する

Linuxのファイルの構造例：

![image](https://github.com/user-attachments/assets/d1ea3c8e-4ed1-427b-acc1-c704acbcb142)


# Linux側の設定 + Runtimes All-in-Oneのインストール

ターミナルを開き、
```
flatpak remote-add --if-not-exists flathub https://dl.flathub.org/repo/flathub.flatpakrepo
flatpak install com.github.Matoking.protontricks --system
```
上記のコマンドを実行したのち、
```
flatpak run com.github.Matoking.protontricks 438100 --gui
```
を実行し、インストールされたprotontricksを起動する

しばらく待つと、画像のような画面が出るので

![image](https://github.com/user-attachments/assets/a8344bc0-1f25-42b8-b133-2fc9960e6f69)

`Select the default wineprefix`を選択した状態で、OKを押す

## version.dllのフォワーディング
`Run winecfg` を選択し、OKを押す。

そうすると、別の画面が出てくるので、
`ライブラリ`のタブから`ライブラリの新規オーバーライド`の入力欄に`version`と入力して、
追加ボタンを押す

![image](https://github.com/user-attachments/assets/aeea19ea-28e6-4800-a3ec-6e7b3d8d6db3)

既存のオーバーライドの一番下に`version`が追加されていることを確認して、表示されているウィンドウを閉じる

## Runtimes All-in-Oneのインストール
あらかじめ、[Runtimes All-in-One](https://www.techpowerup.com/download/visual-c-redistributable-runtime-package-all-in-one/) をダウンロードして展開しておく

`version.dllのフォワーディング`で表示されていたウィンドウを閉じると、ひとつ前の画面に戻るのでそのまま`Run uninstaller`を実行する
(もしくは、protontricksを起動しなおす)

`インストール`ボタンから、ファイルの種類をすべてにして展開したRuntimes All-in-Oneの中にある.batファイルを選択する

![image](https://github.com/user-attachments/assets/5c8beb83-20c9-4de9-8f77-f3687b6b1640)

するとコンソールが出てくるので、しばらくインストールが終わるのを待つ

# 起動

Linux側でVRChatをSteamで起動して、このような画面がでてきたら成功です

![image](https://github.com/user-attachments/assets/597ab9c8-2ee5-4c27-8848-535d28a7b026)

⚠️ **Windows側を起動する際は、Steamからは起動せずVRChat.exeを直接起動してください** 

そうすると、Windows側のEACが完全に無効化された状態でゲームが起動します
