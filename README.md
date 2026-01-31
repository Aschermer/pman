# PMAN
### A project manager built to run on device with no sidecar files needed.
Pman is run from the command line and can create, delete, rename, or duplicate projects in the host's file system without needing to store any additional information. This means that the project files and folders are not reliant on this manager to be accessed or modified.

### **WARNING: This application is not made for public use. It is hardcoded for my personal file structure and will require a great deal of modification before general use.**

---
### General Usage: pman operation [argument1] [argument2]

### Creation: pman create [name] [template]

Creates a project and initializes it with the template specified.

#### [name]: specifies the name of the project directory and the git repository

#### [template]: specifies the structure of the created project

empty:
```
dir/
```
c:
```
dir/
├── src/
│   └── main.c
├── obj/
├── bin/
├── build
└── README.md
```