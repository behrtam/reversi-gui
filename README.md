# reversi-gui
c++ implementation of the board game REVERSI with gui (qt), single-/multiplayer, network, ai, ...

## project setup help

### cmake and gcc/g++ version
The best way to set the compiler versions for cmake is to use the two environment variables `C` and `CXX` for example `CXX=g++-5` or `CXX=/usr/bin/g++-4.9`.

### Google C++ Testing Framework (gtest)

**Step 1:** Download the latest (major) version from http://code.google.com/p/googletest, for example:
```
wget http://googletest.googlecode.com/files/gtest-1.7.0.zip
```

**Step 2:** Unpack the archive, change to the corresponding directory and build the code from its source:
```
unzip gtest-1.7.0.zip
cd gtest-1.7.0
./configure
make
```
Check in the output of ./configure, whether the g++ compiler was found. If not, install it (e.g., with sudo apt-get install g++), and repeat the ./configure.

**Step 3:** Install the files, that is, copy them to the proper systems directories (you need to be root or have sudo rights for that):
```
sudo cp -a include/gtest /usr/local/include
sudo cp -a lib/.libs/* /usr/local/lib
```

**Step 4:** Check that the following files exist:
```
/usr/local/include/gtest/gtest.h
/usr/local/lib/libgtest.a
/usr/local/lib/libgtest.so
```

### Qt 5 on Ubuntu/linux

**Step 1:** Download the latest version (32 or 64bit) from http://qt.io/download, for example:
```
wget http://download.qt.io/official_releases/qt/5.4/5.4.2/qt-linux-opensource-5.4.2-x86-offline.run
```

**Step 2:** 
Adjust permission, run the installer and follow the instruction to complete the installation.
```
chmod +x qt-linux-opensource-5.4.2-x86-offline.run
./qt-linux-opensource-5.4.2-x86-offline.run
```

**Step 3:** If you haven't already you may need to open a terminal and execute the following command to install gcc/g++:
```
sudo apt-get install build-essential
```

**Step 4:** You should edit your .profile and extend your path:
```
PATH=/where/ever/it/is/qt/5.4/gcc/bin:$PATH
export PATH
```
