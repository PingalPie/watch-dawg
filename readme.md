# Watch dawg

This program is used for watching over changes in system files,
It is also one of my first programs ever in `c` language so. it does have a few issues

# Installation
So far this program is only for *nix like (unix, linux, bsd, macOS, etc) although I've not tested it on other than `linux`

```bash
make
```
# Usage
You can get a binary file named watch_dawg, which is the main binary.
```
Usage: ./watch_dawg PATH_TO_FILE_TO_WATCH
```
# Dependencies
- inotify
- gcc

# Current known issues
- [ ] Unable to check if state of file is restored after being edited
- [ ] Does not give output for intended state (i.e. FILE_OPEN)
