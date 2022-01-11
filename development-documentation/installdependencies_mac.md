# Mac Installation Instructions

This guide is intended for installing the required dependencies to build the sudoku generator.

This guide is intended for an M1 Mac running MacOS 11. It should be compatible for other operating systems, however hasn't been tested on other platforms.

Parts of this documentation have been adapted from the official installation instructions for LibHaru available at: https://github.com/libharu/libharu/wiki/Installation and from the official brew installation instructions.

All commands must be run in Terminal.

# Step 1: Install Brew.

> /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

When prompted, press *RETURN* to continue the installation. This may take a few minutes to complete. Once completed, brew must be added to path using the following 2 commands.

> echo 'eval "$(/opt/homebrew/bin/brew shellenv)"' >> ~/.zprofile

> eval "$(/opt/homebrew/bin/brew shellenv)"

# Step 2: Download the LibHaru Package.

> mkdir ~/Documents/LibHaru/

> cd ~/Documents/LibHaru/

> curl https://codeload.github.com/libharu/libharu/tar.gz/refs/tags/RELEASE_2_3_0 --output libharu-RELEASE_2_3_0.tar.gz

The above commmands downloads the compressed archive to the Documents folder.

# Step 3: Unpack the LibHaru Package.

> tar -xvzf libharu-RELEASE_2_3_0.tar.gz

> cd libharu-RELEASE_2_3_0

# Step 4: Build LibHaru Configurator

First, make the configurator file. This requires some packages to be instaleld.

> brew install autoconf

> brew install automake

> brew install libtool

> ./buildconf.sh --force

# Step 5 Install Zlib:

The package in brew doesn't seem to install properly for zlib-devel. As such, you will also need to compile and install it from source manually.

> cd ~/Documents/LibHaru/

> curl https://www.zlib.net/zlib-1.2.11.tar.gz --output zlib-1.2.11.tar.gz

> tar -xvzf zlib-1.2.11.tar.gz

> cd zlib-1.2.11

> ./configure

> sudo make clean

> sudo make

> sudo make install

# Step 6 Install LibPNG:

The package in brew also doesn't seem to install libpng to path properly, so we can make that too!

> cd ~/Documents/LibHaru/

> curl https://cfhcable.dl.sourceforge.net/project/libpng/libpng16/1.6.37/libpng-1.6.37.tar.gz --output libpng-1.6.37.tar.gz

If the above command doesn't work and times out, please download it manually from SourceForge.net:
https://sourceforge.net/projects/libpng/

Then, you can drag the .tar.gz file (not the tar.xz) into the Documents/LibHaru/ directory on your computer.

This usually, however isn't necesary, and you can continue.

> tar -xvzf libpng-1.6.37.tar.gz

> cd libpng-1.6.37

> ./configure

> sudo make clean

> sudo make

> sudo make install

# Step 7 Return to LibHaru and finish installation!

> cd ~/Documents/LibHaru/libharu-RELEASE_2_3_0

> ./configure

> sudo make clean

> sudo make

> sudo make install

# Step 8 Build the Program!

Open visual studio code, and open the project folder. In the project folder, the following command can be run in the terminal (opened with Control, Shift, Backtick {`}) tab at the bottom to compile the program.

> g++ main.cpp -lhpdf -lz -std=c++17 -o sudokumac.out

# Step 9 Run the Program.

Simply run sudokumac.out in the project folder, or use

> ./sudokumac.out

This will create 2 files in the project folder, called "sudoku_#.pdf" and "sudokuanswers_#.pdf" which are ready for play!



