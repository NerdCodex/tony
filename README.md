# Tony ![Conventional Commits](https://img.shields.io/badge/g++%20-11.4.0-blue.svg) ![Conventional Commits](https://img.shields.io/badge/Tony%20-0.0.5-red.svg) 

Tony is a simple interpreted language written in C++. This language currently supports only one control structure and dynamic typed variables, where the datatype of the variable changes as per its value. Here are some additional points:
<b>(This Programming Language Is Under Development Stage)</b>

# The Language
  ### Program
  The program begins with `BEGIN` and ends with `END`.
  
  <b> Example </b>
  ```tony
  BEGIN
      print("Hello World");
  END
  ```
  ## Variables
  Variables are declared and initialized in the same line: `variable_name := value;`.
  
  <b> Example </b>
  ```
  name := "Rakesh";
  age := 18;
  ```
  ## Builtin Functions
  The language comes with some builtin functions like `print(), scanInt(), scanStr(), and str()`.
  | Builtin Function | Use            | Usage                                   |
|------------------|----------------|-----------------------------------------|
| print()          | Output         | `print("Hello, world!")`                |
| scanInt()        | Input          | `int_var := scanInt("Enter a number: ")`                  |
| scanStr()        | Input          | `str_var := scanStr("Enter a String: ")`                  |
| str()            | String Convert | `string_var := str(42)`                 |

  ## Control Structure
  The language currently supports only the `if() { } else { };` structure.
  
  <b> Example </b>
  ```
  age := 18;
  if (age > 18) {
      print("Age is greater than 18");
  } else {
      print("Age is less than or equal to 18.");
  };
  ```

  ## Comment
  Comments start with $.

  <b> Example </b>
  ```
  $ This is a comment.
  ```

# Example Program
```
$ main.tony
BEGIN
    print("Voting Eligibility Checker");
    name := scanStr("Enter your name: ");
    age := scanInt("Enter your age: ");

    $ printing the voter's details
    print("Voter Name: " + name);
    print("Voter Age: " + str(age));

    $ Checking whether he/she is eligible for voting or not.
    if (age >= 18) {
        print("You are eligible for voting");
    } else {
        print("Your age is less than 18.");
        print("So, You are not eligible for voting.");
    };
END
```
# Usage
    git clone https://github.com/NerdCodex/tony.git
    cd tony
    make
    ./tony programs/voting.tony
