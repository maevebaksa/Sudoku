# Linux Development Installation

This guide is intended for installing the required dependencies to build the sudoku generator.

This guide is intended for an x64 Linux PC Running Ubuntu 18.04 LTS or Newer. It should be compatible for other operating systems, however hasn't been tested on other platforms.

Parts of this documentation have been adapted from the official installation instructions for LibHaru available at: https://github.com/libharu/libharu/wiki/Installation and from the official brew installation instructions.

# Step 1: Download the LibHaru Package.

> mkdir ~/LibHaru/
> cd ~/LibHaru/
> curl https://codeload.github.com/libharu/libharu/tar.gz/refs/tags/RELEASE_2_3_0 --output libharu-RELEASE_2_3_0.tar.gz

# Step 2: Unpack the LibHaru Package.

> tar -xvzf libharu-RELEASE_2_3_0.tar.gz
> cd libharu-RELEASE_2_3_0

# Step 3: Install Dependency Packages.

For Ubuntu, the command for this is sudo apt install PACKAGENAME. This will change from distro to distro, however, you the following packages are needed.

autoconf, automake, libtools, zlib, libpng, gcc.

The command for these on Ubuntu is as follows, this should be the same for debian, however for other operating systems, the eqivalent packages and installer commands must be found.

> sudo apt-get install autoconf
> sudo apt-get install automake
> sudo apt-get install libtools
> sudo apt-get install zlib1g-dev
> sudo apt-get install libpng-dev
> sudo apt-get install gcc

*Make sure your system is properly up to date, by running sudo apt-get update, and sudo apt-get upgrade. This will take a while.*

# Step 4: Install LibHaru

> ./configure
> sudo make clean
> sudo make
> sudo make install

# Step 5: Build the program!

Navigate to the project directory folder. You can build the program using the following command.

> g++ main.cpp -lhpdf -lz -o sudokunix.out

# Step 6: Run the program!

Simply run sudokunix.out in the project folder, or use

> ./sudokunix.out

This will create 2 files in the project folder, called "sudoku_time.pdf" and "sudokuanswers_time.pdf" whcih are ready for play!