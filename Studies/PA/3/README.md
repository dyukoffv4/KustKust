# Open MP
## Compile

To compile version with interprogramm CLI run:

`make MAIN=main.cpp`

To compile version with flags CLI run:

`make MAIN=fmain.cpp`

## Run

### For interprogramm CLI run:

`bin/main`

### For flags CLI run:

Required parametrs, only one can be entered:
* -S - to test serial function;
* -P - to test parallel function;
* -I - to test improved function.

Optional parametrs:
* -r - set number of repeating function;
* -d - set start, stop and step of changing size for test data.

`bin/main -S -d 2 16 2 -r 50`

`bin/main -P`

## Clean

`make clear`
