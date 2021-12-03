```
// This program will take numbers, put them in a stack,
// try to sort them in ascending order using few operations
// using limited operations and the help of another stack.
// It output the operations it used to sort the numbers one at a line.
```

```
// 'stack' is always referring to the main stack
// the helping stack is always referred to as 'the helping stack'
```

```
TAKE input from command line as argument {
	CHECK IF they are valid integers
	CHECK IF there are duplicate integers
	CHECK THAT they are not sorted
	ELSE print "Error" and exit
}
```

```
SWITCH the N taken integers to - from 0 to N - 1 - according to their index
	// E.g. 88 17 118 -2 60 becomes 3 1 4 0 2
	// It's easier to deal with consecutive numbers starting from 0 than random numbers.
	// each number gets it's new value according to how many number is lesser than it in the stack
```

```
IF the number of integers in stack is 2
	switch them
ELSE IF it is 3
	the five hardcoded possibilities
ELSE IF it is 5 {
	PUSH the smallest element and the second smallest element to the helping stack
	SORT using the 3 algo
	PUSH back the elements pushed
	SWITCH the head if they are pushed back unsorted
}
ELSE { // push almost every element to the helping stack and push them back to be sorted
	WHILE lenght of stack is bigger than 5 {
		// keep pushing elements to the helping stack untill only 5 are left
		// keep 5 elements in the stack because there is an algo to do them.
		DEFINE 4 values (
			to_push, the number of element in stack minus 5 divided by 3 plus 1
			// divided by 3, small chunks are easier to deal with
			// plus 1, to avoid the infinite loop in case 6 or 7 elements are in the stack
			min, the smallest element to push at this round
			max, the biggest element to push which is min + (to_push - 1)
			// the added one to avoid infinite loop should be omitted here
			mid, (min + max) / 2
			// this one is used to divide elements when they get pushed to the helping stack
			// if the element pushed id smaller than the mid I rotate it to the end
			// this way I split the pushed elements into 2 chunks, thus, easier to handle
		)
		PUSH elements between min and max {
			before pushing a wanted element to the helping stack,
			find the quickest way to get it the top of the stack
			either rotating the top to the bottom
			or reverse rotation the bottom to the top

			push it to the helping stack and rotate it in case it is smaller than the mid
		}
	}
	SORT the five left elements
	FAKE the last element in the stack to -1
	// this step is needed to define the last element - it gets lost somehow
	// and it is needed for the next step to work properly
	WHILE lenght of the helping stack is bigger than 0 {
		IF the wanted element to push back is in the helping stack {
			// the wanted element to push back is the smallest element in the stack minus 1
			IF the top of the helping stack is ( smaller than the stack's
			AND bigger than the stack's tail ) {
				push it back to the stack
				IF the stack's top is not the wanted element
					reverse it down
			}
			ELSE
				push the wanted element to the top of the helping stack using the closest path
				either by rotating or reverse rotating.
		}
		ELSE it is at the end of the stack
			reverse rotate element in stack
	}
	UNFAKE the last element
	WHILE the stack isn't sorted yet, reverse rotate
}
```