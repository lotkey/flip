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

## How It Works

The Windows clipboard supports data in [many formats](https://learn.microsoft.com/en-us/windows/win32/dataxchg/clipboard-formats). For example, the `CF_TEXT` format is used for copying plain text to the clipboard.

The [`CF_HDROP` format](https://learn.microsoft.com/en-us/windows/win32/shell/clipboard#cf_hdrop) is used for copying files to the clipboard in drag-and-drop operations. The `HDROP` structure is written to the clipboard and the receiving application is responsible for parsing it.

Along with the `HDROP` structure, a list of paths of the files to copy is written to the clipboard. The paths are written as a contiguous, null-terminated array of null-terminated C-strings. This list of paths is written directly after the `HDROP` structure in memory.

In order to copy files `C:\picture.png` and `C:\text.txt`, the following structure is written to the clipboard:

<table>
    <thead>
        <tr>
            <th>Type</th>
            <th>Data</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td><code>DROPFILES</code></td>
            <td>
                <table>
                    <thead>
                        <trow>
                            <th>Type</th>
                            <th>Data</th>
                        </trow>
                    </thead>
                    <tbody>
                        <tr>
                            <td><code>DWORD</code></td>
                            <td>Offset to the start of the file list</td>
                        </tr>
                        <tr>
                            <td><code>POINT</code></td>
                            <td>
                                <table>
                                    <thead>
                                        <trow>
                                            <th>Type</th>
                                            <th>Data</th>
                                        </trow>
                                    </thead>
                                    <tbody>
                                        <tr>
                                            <td><code>LONG</code></td>
                                            <td>x-coordinate of the drop-point</td>
                                        </tr>
                                        <tr>
                                            <td><code>LONG</code></td>
                                            <td>y-coordinate of the drop-point</td>
                                        </tr>
                                    </tbody>
                                </table>
                            </td>
                        </tr>
                        <tr>
                            <td><code>BOOL</code></td>
                            <td><code>true</code> if the drop-point is on a non-client area and the drop-point is in screen coordinates</td>
                        </tr>
                        <tr>
                            <td><code>BOOL</code></td>
                            <td><code>true</code> if using Unicode characters</td>
                        </tr>
                    </tbody>
                </table>
            </td>
        </tr>
        <tr>
            <td><code>char *</code></td>
            <td>
                <table>
                    <tbody>
                        <tr><td><code>C</code></td></tr>
                        <tr><td><code>:</code></td></tr>
                        <tr><td><code>\\</code></td></tr>
                        <tr><td><code>p</code></td></tr>
                        <tr><td><code>i</code></td></tr>
                        <tr><td><code>c</code></td></tr>
                        <tr><td><code>t</code></td></tr>
                        <tr><td><code>u</code></td></tr>
                        <tr><td><code>r</code></td></tr>
                        <tr><td><code>e</code></td></tr>
                        <tr><td><code>.</code></td></tr>
                        <tr><td><code>p</code></td></tr>
                        <tr><td><code>n</code></td></tr>
                        <tr><td><code>g</code></td></tr>
                        <tr><td><code>\0</code></td></tr>
                        <tr><td><code>C</code></td></tr>
                        <tr><td><code>:</code></td></tr>
                        <tr><td><code>\\</code></td></tr>
                        <tr><td><code>t</code></td></tr>
                        <tr><td><code>e</code></td></tr>
                        <tr><td><code>x</code></td></tr>
                        <tr><td><code>t</code></td></tr>
                        <tr><td><code>.</code></td></tr>
                        <tr><td><code>t</code></td></tr>
                        <tr><td><code>x</code></td></tr>
                        <tr><td><code>t</code></td></tr>
                        <tr><td><code>\0</code></td></tr>
                        <tr><td><code>\0</code></td></tr>
                    </tbody>
                </table>
            </td>
        </tr>
    </tbody>
</table>