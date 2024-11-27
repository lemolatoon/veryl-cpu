# Setup

```bash
$ cargo install verylup
$ sudo apt install verilator gtkwave
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