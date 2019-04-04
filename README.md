# Introduction
    Creating an Interactive User Defined Shell
# How to run
    * Run make and then ./shell to run the shell
 # How to quit
    * Type quit to quit the shell
    
# Specification 1: Display requirement
    When you execute your code a shell prompt similar to the following must appear:
    <username@system_name:curr_dir>
    Example: <Name@UBUNTU:~/Documents/>
    The directory from which the shell is invoked will be the home directory of the shell
    and should be indicated by “~". If the user executes "cd" i.e change dir, then the
    corresponding change must be reflected in the shell as well.
    Example: ./a.out
    <Name@UBUNTU:~> cd newdir
    <Name@UBUNTU:~/newdir>
    
  # Specification 2: Built-in Commands
    Builtin commands are contained within the shell itself. Checkout ‘type
    commandname’ in the terminal (eg. ‘type echo’).
    When the name of a builtin command is used as the first word of a simple
    command the shell executes the command directly, without invoking another
    program. Builtin commands are necessary to implement functionality impossible or
    inconvenient to obtain with separate utilities.
    Make sure you implement cd, pwd and echo.
    Don’t use ‘execvp’ or similar commands for these, using these doesn’t mean it’s
    built-in to your shell.
    
  # Specification 3: ls command
    Implement ls [al] – (it should be able to handle ls, ls -l, ls -a and ls -al/la. For ls and
    ls -a, outputting the entries in a single column is fine.
    
  # Specification 4: System commands with and without arguments
    All other commands are treated as system commands like : emacs, vi and so on.
    The shell must be able to execute them either in the background or in the
    foreground.
    Foreground processes: For example, executing a "vi" command in the foreground
    implies that your shell will wait for this process to complete and regain control when
    this process exits.
    Background processes: Any command invoked with "&" is treated as background
    command. This implies that your shell will spawn that process and doesn't wait for
    the process to exit. It will keep taking user commands.
    
    E.g
    <Name@UBUNTU:~> ls &
    This command when finished, should print its result to stdout.
    <Name@UBUNTU:~>emacs &
    <Name@UBUNTU:~> ls -l -a ( Make sure all the given flags are executed properly
    for any command and not just ls.).
    .
    .
    ... Execute other commands...
    .
    <Name@UBUNTU:~> echo hello
    
   # Specification 5: pinfo command (user defined)
    pinfo : prints the process related info of your shell program.
    
    Ex: <Name@UBUNTU:~> pinfo
    pid -- 231
    Process Status -- {R/S/S+/Z} memory
    - 67854 {Virtual Memory}
    - Executable Path -- ~/a.out
    -pinfo <pid> : prints the process info about given pid.
    
    Ex: <Name@UBUNTU:~>pinfo 7777
    pid -- 7777
    Process Status -- {R/S/S+/Z} memory
    - 123123 {Virtual Memory}
    - Executable Path — /usr/bin/gcc
   # Specification 6: Finished Background Processes
      If the background process exits then the shell must display the appropriate
      message to the user.
      
      Example:
      After emacs exits, your shell program should check the exit status of emacs and
      print it on stderr.
      <Name@UBUNTU:~>
      emacs with pid 456 exited normally
      <Name@UBUNTU:~>
   # Specification 7: Implement input-output redirection functionality
      Output of running one (or more) commands must be redirected to a file. Similarly, a
      command might be prompted to read input data from a file and asked to write
      output to another file. Appropriate error handling must be done (like if the input
      file does not exist – display error message, if output file does not exist - create one
      with permissions of 644, etc.)
      
      Output Redirection - Ex:
      <NAME@UBUNTU:~> diff file1.txt file2.txt > output.txt
      Input Redirection - Ex:
      <NAME@UBUNTU:~> sort < lines.txt
      Input-Output Redirection - Ex:
      <NAME@UBUNTU:~> sort < lines.txt > sortedlines.txt
      Note: There is another clause for output direction '>>', and that must be
      implemented appropriately.
   # Specification 8: Implement command redirection using pipes
      A pipe is identified by "|". One or more commands can be piped as the following
      examples show. Your program must be able to support any number of pipes.
      
      Two Commands - Ex:
      <NAME@UBUNTU:~> more file.txt | wc
      Three Commands - Ex:
      <NAME@UBUNTU:~> grep "new" temp.txt | cat somefile.txt | wc
   # Specification 9: Implement i/o redirection + pipes redirection
    Eg:
    <NAME@UBUNTU:~> ls | grep *.txt > out.txt
    <NAME@UBUNTU:~> cat < in.txt | wc -l > lines.txtHint: treat input output redirection as an argument to the command and handle it
    appropriately
    
   # Specification 10: User-defined commands
        The following commands must be supported by your shell:
        
        - setenv var [value] : If environment variable var does not exist, then your shell
        must create it. Your shell must set the value of var to value, or to the empty string if
        value is omitted. Initially, your shell inherits environment variables from its parent.
        Your shell must be able to modify the value of an existing environment variable or
        create a new environment variable via the setenv command. Your shell must be
        able to set the value of any environment variable; It is an error for a setenv
        command to have zero or more than two command-line arguments.
        
        - unsetenv var : Your shell must destroy the environment variable var. It is an error
        for an unsetenv command to have zero command-line arguments.
        
        - jobs : prints a list of all currently running jobs along with their pid, in particular,
        background jobs, in order of their creation along with their state – Running or
        Stopped.
        
        <NAME@UBUNTU:~> jobs
        [1]
        Running
        emacs assign1.txt [221]
        [2]
        Running
        firefox [430]
        [3]
        Running
        vim [3211]
        [4]
        Stopped
        gedit [3213]
        Here [4] i.e. gedit is most recent background job, and the oldest one is [1] emacs.

        - kjob <jobNumber> <signalNumber> : takes the job id of a running job and
        sends a signal value to that process
        
        <NAME@UBUNTU:~> kjob 2 9
        It sends SIGKILL to the process firefox, and as a result it is terminated. Here 9
        represents the signal number, which is SIGKILL. For further info, lookup “man 7
        signal“

        - fg <jobNumber> : brings a running or a stopped background job with given job
        number to foreground.
        
        <NAME@UBUNTU:~> fg 3
        Either brings the 3rd job which is vim to foreground or returns error if no such
        background number exists.

        - bg <jobNumber> : changes a stopped background job to a running background
        job.
        
        <NAME@UBUNTU:~> bg 4
        Changes gedit from Stopped in the background to Running in the background or
        return error if no such stopped background job exists. If that job is already running,
        do nothing.
    
        - overkill : kills all background process at once.

        - quit : exits the shell. Your shell should exit only if the user types this "quit"
        command. It should ignore any other signal from user like : CTRL-D, CTRL-C,
        SIGINT, SIGCHLD etc.

        - CTRL-Z : It should change the status of currently running job to stop, and push it
        in background process.

        - CTRL-C : It should cause a SIGINT signal to be sent to the current foreground
        job of your shell. If there is no foreground job, then the signal should not have
        any effect. 

   # BONUS
    1) Personal Reminder:
    Implement a reminder command ‘remindme’ which reminds you with a custom
    message after the given number of seconds elapse. You should allow the shell to
    take in commands during this time.
    
    Example:
    <Name@UBUNTU:~> remindme 20 “Go to OS Class.”
    <Name@UBUNTU:~>
    ....
    Reminder: Go to OS Class.
    
    2) Clock Command :
    Implement a ‘clock’ command which displays dynamic date and time in your shell.
    Updates should be done based on fixed time interval given as an argument. The
    usage of ‘date’ or similar commands is not allowed.
    
    Example:
    <Name@UBUNTU:~> clock -t 3 -n 2
    11 Aug 2018, 15:18:21
    11 Aug 2018, 15:18:24
    
    
