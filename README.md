# CS-3353-Spring-2024---Forming-a-Space-Exploration-Team-Dynamic-Programming-
Dynamic programming solution for selecting a space exploration team under budget constraints, with support for up to two applicants per position.
This repository contains an implementation of a dynamic programming solution for selecting the optimal space exploration team under budget constraints. As the captain of a starship, the challenge is to choose applicants for various positions while maximizing the team's overall benefit within a set budget.

Features
Dynamic Programming Solution: Implements an efficient solution based on the 0-1 knapsack problem to select team members while considering their cost and benefit.
Flexible Team Composition: You can fill up to one applicant per position or leave a position vacant to be filled by an AI, which has zero cost and benefit.
Budget-Constrained Selection: Ensures the total cost of selected applicants does not exceed the given budget, while maximizing the team's total benefit.
Extra Credit
Extended Functionality (pickTeam_2): Allows the option to select up to two applicants per position, providing greater flexibility in team composition while adhering to the budget.
Getting Started
The implementation of the dynamic programming function is in prog4.cpp.
The main program can be found in prog4main.cpp, which handles input/output.
The header file prog4.h defines the Applicant structure.
