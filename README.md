# TGA-Image-Manipulation
TGA Image Manipulator with Command Line Interface

Usage:

	./project2.out [output] [firstImage] [method] [...]
note: "project2.out" can be changed to whatever follows -o in the makefile

Example:

	./project2.out outputfile/myimage.tga inputfile/layer1.tga multiply inputfile/layer2.tga scalered 2 flip

Methods:

	multiply - 1 additional image argument
	subtract - 1 additional image argument
	overlay - 1 additional image argument
	screen - 1 additional image argument
	combine - 2 additional image arguments
	flip - no additional arguments
	onlyred - no additional arguments
	onlygreen - no additional arguments
	onlyblue - no additional arguments
	addred - 1 integer argument
	addgreen - 1 integer argument
	addblue - 1 integer argument
	scalered - 1 integer argument
	scalegreen - 1 integer argument
	scaleblue - 1 integer argument
