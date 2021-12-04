# Push_swap

```
- Because Swap_push isn’t as natural
```
```
Subject
	https://github.com/taoufiqjmari/1337-Common-Core/blob/main/Push_swap/en.subject.pdf
```
```
Summary
- This project will make you sort data on a stack, with a limited set of instructions, usingthe lowest possible number of actions. To succeed you’ll have to manipulate varioustypes of algorithms and choose the one (of many) most appropriate solution for anoptimized data sorting.
```
```
Learning outcomes
- C:
	- Use of C
	- Rigor
	- Basic algorithms
	- Sorting algorithms
	- Complexity
```
```
Project prerequisites
- The gcc command (GNU Compiler Collection)
- The make command (Makefile)
- Git [optional]
- Python3 [optional]
```
```
How to use:
1 - Download parent folder of the project or clone it using git
	$> git clone https://github.com/taoufiqjmari/1337-Common-Core.git

2 - On Terminal, go to project directory
	$> cd Push_swap

3 - Make the executable
	$> make
	$> make bonus  // For ./checker

4 - Run
	$> ./push_swap [RANDOM NUMBER OF YOUR CHOICE]
	$> ./push_swap 1 5 2 4 3
	_________________________________
	_________________________________
	// Useful for large input then passing the output of push_swap to a checker to check are the operations valid
	
	$> ARG=$(python3 ./args_generator.py); ./push_swap $ARG | ./checker $ARG
	$> Program asks How many random numbers you want to sort
	_________________________________
	_________________________________
	// Print the generated elements by python and how many operation was produced.

	$> ARG=$(python3 ./args_generator.py); echo $ARG; ./push_swap $ARG | wc -l;
	$> Program asks How many random numbers you want to sort
	_________________________________
	_________________________________
	// A live visualiser of what the algo produced

	ARG=$(python3 ./args_generator.py); python3 pyviz.py $ARG
	$> Program asks How many random numbers you want to sort
```
```
The algorithm is explained as pseudocode
	https://github.com/taoufiqjmari/1337-Common-Core/blob/main/Push_swap/pseudocode.md
```
```
The project follows the school norm:
	https://github.com/taoufiqjmari/1337-Common-Core/blob/main/Norm/C_Norm_V3/en.norm.pdf
```

## Resources

* [Good Starting Point (Medium article)](https://medium.com/@jamierobertdawson/push-swap-the-least-amount-of-moves-with-two-stacks-d1e76a71789a)
* [The visualizer](https://github.com/o-reo/push_swap_visualizer)