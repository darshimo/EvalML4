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

### Syntax

$$
\begin{align*}
i & \in {\rm integer}\\
b & \in {\rm bool}\\
x,y & \in {\rm Var}\\
op & \in {\rm Prim} ::= + ~|~ - ~|~ * ~|~ <\\
v & \in {\rm Value} ::= i ~|~ b ~|~ (\mathcal{E})[{\rm fun} ~ x \to e] ~|~ (\mathcal{E})[{{\rm rec} ~ x = ~ {\rm fun} ~ y \to e}] ~|~ [] ~|~ v::v\\
\mathcal{E} & \in {\rm Env} ::= \bullet ~|~ \mathcal{E}, x=v\\
e & \in {\rm Exp} ::= i ~|~ b ~|~ x ~|~ e ~ op ~ e ~|~ {\rm if} ~ e ~ {\rm then} ~ e ~ {\rm else} ~ e ~|~ {\rm let} ~ x = e ~ {\rm in} ~ e ~|~ {\rm fun} ~ x \to e ~|~ e ~ e \\ & \qquad\qquad |~ {\rm let ~ rec} ~ x = {\rm fun} ~ y \to e ~ {\rm in} ~ e ~|~ [] ~|~ e::e ~|~ {\rm match} ~ e ~ {\rm with} ~ [] \to e ~|~ x::y \to e\\
\end{align*}
$$

### Inference Rules

[](<img src="https://github.com/darshimo/EvalML4/blob/images/rulebook_21.jpeg" width=50%><img src="https://github.com/darshimo/EvalML4/blob/images/rulebook_22.jpeg" width = 50%>)

$$\frac{\mathcal{E}\vdash e_1 \Downarrow i_1 \quad \mathcal{E}\vdash e_2 \Downarrow i_2 \quad i_1 ~ {\rm plus} ~ i_2 ~ {\rm is} ~ i_3}{\mathcal{E}\vdash e_1 ~+~ e_2 \Downarrow i_3}
\qquad
\frac{\mathcal{E}\vdash e_1 \Downarrow i_1 \quad \mathcal{E}\vdash e_2 \Downarrow i_2 \quad i_1 ~ {\rm minus} ~ i_2 ~ {\rm is} ~ i_3}{\mathcal{E}\vdash e_1 ~-~ e_2 \Downarrow i_3}$$
<br>

$$\frac{\mathcal{E}\vdash e_1 \Downarrow i_1 \quad \mathcal{E}\vdash e_2 \Downarrow i_2 \quad i_1 ~ {\rm times} ~ i_2 ~ {\rm is} ~ i_3}{\mathcal{E}\vdash e_1 ~*~ e_2 \Downarrow i_3}
\qquad
\frac{\mathcal{E}\vdash e_1 \Downarrow i_1 \quad \mathcal{E}\vdash e_2 \Downarrow i_2 \quad i_1 ~ {\rm less ~  than} ~ i_2 ~ {\rm is} ~ i_3}{\mathcal{E}\vdash e_1 ~<~ e_2 \Downarrow b_3}$$
<br>

$$\frac{\mathcal{E}\vdash e_1 \Downarrow {\rm true} \quad \mathcal{E}\vdash e_2 \Downarrow v}{\mathcal{E}\vdash {\rm if} ~ e_1 ~ {\rm then} ~ e_2 ~ {\rm else} ~ e_3 \Downarrow v}
\qquad
\frac{\mathcal{E}\vdash e_1 \Downarrow {\rm false} \quad \mathcal{E}\vdash e_3 \Downarrow v}{\mathcal{E}\vdash {\rm if} ~ e_1 ~ {\rm then} ~ e_2 ~ {\rm else} ~ e_3 \Downarrow v}$$
<br>

$$\frac{\mathcal{E}\vdash e_1 \Downarrow v_1 \quad \mathcal{E},x=v_1\vdash e_2 \Downarrow v}{\mathcal{E}\vdash {\rm let} ~ x = e_1 ~ {\rm in} ~ e_2 \Downarrow v}
\qquad
\frac{}{\mathcal{E}\vdash {\rm fun} ~ x \to e \Downarrow (\mathcal{E})[{\rm fun} ~ x \to e]}$$
<br>

$$\frac{\mathcal{E}\vdash e_1\Downarrow(\mathcal{E}_2)[{\rm fun} ~ x\to e_0] \quad \mathcal{E}\vdash e_2\Downarrow v_2 \quad \mathcal{E}_2,x=v_2\vdash e_0\Downarrow v}{\mathcal{E}\vdash e_1 ~ e_2\Downarrow v}
\qquad
\frac{\mathcal{E},x=(\mathcal{E})[{\rm rec} ~ x={\rm fun} ~ y \to e_1]\vdash e_2\Downarrow v}{\mathcal{E}\vdash {\rm let ~ rec} ~ x = {\rm fun} ~ y \to e_1 ~ {\rm in} ~ e_2\Downarrow v}$$
<br>

$$\frac{\mathcal{E}\vdash e_1\Downarrow(\mathcal{E}_2)[{\rm rec} ~ x={\rm fun} ~ y \to e_0] \quad \mathcal{E} \vdash e_2 \Downarrow v_2 \quad \mathcal{E}_2,x=(\mathcal{E}_2)[{\rm rec} ~ x = {\rm fun} ~ y \to e_0],y=v_2\vdash e_0\Downarrow v}{\mathcal{E}\vdash e_1 ~ e_2\Downarrow v}$$
<br>

$$\qquad\frac{}{\mathcal{E}\vdash[]\Downarrow[]}
\qquad\qquad\qquad\qquad\qquad\quad
\frac{\mathcal{E}\vdash e_1\Downarrow v_1 \quad \mathcal{E}\vdash e_2\Downarrow v_2}{\mathcal{E}\vdash e1::e_2\Downarrow v_1::v_2}$$
<br>

$$\frac{\mathcal{E}\vdash e_1\Downarrow[] \quad \mathcal{E}\vdash e_2\Downarrow v}{\mathcal{E}\vdash{\rm match} ~ e_1 ~ {\rm with} ~ [] \to e_2 | x::y \to e_3 \Downarrow v}
\qquad
\frac{\mathcal{E}\vdash e_1\Downarrow v_1::v_2 \quad \mathcal{E},x=v_1,y=v_2\vdash e_3\Downarrow v}{\mathcal{E}\vdash{\rm match} ~ e_1 ~ {\rm with} ~ [] \to e_2 | x::y \to e_3 \Downarrow v}$$
<br>

$$\frac{(i_3 = i_1 + i_2)}{i_1 ~ {\rm plus} ~ i_2 ~ {\rm is} ~ i_3}
\qquad
\frac{(i_3 = i_1 - i_2)}{i_1 ~ {\rm minus} ~ i_2 ~ {\rm is} ~ i_3}
\qquad
\frac{(i_3 = i_1 * i_2)}{i_1 ~ {\rm times} ~ i_2 ~ {\rm is} ~ i_3}
\qquad
\frac{(b_3 = i_1 < i_2)}{i_1 ~ {\rm less~than} ~ i_2 ~ {\rm is} ~ b_3}$$

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
