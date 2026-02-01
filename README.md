# PMAN
### A project manager built to run on device with no sidecar files needed.
Pman is run from the command line and can create, delete, rename, or duplicate projects in the host's file system without needing to store any additional information. This means that the project files and folders are not reliant on this manager to be accessed or modified.

### **WARNING: This application is not made for public use. It is hardcoded for my personal file structure and will require a great deal of modification before general use.**

---
### TODO:

* git repository management
* github integration

---
### General Usage: pman [operation] [arg1] [arg2]

all three arguements are case-insensitive strings

---

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

---

### Deletion: pman delete [name]

Deletes the specified project and git repository.

#### [name]: specifies the name of the project to be deleted

---

### Copying: pman copy [src] [dst]

Copys the source project to a new directory and creates a new git repo.

#### [src]: specifies the name of the project to be copied

#### [dst]: specifies the name of the new project

---

### Renaming: pman rename [old] [new]

Renames the specified project and git repository to the new name.

#### [old]: specifies the name of the project to be renamed.

#### [new]: specifies the new name of the project.

---