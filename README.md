# WS - the Arbitrary Precision workspace

This workspace is used for all activities:
- Development.
- Manual testing.
- Automated testing.
- Coverage measurement.
- Performance measurement.

## Development

Clone the repo and checkout the AP via SSH:
```
git clone --recurse-submodules git@github.com:arbitrary-precision/ws.git
cd ws/src/ap
git remote set-url origin git@github.com:arbitrary-precision/ap.git
git fetch origin -a
git checkout -B main
```
