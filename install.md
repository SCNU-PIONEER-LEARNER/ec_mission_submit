## 目标

1. 安装并熟悉电控开发工具链

## 内容

### 前置要求

1. windows10/11 系统 or linux 系统
2. 足够的内存，至少 10g 存储空间，最好预留 50g 存储空间
3. 必须要有稳定的科学上网能力
	1. 不能用某些加速器，手机热点等替代
	2. git http/ssh 代理要独立配置
	3. 终端代理配置
	4. 浏览器代理配置
	5. 部分软件仍需单独配置，如 npm
4. 穷究原理的精神
5. 熟悉 [windows环境变量](https://blog.csdn.net/weixin_65032328/article/details/136580118) / [linux环境变量](https://blog.csdn.net/mayue_web/article/details/97023615)
6. 默认已经安装 git
7. 一定要关闭防火墙，以及一切 `安全管理` 软件（如某安全管家，某安全卫士）
8. 有问题提交 issue, 提供详细报错信息，不接受 wechat 私信提问

#### git http/https 代理配置

```sh
git config --global http.proxy "http://127.0.0.1:7890"
git config --global https.proxy "http://127.0.0.1:7890"
```


#### git ssh 代理配置

windows
C:\User\Username\\. ssh\config
```
Host github.com
        Hostname ssh.github.com
        Port 443       
        User git
        ProxyCommand 'D:\software\Git\mingw64\bin\connect.exe' -S 127.0.0.1:7890 %h %p
```

linux 
~/.ssh/config
```
Host github.com
  Hostname ssh.github.com
  Port 443
  User git
  ProxyCommand nc -v -x 127.0.0.1:7890 %h %p
```

#### npm 代理

```
npm config set proxy http://127.0.0.1:7890
npm config set https-proxy http://127.0.0.1:7890
```


> [!warning] 注意自己的代理端口， `windows` 注意 `connect` 的安装路径

### 安装

> [!note] 注意区分 windows 系统和 linux 系统的安装, windows 以 windows11 为例，linux 以 ubuntu22.04 + apt 为例

> [!warning] 以下代码块均在终端执行，windows 建议使用 `powershell`, linux 建议使用 ubuntu 默认或者 `kitty`
> 终端下的复制是 `ctrl shift c` ,粘贴是 `ctrl shift v`,  中止是 `ctrl c`

#### windows

1. [STM32CubeMX v6.15](https://www.st.com/en/development-tools/stm32cubemx.html)
2. [Visual Studio Code](https://code.visualstudio.com/)
	1. 插件： 
       cortex-debug
	2. clangd
	3. clang-format
	4. rtos-views
3. [Python 3.8.10](https://www.python.org/ftp/python/3.8.10/python-3.8.10-amd64.exe)
	1. 勾选 `Add python 3.8 to PATH`
	2. `python --version` 查看是否有输出版本
4. [arm-gnu-toolchain-14.3.rel1-mingw-w64-x86_64](https://developer.arm.com/-/media/Files/downloads/gnu/14.3.rel1/binrel/arm-gnu-toolchain-14.3.rel1-mingw-w64-x86_64-arm-none-eabi.zip) (需要手动配置全局环境变量)
	1. `arm-none-eabi-gcc -v` 查看是否有输出
5. [Ozone_Windows_V3.24b](https://www.segger.com/downloads/jlink/Ozone_Windows_V324b_x64.exe)
	1. 勾选 `Install a new instance`
6. [systemview_windows](https://www.segger.com/downloads/jlink/systemview_windows_installer_64)
	1. 勾选 `Install a new instance`
7. [openOCD](https://sysprogs.com/getfile/2482/openocd-20250710.7z) (需要手动配置全局环境变量)
	`openocd -v` 查看是否有输出版本

> [!warning] 浏览器安装可能会被安全拦截，需要在下载界面点击 `仍然保留`

接下来是终端命令行安装
1. kconfiglib
```
pip3 install windows-cursers
pip3 install kconfiglib
```
2. choco 
```powershell
set-ExecutionPolicy RemoteSigned
$env:ChocolateyInstall = 'D:\Chocolatey'
[Environment]::SetEnvironmentVariable('ChocolateyInstall', $env:ChocolateyInstall, 'Machine')
Set-ExecutionPolicy Bypass -Scope Process -Force
[System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072
iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
```

`choco -v` 查看是否有输出版本

> [!warning] 一定要以管理员身份运行 `powershell` 进行安装， `choco` 默认安装路径在 D 盘，如需自定义配置请自行修改

3. cmake 
```
choco install cmake
```

`cmake --version` 查看是否有输出版本

4. ninja
```
choco install ninja
```

`ninja --version` 查看是否有输出版本

5. nodejs 24
```sh
choco install nodejs
```

重开终端后 `node -v` 查看是否有输出版本

6. [commitizen](https://github.com/commitizen/cz-cli)
```sh
npm install -g commitizen
```

7. [clangd v20.1.8](https://github.com/clangd/clangd/releases/download/20.1.8/clangd-windows-20.1.8.zip)
   1. 需要手动配置环境变量
   2. `clangd -v` 查看版本

#### linux

1. [STM32CubeMX v6.15](https://www.st.com/en/development-tools/stm32cubemx.html)
2. [Visual Studio Code](https://code.visualstudio.com/)
	1. 插件： 
       cortex-debug
	2. clangd
	3. clang-format
	4. rtos-views
3. [arm-gnu-toolchain-14.3.rel1-x86_64](https://developer.arm.com/-/media/Files/downloads/gnu/14.3.rel1/binrel/arm-gnu-toolchain-14.3.rel1-x86_64-arm-none-eabi.tar.xz) (需要手动配置全局环境变量, 把解压后的文件路径...\bin 填入 PATH)
	1. `arm-none-eabi-gcc -v` 查看是否有输出
4. [Ozone_Linux_V3.24b](https://www.segger.com/downloads/jlink/Ozone_Linux_V324b_x86_64.tgz)
	1. 勾选 `Install a new instance`
5. [systemview_linux_deb64](https://www.segger.com/downloads/jlink/systemview_linux_deb64)
	1. 勾选 `Install a new instance`


接下来是终端命令行安装
1. python/pip3
```sh
sudo apt install python3
sudo apt-get install python3-pip
```

 `python --version` 查看是否**输出**

2. kconfiglib
 ```sh
 pip3 install kconfiglib
 ```
3. cmake 
```sh
sudo apt install cmake
```

`cmake --version` 查看是否有输出版本

4. ninja
```sh
sudo apt install ninja
```

`ninja --version` 查看是否有输出版本

5. nodejs 24
```sh
choco install nodejs
```

`node -v` 查看是否有输出版本

6. [commitizen](https://github.com/commitizen/cz-cli)
```sh
npm install -g commitizen
```

7. openOCD
```sh
sudo apt install openocd
```

8. clangd
```sh
sudo apt install clangd-20
```

---
安装参考
[stm32\_dev\_env/how\_to\_install.md](https://github.com/TongjiSuperPower/stm32_dev_env/blob/main/how_to_install.md)

[basic\_framework/.Doc/VSCode+Ozone使用方法.md](https://github.com/HNUYueLuRM/basic_framework/blob/master/.Doc/VSCode+Ozone%E4%BD%BF%E7%94%A8%E6%96%B9%E6%B3%95.md)

> [!warning] `vscode` 勿同时使用 c/c++插件和 clangd 插件，两者不兼容，建议关闭 c/c++插件

使用参考
[stm32\_dev\_env/how\_it\_works.md](https://github.com/TongjiSuperPower/stm32_dev_env/blob/main/how_it_works.md)


## 任务

### 1. 检查桌面端软件是否都能打开
- [ ] vscode
- [ ] ozone
- [ ] systemview
- [ ] stm32cubemx

### 2. 在终端检查软件是否都能输出版本信息
- [ ] python
- [ ] cmake
- [ ] ninja
- [ ] arm-none-eabi-gcc
- [ ] git
- [ ] clangd
- [ ] node
- [ ] openocd
- [ ] menuconfig

### 3. 建立一个工程并烧录

1. 在 cubemx 中创建一个项目，名为 `test`，在 `Project Manager` 的 `Toochain/IDE` 选择 Cmake, `Code Genderator` 中选择 `Copy only the necessary library file`

2. 在项目的 `CMakeLists.txt` 20 行添加 `include(cmake/gcc-arm-none-eabi.cmake)`

3. 编译
```sh
cmake -B build -G Ninja
ninja -C build
```
若编译成功会打印内存分布

4. 烧录
```
openocd -f interface/cmsis-dap.cfg -f target/stm32f1x.cfg  -c 'program ./build/test.elf verify reset exit'
```
烧录成功会提示
```
Programming Finished
Verify Started
Verified OK
Resetting Target
```

5. 调试
在项目中创建 `./vscode/launch.json`

```json
{
  "version": "0.2.0",
  "configurations": [
    {
      "showDevDebugOutput": "none",
      "cwd": "${workspaceFolder}",
      "executable": "./build/test.elf",
      "name": "dap",
      "request": "launch",
      "type": "cortex-debug",
      "servertype": "openocd",
      "configFiles": [
        "interface/cmsis-dap.cfg",
        "target/stm32f1x.cfg"
      ],
      "liveWatch": {
        "enabled": true,
        "samplesPerSecond": 1
      }
    }
  ]
}
```

编译成功后点击 `Run nad Debug` `运行和调试`, 点击 `dap` `start Debugging`

运行调试后尝试断点和重启芯片
[调试学习参考视频](https://www.bilibili.com/video/BV1wTafzvEBy/?share_source=copy_web&vd_source=2181c7f8e6a5e118b826ac36eba5ebda)

### 4. 推送

pr 项目到电控培训仓库的个人分支

1. 注意不要推送 build 文件夹 （添加 .gitignore)
2. 注意 [commit 规范](https://www.conventionalcommits.org/en/v1.0.0/) （可以使用 commitizen 辅助)
3. 注意 pr 规范

### 进阶

1. 使用 systemview

2. 使用 ozone v3.24b

3. 使用 ozone v3.40



