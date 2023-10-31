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

__From parametrs below can be entered only one and only once:__
* -P - to test parallel function, set number of processes (optionaly, default - 4);
* -I - to test improved function, set number of processes (optionaly, default - 4).

_By default tests serial function._

__Other parametrs:__
* -r - set number of tests for function at one size of test data;
* -d - set start, stop and step for size for test data.

`bin/fmain -d 2 16 -r 50   // Run serial on number of vars - [2, 4, 8, 16], for 50 times each one.`

`bin/fmain -P 8            // Run parallel on number of vars - [10, 20, 40, 80, 160], for 10 times each one, on 8 processes.`

## Clean

`make clear`
