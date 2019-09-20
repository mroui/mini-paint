# MiniPaint
> This is an desktop application based on a Paint XP application from Windows XP. It provides main functions you'd expect from a Paint, such as drawing, painting using shapes like circle, rectangle or triangle, etc. You can also edit image by stretch it, change size, invert colors, save it on your computer, open existing image and more. 

## Table of contents
* [Introduction](#introduction)
* [Features](#features)
* [Technologies](#technologies)
* [Screenshots](#screenshots)
* [Setup](#setup)
* [License](#license)

## Introduction
![alt text](./Assets/Images/eraser.png "Rubber image") 
</br>
**MiniPaint** is an application that reminds **Paint** app known from *Windows XP*. It does not have all functionalities like his parent, only some of them.
Hence the conclusion that *it is an application for drawing and editing images*.
</br>
![alt text](./Assets/Images/pencil.png "Pencil image")
</br>
There are a color palette and set of basic shapes and tools at our disposal. Created images can be saved to disk in several formats. It is possible to open existing images and edit them.
In addition, we can rotate, stretch, cut image and much more. 
</br>
![alt text](./Assets/Images/paintbucket.png "Paint bucket image")
</br>
It is an **desktop, window application** created in **C++** using **Qt**. Application was tested on *Windows 10 64bit*.

*Project was made for passing the subject in college, but it was so interesting, that I willingly developed it with additional properties.*

## Features
The main purpose is **drawing** and **painting**. 
* Tools: Rubber, Pencil, Line, Bucket
* Shapes: Line, Rectangle, Circle, Triangle
* Change brush width
* Full color palette
* Change work space size
* Floating window with tools
* Save image in formats: JPEG, PNG, BMP
* Open existing image in formats: JPEG, PNG, BMP
* Image modification: stretch, change size, rotation, invert colors
* Cut and paste

## Technologies
* C++
* Qt 5.13.1 (MSVC 2017, 32bit)
* Qt Creator 4.10.0

## Screenshots
![alt text](https://i.ibb.co/pbgFFWq/Screen1.png "Cosmos MiniPaint image")
![alt text](https://i.ibb.co/F3CNVVW/Screen3.png "Motor, clouds MiniPaint image")
![alt text](https://i.ibb.co/4gHCKLm/Screen2.png "Flower MiniPaint image")

## Setup
* Install Qt 5.13 or newer [here](http://qt-project.org/downloads)

```
#clone repository mini-paint
git clone https://github.com/mroui/mini-paint.git

#enter main folder
cd mini-paint

#start by Qt Creator project file
qt-creator mini-paint.pro
```
## License
This project is licensed under the terms of the MIT license.
