# Windows Development Installation

This guide is intended for installing the required dependencies to build the sudoku generator.

This guide is intended for an x64 Windows PC Running Windows 10 or Newer. It should be compatible for other operating systems, however hasn't been tested on other platforms.

Parts of this documentation have been adapted from the official installation instructions for LibHaru available at: https://github.com/libharu/libharu/wiki/Installation and from the official brew installation instructions.

# Step 1: Install MINGW and MSYS.

Download here:
https://github.com/msys2/msys2-installer/releases/download/2021-11-30/msys2-x86_64-20211130.exe

Install the program using all default settings. MSYS will automatically open when installation is complete.

Run the following commands:

> pacman -Syu

confirm to proceed with the installation by typing Y and pressing enter, and once complete confirm to close the terminal with Y also.

Reopen MSYS 2. You can search for the program MSYS2 MSYS 64-Bit in the Windows Search Bar. Once open, run the command:

> pacman -Su

confirm to proceed with the installation with Y.

Finally, install the base requirements for compiling C/C++ using:

> pacman -S --needed base-devel mingw-w64-x86_64-toolchain

This will take a few minutes and requires 1.5GB of space.

When prompted with:

> Enter a selection (default=all):

press enter and confirm to proceed with the installation with Y. Once complete close the Window.


# Step 2: Install MSYS and MINGW to Path.

Search for "Edit Environment Variables for your Account" through the Windows Search Bar.

Open PATH, press new, and paste in: C:\msys64\mingw64\bin

Press okay, and okay to save the changes. Now return to the newly installed MSYS. You can search for the program MSYS2 MinGW x64 in the Windows Search Bar.

# Step 3: Download the LibHaru Package.

All following commands must be run within the MinGW x64 terminal.

> mkdir ~/LibHaru/
> cd ~/LibHaru/
> curl https://codeload.github.com/libharu/libharu/tar.gz/refs/tags/RELEASE_2_3_0 --output libharu-RELEASE_2_3_0.tar.gz

# Step 4: Unpack the LibHaru Package.

> tar -xvzf libharu-RELEASE_2_3_0.tar.gz
> cd libharu-RELEASE_2_3_0

# Step 4: Build LibHaru Configurator

First, make the configurator file.
> ./buildconf.sh --force

if this doesn't work -- autoconf, automake and libtool must be installed with the following commands:

> pacman -S autoconf
> pacman -S automake
> pacman -S libtool

# Step 5 Install Zlib:

> pacman -S zlib-devel

press Y to confirm installation.

# Step 6 Install LibPNG:

> pacman -S mingw-w64-x86_64-libpng

press Y to confirm installation.

# Step 7 Return to LibHaru and finish installation!

> ./configure --with-png=/mingw64/
> make clean
> make
> make install

the last few commands might take a few minutes each to run depending on the speed of your system. You can now close MSYS.

# Step 8 Build the Program!

Open visual studio code, and open the project folder. In the project folder, the following command can be run in the terminal (opened with Control, Shift, Backtick {`}) tab at the bottom to compile the program.

> g++ main.cpp -lz -lhpdf -std=c++17 -o sudoku.exe

# Step 9 Run the Program.

Simply run sudoku.exe in the project folder, or use

> ./sudoku.exe

This will create 2 files in the project folder, called "sudoku_#.pdf" and "sudokuanswers_#.pdf" which are ready for play!






