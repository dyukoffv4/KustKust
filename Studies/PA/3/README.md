# Open MP
## Compile

To compile version with interprogramm CLI run:

`make cmain`

To compile version with flags CLI run:

`make fmain`

## Run

### For interprogramm CLI run:

`bin/cmain`

### For flags CLI run:

Required parametrs, only one can be entered:
* -S - to test serial function;
* -P - to test parallel function;
* -I - to test improved function.

Optional parametrs:
* -r - set number of repeating function;
* -d - set start, stop and step of changing size for test data.
* -c - set number of process.

`bin/fmain -S -d 2 16 -r 50   // Run serial on number of vars - [2, 4, 8, 16], for 50 times each one.`

`bin/fmain -P -c 8            // Run parallel on number of vars - [10, 20, 40, 80, 160], for 10 times each one, on 8 processes.`

## Clean

`make clear`
