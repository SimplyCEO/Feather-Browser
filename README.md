<img src="./assets/icon_git.png" width="32" title="Feather Browser"> Feather Browser
====================================================================================

A quick example of a browser, made in pure ANSI C using GTK3 and WebKit2GTK+.

Usage
-----

To install it is really simple. Clone, enter, make, run, rage.
```shell
git clone https://gitlab.com/SimplyCEO/Feather-Browser.git
cd Feather-Browser
make BUILD_TYPE=Release
bin/feather-browser
```
Or just open `feather-browser` located inside `bin` folder.

Installation
------------

Run the following installation command as root:
```shell
make install
```

<details><summary>Local installation</summary>

To install only for the local user, the `PATH` environment variable need to be set to the specific path
which will be assumed it is under the `HOME` directory.

Exporting the `PATH` environment variable is easy, just need a few steps:
```shell
export PATH="${HOME}/.local/bin:${PATH}"
cp bin/feather-browser "${HOME}/.local/bin"
```

Copy the contents of the `assets` folder to the local browser folder:
```shell
mkdir -p "${HOME}/.local/share/feather-browser"
cp -r ./assets "${HOME}/.local/share/feather-browser"
```

Additionaly, the desktop file for Linux devices can be accessed through the menu and/or desktop:
```shell
cp assets/icon.png "${HOME}/.icons/feather-browser_icon.png"
cp feather-browser.desktop "${HOME}/.local/share/applications"
cp feather-browser.desktop "${HOME}/Desktop"
```

Remember to add the binary path to the desktop file:
```desktop
Path=/home/username/.local/bin
Exec=./feather-browser
Icon=./assets/icon.png
```

</details>

Gallery
-------

<p align="left">
  <a href="/.media/screenshots/feather-browser_0.png">
    <img src="/.media/screenshots/lowres_feather-browser_0.png" width="192" title="Feather Browser Technologic">
  </a>
  <a href="/.media/screenshots/feather-browser_1.png">
    <img src="/.media/screenshots/lowres_feather-browser_1.png" width="192" title="Feather Browser Repository">
  </a>
</p>

