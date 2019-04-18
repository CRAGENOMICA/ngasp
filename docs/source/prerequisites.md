Prerequisites
=============

Docker is available for Linux, MacOS, and Windows.

### Ubuntu

`docker.io` is available from the Ubuntu repositories (as of Xenial).

```bash
# Install Docker
sudo apt install docker.io
sudo apt install docker-compose

# Start it
sudo systemctl start docker
```

> Tip: If the `docker.io` package isn't available for you, see [Get Docker CE for Ubuntu](https://docs.docker.com/install/linux/docker-ce/ubuntu/) for an alternative.

### MacOS

Docker for Mac is best installed with [Homebrew](http://brew.sh) and [Homebrew Cask](http://caskroom.io/). For other ways to install on MacOS, see [Install Docker for Mac](https://docs.docker.com/docker-for-mac/install/) in Docker's docs.

```bash
brew cask install docker       # Install Docker
open /Applications/Docker.app  # Start Docker
```

> Tip: Avoid _Docker Toolbox_ and _boot2docker_. These are older packages that have been ceded by _Docker for Mac_.

### Arch Linux

Docker is available in Arch Linux's repositories. Also see [Docker in ArchWiki](https://wiki.archlinux.org/index.php/Docker).

```bash
sudo pacman -Syu docker        # Install Docker
sudo systemctl start docker    # Start Docker
```

### Windows

Install [Windows Subsystem for Linux][wsl] and choose _Ubuntu_ as your guest OS. Install Docker as you normally would on Ubuntu (see above). After that, [see these instructions](https://github.com/Microsoft/WSL/issues/2291#issuecomment-383698720) for info on how to get it running.

> Tip: Avoid _Docker for Windows_. While it works in most cases, you'll still face NTFS limitations without WSL (eg, lack of symlinks, which is needed for Yarn/npm to work).

[wsl]: https://docs.microsoft.com/en-us/windows/wsl/install-win10

### Other OS's

For other operating systems, see: <https://www.docker.com/community-edition#download>

## Verifying if it works

If everything works, you should have the following commands available:

```bash
$ docker info
Containers: 0
Running: 0
Paused: 0
...
```

```bash
$ docker-compose --version
docker-compose version 1.21.2, build unknown
```

## Starting Docker

If you get an error like the one below, you might need to start the Docker daemon.

```bash
$ docker info
Cannot connect to the Docker daemon at unix:///var/run/docker.sock. Is the docker daemon running?
```

To start the Docker daemon, it probably needs one of these commands

```bash
open /Applications/Docker.app  # macOS
sudo systemctl start docker    # Arch, Ubuntu, CentOS
```

## Enabling on startup

For Arch Linux, Ubuntu and CentOS, this will enable auto-starting of the Docker service:

```sh
sudo systemctl enable docker
```