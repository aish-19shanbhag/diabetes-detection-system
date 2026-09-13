# Diabetes Detection System

A rule-based expert system that diagnoses the likely type of diabetes based on a series of escalating symptom questions, implemented in C++.

## Overview

The program asks up to three levels of symptom questions (general symptoms, secondary conditions, and detailed history), and uses a rule-based decision process at each level to determine whether to classify the person as diabetic, and if so, what type (primary/secondary, insulin-dependent/non-insulin-dependent).

## Background

Originally built during my Bachelor's degree, with help from a classmate on parts of the original logic. This version has been modernized from the original Turbo C++ (DOS) implementation to standard, portable C++ that compiles with any current compiler, along with fixes to a few logic bugs found in the original (an uninitialized pointer, a stray semicolon that silently broke a switch statement, and swapped function arguments in two call sites).

## Tech Stack

- C++ (standard library only — no external dependencies)

## Running the Project

```bash
g++ -std=c++17 diabetes_detection.cpp -o diabetes_detection
./diabetes_detection
```

## Author

Aishwarya Ramanath Shanbhag
