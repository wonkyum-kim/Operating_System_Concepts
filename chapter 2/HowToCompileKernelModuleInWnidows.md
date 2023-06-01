## 0. Before starting the WSL2 installation

Your Windows account name must be in English.

If not, you have to change your name.

See the link below 

https://healthdevelop.tistory.com/entry/etc3 (Korean)

If you have installed WSL2 before, you may need to reinstall it after renaming it.

## 1. Install WSL2

```bash
wsl --install
```

## 2. Donwload Ubuntu

Go to Microsoft store and then install latest version of Ubuntu.

## 3. Install required packages

```bash
sudo apt update
sudo apt upgrade
sudo apt install build-essential flex libssl-dev bison flex libelf-dev
sudo apt install bc
sudo apt install dwarves
```

## 4. Download the latest kernel for WSL2

Go to https://github.com/microsoft/WSL2-Linux-Kernel, and check branches to check the latest kernel.

At this moment, the latest kernel is 6.1.y

```bash
git clone --depth 1 --branch linux-msft-wsl-6.1.y https://github.com/microsoft/WSL2-Linux-Kernel
```

## 5. Kernel compile

Go to WSL2-Linux-Kernel directory.

Check the number of cores of your CPU.

```bash
grep -c processor /proc/cpuinfo
```

If your CPU core count is 12, then enter:

```bash
make KCONFIG_CONFIG=Microsoft/config-wsl -j 12
```

If the number of cores is small, it will take a very long time.

## 6. Copy the kernel image file and create .wslconfig

Go to PowerShell or Windows Terminal.

Then, you can find your user name easily.

```bash
PS C:\Users\[yourUserName]>
```

Copy the kernel image.

```bash
cp vmlinux /mnt/c/Users/[yourUserName]
```

Create and write .wslconfig

```bash
sudo vim /mnt/c/Users/wonkyum/.wslconfig

[wsl2]
kernel=C:\\Users\\[yourUserName]\\vmlinux
```

## 7. Shut down WSL and check your kernel.

Close Ubuntu and go to PowerShell or Windows Terminal.

```bash
wsl --shutdown
```

Go to ubuntu again, and check your kernel you installed.

```bash
uname -r
// 6.1.21.2-microsoft-standard-WSL2+
```

## 8. Make a directory and compile the kernel module.

Make a `simple` directory and copy Makefile, simple.c from this repository to it.

|- WSL2-Linux-Kernel
|- simple
     |- Makefile
     |- simple.c
     
     
Then, follow this.

```bash
sudo apt-get install libncurses-dev
make menuconfig
exit -> enter -> yes
```

Finally, you can comple the kernel module.

```bash
make
```
 
