# Test the C++ Library

In the file `test.cpp` it is provided a simple test for the Motion Sensor module. The test consist in sensing the Motion Sensor state (`ON | OFF`) every `1s`.

To run the test follow these steps:

* Compile the sources with the following command: `make all`

* The previous command will generate an executable file named `runner`, which you can run as follows: `sudo ./runner`.

* To remove the compiled `*.o` files and the dist file `runner`, execute the following line: `make clean`.
