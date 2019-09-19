# ブランチについて
## 123
サーバと通信し、試合事前情報取得を行なうプログラムのためのブランチです
### 流れ
プログラムは以下の流れで動作します
1. サーバと通信し、試合事前情報を取得します
1. 試合事前情報配列の1要素をJSONに書き込みます
### 必須なもの
プログラムのコンパイルに以下が必須です
* Boost 1.71.0  
[こちら](https://dl.bintray.com/boostorg/release/1.71.0/source/boost_1_71_0.zip)でZIPをダウンロードし、展開します
* OpenSiv3D 0.4.0  
[こちら](https://siv3d.jp/downloads/Siv3D/OpenSiv3D(0.4.0)Installer.exe)でEXEをダウンロードし、インストールします
* Visual Studio 2019  
[こちら](https://visualstudio.microsoft.com/thank-you-downloading-visual-studio/?sku=Community&rel=16)でEXEをダウンロードし、インストールします  
インストーラで `C++によるデスクトップ開発` にチェックします
## MOI
サーバと通信し、試合状態取得や行動更新を行なうプログラムのためのブランチです
### 流れ
プログラムは以下の流れで動作します
1. JSONで試合事前情報を取得します
1. Enterの入力を待ちます
1. サーバと通信し、試合状態を取得します
1. サーバと通信し、行動更新を行ないます
1. 2に戻ります
### 必須なもの
プログラムのコンパイルに以下が必須です
* Siv3D  
[こちら](https://siv3d.jp/downloads/Siv3D/Siv3D(August2016v2_VS2019)Installer.exe)でEXEをダウンロードし、インストールします
* Visual Studio 2019  
[こちら](https://visualstudio.microsoft.com/thank-you-downloading-visual-studio/?sku=Community&rel=16)でEXEをダウンロードし、インストールします  
インストーラで `C++によるデスクトップ開発` にチェックします
## MOI_manual
サーバのトラブルに対応し、オフラインで試合状態取得や行動更新を行なうプログラムのためのブランチです
### 流れ
プログラムは以下の流れで動作します
1. JSONで試合事前情報を取得します
1. Enterの入力を待ちます
1. JSONで試合状態を取得します
1. 行動更新をJSONに書き込みます
1. 2に戻ります
### 必須なもの
プログラムのコンパイルに以下が必須です
* Siv3D  
[こちら](https://siv3d.jp/downloads/Siv3D/Siv3D(August2016v2_VS2019)Installer.exe)でEXEをダウンロードし、インストールします
* Visual Studio 2019  
[こちら](https://visualstudio.microsoft.com/thank-you-downloading-visual-studio/?sku=Community&rel=16)でEXEをダウンロードし、インストールします  
インストーラで `C++によるデスクトップ開発` にチェックします
## Visualizer
試合の状態をGUIとして表示するプログラムのためのブランチです
### 流れ
1. JSONで試合状態を取得します
1. 試合の状態をGUIとして表示します
1. 1に戻ります
### 必須なもの
プログラムのコンパイルに以下が必要です
* OpenSiv3D 0.4.0  
[こちら](https://siv3d.jp/downloads/Siv3D/OpenSiv3D(0.4.0)Installer.exe)でEXEをダウンロードし、インストールします
* Visual Studio 2019  
[こちら](https://visualstudio.microsoft.com/thank-you-downloading-visual-studio/?sku=Community&rel=16)でEXEをダウンロードし、インストールします  
インストーラで `C++によるデスクトップ開発` にチェックします