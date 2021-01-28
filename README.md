# arx
<h2>Arithmetic expansion</h2></br>
The first version of a shell arithmetic expansion feature. It was integrated with a bash-like <a href=https://github.com/ihwang/42sh>shell</a></br> which forms part of my studies at Hive Helsinki.
</br>
The following operators are handled (in order or precedence):</br>

* Brackets ()
* Postfix incrementality, decrementality ++ --
* Prefix incrementality, decrementality ++ --
* Unary + - (not explicitly asked for in subject)
* Multiplication, division, modulo * / %
* Addition, subtraction + -
* Comparison <= >= < >
* Equality, non-equality == !=
* AND/OR && ||
</br>
The following operands are handled:</br>

* integer
* octal
* hexadecimal
* base 2 - 64 (base#value)
* internal variables
</br>
<h2>Usage</h2>
Repository contains a Makefile for:

* compiling executable (make all)
* removing object files (make clean)
* deleting executable (make fclean)
* recompiling (make re)
</br>
Run executable: ./arx</br>
Quit program: q <ENTER></br>
</br>
Note:</br>
This program does not handle nested expansions, and was something that was added after this was integrated with the shell it was intende for.
