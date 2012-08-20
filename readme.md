This is an Arduino 1.0 program for animating a series of ShiftBrite lights.  The project is for an art installation at Burning Man 2012.  Initially the project started out as a [series of pendulums](http://robacarp.github.com/burning-man-pendulum) that would each be swinging with a slightly offset period, calculated to produce striking patterns in their swing.  Due to cost and time constraints, the pendulum idea was scrapped for a series of variable length, stationary light poles.   Each pole has a [ShiftBrite Satellite](http://macetech.com/store/index.php?main_page=product_info&products_id=16) module inside a diffuser globe. 

###Code Highlights:

  - **Arduino 1.0 compatible algorithm for controlling ShiftBrites** - Available code from [Macetech](http://docs.macetech.com/doku.php/shiftbrite#code_example), the [Arduino website](http://arduino.cc/playground/Main/ShiftBriteLib), and [other resources on Github](http://code.google.com/p/shiftbritehughesyarduino/) is largely messy code, overcomplicated, with excessively verbose *and global* variable names, and... it doesn't compile anymore.  It isn't abstracted out into its own library, but the [functions are isolated into their own .ino file](https://github.com/robacarp/bm_lights/blob/master/lights.ino). for easy inclusion into other arduino projects.
  - **Working Algorithm for converting HSB color values to RGB**  - This proved to be incredibly useful for producing good looking color transitions.  Setting color values with RGB is not conducive to simple constant brightness color changing algorithms. By altering the color space to allow for setting Hue, Saturation and Brightness independently, visual applications which slide between colors are much easier to write and understand.  [Color.h](https://github.com/robacarp/bm_lights/blob/master/color.h) contains a class definition which will transparently transcode HSB color values to RGB -- but **not** the other way. 
  - **Several simple color fading algorithms** - These are scattered out across .ino files to keep things simple in the main sketch file.  [rainbow.ino](https://github.com/robacarp/bm_lights/blob/master/rainbow.ino), [pink.ino](https://github.com/robacarp/bm_lights/blob/master/pink.ino) and [achromatic.ino](https://github.com/robacarp/bm_lights/blob/master/achromatic.ino) are a few examples.  Thanks to HSB conversion, these algorithms are basically one or two lines.
  - **Function pointer algorithm switcher** - More or less for my own enjoyment and later reference, I'd never coded with a function pointer in C/C++.  Pundits tell me function pointers are often a bad idea and without pre-setting the pointer in the setup() function, I quickly found out why.  Nevertheless, it was a good exercise and I hope this will provide a reference for myself and whoever else.


###As-is Use:

If you'd like to use this library to control your own series of ShiftBrite lights, feel free.  The configuration variables at the top of [bm_lights.ino](https://github.com/robacarp/bm_lights/blob/master/bm_lights.ino) contain the default pin mappings for the ShiftBrite shield.  If you're using the shield, NUM_LIGHTS is probably the only thing you'll need to configure.

The algorithm switcher is triggered by an interrupt on pin 3 using the internal pull-up resistor.  Connect a switch between pin 3 and ground to hook into this functionality.  There is some light software debounce, I'd suggest a cap on that circuit if you really want it to be reliable.  YMMV.

This was verified compiling under Arduino 1.0.1 on 2012-08-20.  If you end up using this code or any parts of it in a project of yours, send me an email description or a picture.  I'd love to hear about it going big places. :-)


###License:

Copyright &copy; 2012 Robert Carpenter.

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.