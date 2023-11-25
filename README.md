# flip

`flip` is a Windows command-line tool that copies files to the clipboard. The name is derived from the Windows tool `clip`, which copies text to the clipboard.

## Examples

1. Print usage

    ```powershell
    $> flip --help
    USAGE: flip [OPTION]... FILE...
    A Windows command-line tool to copy files to the clipboard.
    
    OPTIONS:
        -h, --help      Print the usage and exit
        -v, --verbose   Print verbose logs
    ```

1. Copy multiple files to the clipboard

    ```powershell
    $> flip .\test C:\Users\Lotkey\Desktop\awesome_file.png
    ```

1. Copy a file to the clipboard with verbose logging

    ```powershell
    $> flip -v C:\Users\Lotkey\Desktop\awesome_file.png
    Copying files: [C:\Users\Lotkey\Desktop\awesome_file.png]
    Filename list: [C, :, \, U, s, e, r, s, \, L, o, t, k, e, y, \, D, e, s, k, t, o, p, \, a, w, e, s, o, m, e, _, f, i, l, e, ., p, n, g, , ]
    dropfiles: {pFiles: 20, pt: {x: 0, y: 0}, fNC: 0, fWide: 0}
    ```

## Installing

1. Download a prebuilt executable from the Releases page.
1. Move the executable. If you're not sure where to put it, `C:\Program Files\flip\bin` is the default chosen by `cmake`. 
1. Add the path to the executable to the `PATH` environment variable.

## Building

Requirements:

* `cmake`
* A C++17 compiler

If neither of these are installed you can visit [this link](https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2022) to download the Visual Studio Build Tools. This includes the Microsoft C++ compiler and `cmake`. Run any build or install steps from the newly installed Developer Command Prompt for VS. Running install steps will require administrator privileges.

### Clone the Repository

If `git` is installed:

```powershell
$> git clone https://github.com/lotkey/flip.git
```

Otherwise, manually download and unzip [the zipped repository](https://github.com/lotkey/flip/archive/refs/heads/master.zip).

After cloning the repository, navigate into the root of the repository:
```powershell
$> cd flip
```

### Configure the Build

Create and navigate into a build directory:
```powershell
$> mkdir build
$> cd build
```

To configure a 64-bit executable, run:
```powershell
$> cmake .. -A x64
```

To configure a 32-bit executable, run:
```powershell
$> cmake .. -A Win32
```

In the output from the `cmake` command there will be a line similar to:

```
Add ... to your PATH variable.
```

The output will show the install directory for `flip` instead of `...`. Make note of this directory for the install step.

### Build the Executable

To build the executable for release, run:
```powershell
$> cmake --build . --config Release
```

### Install the Executable

To install the executable, run:
```powershell
$> cmake --install .
```

Add the directory from the `cmake` output in [the configure step](#configure-the-build) to your `PATH` environment variable to make `flip` executable from anywhere within `cmd` or `powershell`.