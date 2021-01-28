# arx
<h2>Arithmetic expansion</h2></br>
The first version of a shell arithmetic expansion feature, which was integrated with a bash-like <a href=https://github.com/ihwang/42sh>shell</a></br>
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
