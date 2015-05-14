# ClassForge
For a while now I have been trying to contruct a tool that would turn a massive amount of configs into some sort of usable class documentation automatically. ClassForge is the first step to achieve this.

## What is ClassForge?

Its a .NET dll library that lets you (given a path to either a config or a folder where multiple configs are located) generate an in-memory class tree model that you can later use to do whatever you please with.

**THIS IS NOT AN APPLICATION, BUT A TOOL FOR PROGRAMMERS!**

## Usage

The library is available through NuGet:

https://www.nuget.org/packages/ClassForge.dll/

```
PM> Install-Package ClassForge.dll
```

Or just find it in the NuGet Package Manager in VS.

One the dll is referenced in your project you can use the three following methods:

```
using ClassForge;
using ClassForge.Model;

.....

var parser = new CfgSimpleParser();

var model = parser.Parse("files\\config.cpp"); // parses one single config and returns a Model

var models = parser.ParseDirectory("files\\mergetest"); // parses a directory and returns a List<Model> with every Model corresponding to a config.cpp found (recursively)

var model = parser.ParseDirectoryMerged("files\\mergetest"); // parses a directory and returns a Model with all Models corresponding to a config.cpp found (recursively) merged into a single model

```
