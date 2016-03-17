## CSCI 2312: Programming Assignment 4   \<\<IN PROGRESS\>\>

_inheritance, polymorphism, board games, randomization_

* * *

### Goals

1. Get experience with inheritance, polymorphism, and class hierarchies in the domain of board turn-based strategic games.
2. Enrich your pallette of C++ tools to define complex behavior:
  1. Abstract and concrete classes for hierarchical behavior extension.
  2. `virtual` functions and overriding to specialize behavior while supporting polymorphism.
  3. _functors_ to specify dynamic object behavior.
  4. The `<random>` library to randomize object behavior.
  5. A `virtual` binary operator to implement object interaction.
  6. STL classes for data management.
3. Develop in _one go_ a small-scale semi-interactive game with bare-bones ASCII visualization.
4. Continue using git and Github.
5. Develop good coding style.

### Synopsis

PA4 leaves the clustering domain and gives a glimpse of the game domain. While it is a chance to put any C++ features we have covered to new use, its main goal is to give a fertile setting for dynamic (run-time) polymorphism of user types. You will create a class hierarchy with a rich tapestry of polymorphic behavior. You have to write quite a few more files than usual, though most are small: `Exceptions.cpp`, `Piece.cpp`, `Agent.cpp`, `Simple.cpp`, `Strategic.cpp`, `Resource.cpp`, `Food.cpp`, `Advantage.cpp`, `Game.cpp`, `DefaultAgentStrategy.cpp`, and `AggressiveAgentStrategy.cpp`. See the [Detailed Instructions](https://github.com/ivogeorg/ucd-csci2312-pa4/blob/master/README.md#detailed-instructions) at the bottom of this file.

PA4 is in the test-driven-development (TDD) style, just like the preceding assignments. It has 153 tests that your implementation should pass for full points. Because the different elements of the `Game` are quite intertwined, it is recommended that you follow roughly this order of implementation and testing:

1. `Game` smoke test.
2. `Game` printing.
3. `Piece` smoke test.
4. `Piece` printing.
5. `Game` population.
6. `Surroundings` smoke test.
7. _Action_ smoke test.
8. Other `Piece` tests.
9. _Randomization_ test.
9. `Game` play.

This assignment may be smaller in terms of the total lines of code relative to the preceding ones but is not trivial. It might take just as much time as the others since it introduces new language features and has several points of algorithmic complexity.

### Submission

You don't need to submit anything. Once you fork the repository (this is your **remote** repository on Github, aka **origin**), you will clone it to your development machine (this is your local repository), and start work on it. Commit your changes to your local repository often and push them up to the remote repository occasionally. Make sure you push at least once before the due date. At the due date, your remote repository will be cloned and tested automatically by the grading script. _**Note:** Your code should be in the **master** branch of your remote repository._

### Grading

An autograding script will run the test suite against your files. Your grade will be based on the number of tests passed. (E.g. if your code passes 3 out of 6 test cases, your score will be 50% and the grade will be the corresponding letter grade in the course's grading scale). The test suite for PA4 has __153__ tests. **Note:** The testing and grading will be done with fresh original copies of all the provided files. In the course of development, you can modify them, if you need to, but your changes will not be used. Only your <tt>Point.cpp</tt>, <tt>Cluster.cpp</tt>, <tt>KMeans.cpp</tt>, and <tt>Exceptions.cpp</tt> files will be used.

### Compiler

Your program should run on **GCC 4.9.0** or later, or **Clang 3.3** or later. No other compilers are supported.

### Due Date

The assignment is due on **Sun, Apr 17, at 23:59 Mountain time**. No late work. The last commit to your PA4 repository before the deadline will be graded.

### Honor Code

Free Github repositories are public so you can look at each other's code. Please, don't do that. You can discuss any programming topics and the assignments in general but sharing of solutions diminishes the individual learning experience of many people. Assignments might be randomly checked for plagiarism and a plagiarism claim may be raised against you.

### Use of libraries

You are encouraged to make maximum use of the Standard Library especially including the Standard Template Library (STL).

### Coding style

Familiarize yourself with and start following [coding style guidelines](http://courses.cms.caltech.edu/cs11/material/cpp/donnie/cppstyle.html). There are others on the Web. Pick one and be consistent. _**Note:** If you stumble on the Google C++ Style Guide, be advised that it has been heavily criticized by many leading C++ programmers. I don't advise you to follow it, especially the more advanced features. This Guide is for entry-level coders at Google who need to be able to work with their legacy code. It is not advisable for new projects and novice programmers._

### References

Operator overloading [guidelines](http://courses.cms.caltech.edu/cs11/material/cpp/donnie/cpp-ops.html).

A very good [C++ tutorial](http://www.learncpp.com/), including many topics we are covering.

Two websites with C++ Reference, [here](http://en.cppreference.com/w/) and [here](http://www.cplusplus.com/).

### Detailed Instructions

![alt text](https://github.com/ivogeorg/ucd-csci2312-pa4/blob/master/images/piece_hier.png "Piece class hierarchy")

