//
//  main.cpp
//  UnixShellWannabe
//
//  Created by Warner Nielsen on 1/31/20.
//  Copyright © 2020 Warner Nielsen. All rights reserved.
//

#include "shelpers.hpp"

#include <iostream>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int cd(char *path) {
    return chdir(path);
}

int main(int argc, const char * argv[]) {
  try {
    // todo loop tokenizer
    std::string line;
    char *buffer;
    
    while ((buffer = readline("$ "))) {
//    while (getline(std::cin, line)) {
      auto symbols = tokenize(buffer);
      auto commands = getCommands(symbols);
      std::vector<pid_t> pids;
      
      for (int i = 0; i < commands.size(); i++) {
        int pid = fork();
        Command c = commands[i];
        
        if (pid < 0) {
          // failed fork
          perror("fork failed");
        } else if (pid == 0) {
          // in child
          int fdIn = dup2(c.fdStdin, 0);
          if (fdIn == -1) {
            perror("fdIn failed");
            exit(1);
          }
          
          int fdOut = dup2(c.fdStdout, 1);
          if (fdOut == -1) {
            perror("fdOut failed");
            exit(1);
          }
          
          if (c.exec == "cd") {
            if (symbols.size() == 1)
              cd(getenv("HOME"));
            else if (cd((char *)(symbols[1].c_str())) < 0)
              perror("cd command did not work");
            
            /* Skip the fork */
            continue;
          }
          
          int ret = execvp(c.exec.c_str(), const_cast<char* const *>(c.argv.data()));
          if (ret == -1) {
            perror("execvp failed");
            exit(1);
          }
        } else {
          // in parent
          if (c.fdStdin != 0)
            close(c.fdStdin);
          if (c.fdStdout != 1)
            close(c.fdStdout);
          
          pids.push_back(pid);
          int returnStatus;
          
          if (!c.background) {
            for (pid_t p: pids) {
              waitpid(p, &returnStatus, 0);
            }
          } else {
            for (pid_t p: pids) {
              std::cout << p << std::endl;
            }
          }
        }
      }
      free(buffer);
    }
    return 0;
  } catch (std::runtime_error exn) {
    std::cerr << exn.what() << std::endl;
    return 1;
  }
}
