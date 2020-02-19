//
//  shelpers.hpp
//  UnixShellWannabe
//
//  Created by Warner Nielsen on 1/31/20.
//  Copyright © 2020 Warner Nielsen. All rights reserved.
//

#pragma once

#include <string>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <vector>
#include <stdio.h>

//You shouldn't need to touch these or call them directly
bool splitOnSymbol(std::vector<std::string>& words, int i, char c);
std::vector<std::string> tokenize(const std::string& s);

//You'll need to fork/exec for each one of these!
//Initially, assume the user tries to only execute 1 command.
struct Command{
  std::string exec; //the name of the executable
  //remember argv[0] should be the name of the program (same as exec)
  //Also, argv should end with a nullptr!
  std::vector<const char*> argv;
  int fdStdin, fdStdout;
  bool background;
};

//useful for debugging (implemented for you)
std::ostream& operator<<(std::ostream& outs, const Command& c);

//Read this function.  You'll need to fill in a few parts to implement
//I/O redirection and (possibly) backgrounded commands.
//Most of the places you need to fill in contain an assert(false), so you'll
//discover them when you try to use more functionality
std::vector<Command> getCommands(const std::vector<std::string>& tokens);
