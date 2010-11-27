CV:run([[
// console language standard library

// executes the body supplied
// i.e. do [@stuff]
do = [ arg1 ]

// concats all the results of each iteration
// i.e. loopconcat i 5 [result $i]
// results in "0 1 2 3 4"
loopconcat = [
    sum = "";
    loop $arg1 $arg2 [sum = (concat $sum (arg3))]
    result $sum;
]

// creates a macro whose body is a format string
// i.e. macro greet [ say Hi, %1! ]
macro = [
    $arg1 = (concat [format [@@arg2] ] (loopconcat i $numargs [concatword " $arg" (+ $i 1)]))
]

// binds a key so that it will toggle a variable
// i.e. bindvar 9 thirdperson
bindvar = [
  bind $arg1 [@arg2 (= $@arg2 0); if (= $@arg2 0) [echo @@arg2 OFF] [ echo @@arg2 ON] ]
]

// same as above, but only binds for edit mode
editbindvar = [
  editbind $arg1 [@arg2 (= $@arg2 0); if (= $@arg2 0) [echo @@arg2 OFF] [ echo @@arg2 ON] ]
]

// binds a key so that it will set a modifier while held down
bindmod = [
  bind $arg1 [@arg2 1; onrelease [@@arg2 0] ]
]

// same as above, but only binds for edit mode
editbindmod = [
  editbind $arg1 [@arg2 1; onrelease [@@arg2 0] ]
]

quine = [ echo (format "quine = [%1]" $quine) ]

loadsky = [
    skybox $arg1
    if (> $numargs 1) [
        spinsky $arg2
    ] [
        if (!=f $spinsky 0) [spinsky 0]
    ]
]

mapmsg = [ maptitle $arg1 ]

sayteamcommand = [ echo "Team chat not yet implemented" ]
togglezoom = [ zoom (if (= $zoom 1) -1 1) ]
]])