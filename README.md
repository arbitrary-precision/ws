# WS - the Arbitrary Precision workspace

This workspace is used for all activities:
- Development.
- Manual testing.
- Automated testing.
- Coverage measurement.
- Performance measurement.

All the development is supposed to be done on a Linux-based OS.
Docker is used for building and testing the changes.

## Prerequisites

All actions are tested on Ubuntu 22.04.
The required tools are:
- Git (trivial).
- GNU Make (typically installed).
- Docker.

### Docker

Install:
```sh
sudo apt-get install -y docker docker.io
```

Confirm that Docker works correctly:
```sh
docker run hello-world
```

Troubleshooting `Got permission denied while trying to connect to the Docker daemon`:
```sh
# Add user to the group 'docker'.
sudo usermod -a -G docker $USER
# Enforce proper permissions.
sudo chmod 664 /var/run/docker.sock
# Then reboot the PC.
```

## Development

Clone the repo and checkout the AP via SSH:
```
git clone --recurse-submodules git@github.com:arbitrary-precision/ws.git
cd ws/src/ap
git remote set-url origin git@github.com:arbitrary-precision/ap.git
git fetch origin -a
git checkout -B main
```
