# ATM

This project is a C++ library that simulates the core operations of an ATM controller by communicating with a bank server through a bank API. <br>
It does not include integration with actual banking systems or ATM hardware. However, the code is structured to allow such integration in the future. <br>
The library is intended to be used as a module in other applications, and it also includes test cases to demonstrate its functionality. <br>
It provides features such as card insertion, PIN authentication, account selection, balance inquiry, deposits, and withdrawals. <br>

## Table of Contents
- [ATM](#atm)
  - [Table of Contents](#table-of-contents)
  - [Key Features](#key-features)
  - [Build and Run](#build-and-run)
    - [Requirements](#requirements)
    - [Build](#build)
    - [Run Tests](#run-tests)
  - [Documentation](#documentation)

## Key Features
- **Card Insertion and Removal**: Insert or remove a card from the ATM.
- **PIN Authentication**: Authenticate the card's PIN through the bank API.
- **Account Selection**: Retrieve a list of available accounts and select a specific account.
- **Balance Inquiry**: Check the balance of the selected account.
- **Deposit and Withdrawal**: Deposit or withdraw funds from the account.

## Build and Run

### Requirements
- CMake 3.11 or higher
- C++17 compatible compiler

### Build
1. Clone the project:
   ```bash
   git clone https://github.com/shkwon98/atm.git
   cd atm
   ```
2. Create a build directory and configure the project:
   ```bash
   mkdir build && cd build
   cmake .. -DBUILD_SHARED_LIBS=ON  # Use ON for shared libraries, OFF for static libraries
   cmake --build .
   ```

### Run Tests
After building, run the tests using the following command:
```bash
ctest
```

## Documentation
The documentation is automatically generated and deployed via GitHub Actions.  
You can access the live documentation [here](https://shkwon98.github.io/atm/).
