# Intensive Care Unit Project

## Description:
   This Projects is a Hospital Management System devided into multiple services and each servies contains a set of doctors and nurses that can control and monitor the patients of the hospital. The director of the hospital has access to any information on any service in contrary to the nurses and doctors which can only check the patients of their service. In critical cases patients can be moved to a `Critical Unit` where he will be treated differently

### Dependencies

- `nhlohmann/JSON` Library for JSON Manipulation
[github repo](https://github.com/nlohmann/json)


- `ncurse` Library for I/O manipulation
[github repo](https://github.com/mirror/ncurses) 

   **Installation:**
   

   ### **ncurses**:
   
   **Mac**:

   ```
   sudo port install ncurses
   ```

   **Linux**:
   
   Debian & Ubuntu 
   ```
   sudo apt-get install libncurses5-dev libncursesw5-dev
   ```
   Fedora, RHEL, CentOS, AlmaLinux, Rocky Linux
   ```
   sudo yum install ncurses-devel
   ```
   or
   ```
   sudo dnf install ncurses-devel
   ```
   
   Arch
   ```
   sudo pacman -S ncurses
   ```

   ### **nlohmann/json**:
   You need to copy the `include` file from json to the include path of the compiler.

   **Linux**:
   ```
   git clone https://github.com/nlohmann/json.git
   cd json/
   sudo cp -r include /usr/
   ```


   **Mac**:
   ```
   git clone https://github.com/nlohmann/json.git
   cd json/
   sudo cp -r include /usr/local
   ```

## Compilation:

Then execute one of the two commands

__To Run the program:__
```
g++ --std=c++14 src/*.cpp -o project -lncurses && ./project
```

__To Run the test:__
```
g++ --std=c++14 Test/*.cpp -o project -lncurses && ./project
```

--- 
## Notes:
- This Project only runs on UNIX systems because of the `ncurses` library which is only supported in UNIX.
- Compilation may take some seconds Because of The `nlohmann/json.hpp`.
___