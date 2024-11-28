# Setup

```bash
$ cargo install verylup
# apt (ubuntu etc)
$ sudo apt install verilator gtkwave
# brew (macos etc)
$ brew install verilator
$ brew install --HEAD randomplum/gtkwave/gtkwave
$ verylup setup
$ verylup install 0.13.3
```

# build and simulate

```bash
# run `veryl build`
$ ./bin build
# run simulation using verilator
$ ./bin sim sample.hex 6
# clean generated files
$ ./bin clean
```