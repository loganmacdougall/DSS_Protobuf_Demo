# DSS Protobuf Demo
This is a demonstration on how protobuf can be used at DSS. This includes setting up the CMake and code for sending and recving protobuf objects in C++

## Setup
You will need to clone this repository:
  
`$  git clone https://github.com/loganmacdougall/DSS_Protobuf_Demo.git`

You will need to enter the Nix Shell from the [MANTIS-DevEnv repo](https://github.com/DalhousieSpaceSystemsLab/MANTIS-DevEnv). This will allow you to compile the demo.

You then go into the demo repository and type the following commands to setup the build folder:

```
$  mkdir build && cd build
$  cmake ..
```

Now you can generate the files in the `build` folder with the following command:

`$  make`

This will generate 2 executables in your build folder, `sender`, and `receiver`. You should run these in 2 seprate shell for this to work, making sure to **run the receiver first** or else it will not work.
