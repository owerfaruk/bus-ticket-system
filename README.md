# Bus Ticket Management System

![Build](https://img.shields.io/badge/build-passing-brightgreen)
![Language](https://img.shields.io/badge/language-C-blue)
![License](https://img.shields.io/badge/license-Educational-lightgrey)
![Platform](https://img.shields.io/badge/platform-CLI-orange)

A simple console-based **Bus Ticket Management System** written in C. This project allows users to manage bus trips, sell tickets, and view trip information through a menu-driven interface.

---

## 📌 Features

* Add new bus trips
* List all available trips
* Search trips by destination and date
* Sell tickets to passengers
* View sold tickets
* Data persistence using text files

---

## 🛠️ Technologies Used

* **Language:** C
* **Compiler:** GCC (or any standard C compiler)
* **Libraries:**

  * stdio.h
  * stdlib.h
  * string.h

---

## 📂 Project Structure

```
.
├── main.c
├── trips.txt
├── tickets.txt
└── README.md
```

---

## 🚀 How to Compile & Run

1. Open a terminal in the project directory.
2. Compile the program:

```bash
gcc CMPE1101_Project_5001240020_OmerFaruk_Asik.c -o bus_system
```

3. Run the program:

```bash
./bus_system
```

---

## 🧾 Data Files

* **trips.txt** – Stores all created trip records
* **tickets.txt** – Stores all sold ticket records

These files are automatically created if they do not exist.

---

## 🧑‍💻 Author

**Ömer Faruk Aşık**

---
