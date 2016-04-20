# dfyyc

###
编译源码需要SDL多媒体库，工程中提供了两个版本的工程文件，一个是linux下的Makefile，在linux下cd到当前目录键入：

	make && make run

即可运行游戏，对于windows下，提供了codeblocks工程文件，请在修改工程文件中SDL库的绝对目录，修改为您实际安装的实际目录。然后双击即可打开编译。


linux下已经测试编译通过的适用范围（其他并未测试）：

	gcc version 5.2.1 20151010 (Ubuntu 15.10)
	sdl version 1.2

对于其他版本的gcc，若无法编译通过，请尝试去掉编译选项中的-Wall -Werror，然后在尝试重新编译：

	make clean && make && make run

对于windows下：

	编译器：mingw-gcc（codeblocks-mingw-gcc中附带的gcc）
	sdl version 1.2

总结：
	算法才是硬道理，不能在不误正业了，多上github，少上知乎。
