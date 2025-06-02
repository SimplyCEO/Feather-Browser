<img src="./assets/icon_git.png" width="32" title="Feather Browser"> Feather Browser
====================================================================================

A quick example of a browser, made in pure C using GTK3 and WebKit2GTK+.

Usage
-----

To install it is really simple. Clone, enter, make, run, rage.
```shell
git clone https://gitlab.com/SimplyCEO/Feather-Browser.git
cd Feather-Browser
make BUILD_TYPE=Release
bin/feather_browser
```
Or just open `feather_browser` located inside `bin` folder.

Installation
------------

Copy the contents of the `assets` folder to the local browser folder:
```shell
mkdir -p "${HOME}/.local/share/feather_browser"
cp -r ./assets "${HOME}/.local/share/feather_browser"
```

<details><summary>Local installation</summary>

To install only for the local user, the `PATH` environment variable need to be set to the specific path
which will be assumed it is under the `HOME` directory.

Exporting the `PATH` environment variable is easy, just need a few steps:
```shell
export PATH="${HOME}/.local/bin:${PATH}"
cp bin/feather_browser "${HOME}/.local/bin"
```

Additionaly, the desktop file for Linux devices can be accessed through the menu and/or desktop:
```shell
cp assets/icon.png "${HOME}/.icons/feather_browser_icon.png"
cp Feather_Browser.desktop "${HOME}/.local/share/applications"
cp Feather_Browser.desktop "${HOME}/Desktop"
```

Remember to add the binary path to the desktop file:
```desktop
Path=/home/username/.local/bin
Exec=./feather_browser
```

</details>

<details><summary>System-wide installation</summary>

To install system-wide, the `/usr/local/bin` directory can be used:
```shell
cp bin/feather_browser "/usr/.local/bin"
```

Additionaly, the desktop file for Linux devices can be accessed through the menu and/or desktop:
```shell
cp assets/icon.png "/usr/share/icons/feather_browser_icon.png"
cp Feather_Browser.desktop "/usr/share/applications"
```

</details>

Gallery
-------

<p align="left">
  <a href="/.media/screenshots/feather_browser_0.png">
    <img src="/.media/screenshots/lowres_feather_browser_0.png" width="192" title="Feather Browser Technologic">
  </a>
</p>

