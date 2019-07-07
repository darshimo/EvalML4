# EvalML4

![](https://github.com/darshimo/EvalML4/blob/images/demo.gif)

## Overview

An interpreter for subset of OCaml.

It evaluates an expression in call-by-value and outputs the derivation tree.

## Installation

```sh
$ cd EvalML4
$ make
```

## Usage

- Execute evalML4 without arguments and type expression.
	
	```sh
	$ ./evalML4
	input expression within 500 characters (end with ;)
	> [expression];
	```

- Give file path as command line argument.

	```sh
	$ ./evalML4 problem/70
	```
	
	Runing `make test`, you can get the answers for sample problems.

## Derivation System

[](<img src="https://github.com/darshimo/EvalML4/blob/images/rule_1.jpeg" width=50%><img src="https://github.com/darshimo/EvalML4/blob/images/rule_2.jpeg" width = 50%>)


## Example

```
$ ./evalML4
input expression within 500 characters (end with ;)
> let a = 3 in let f = fun x -> x * a in f 2;

|- let a = 3 in let f = fun x -> x * a in f 2 evalto 6 by E-Let {
  |- 3 evalto 3 by E-Int {};
  a = 3 |- let f = fun x -> x * a in f 2 evalto 6 by E-Let {
    a = 3 |- fun x -> x * a evalto (a = 3)[fun x -> x * a] by E-Fun {};
    a = 3, f = (a = 3)[fun x -> x * a] |- f 2 evalto 6 by E-App {
      a = 3, f = (a = 3)[fun x -> x * a] |- f evalto (a = 3)[fun x -> x * a] by E-Var {};
      a = 3, f = (a = 3)[fun x -> x * a] |- 2 evalto 2 by E-Int {};
      a = 3, x = 2 |- x * a evalto 6 by E-Times {
        a = 3, x = 2 |- x evalto 2 by E-Var {};
        a = 3, x = 2 |- a evalto 3 by E-Var {};
        2 times 3 is 6 by B-Times {}
      }
    }
  }
}
```

## Requirement

gcc 8.3.0
