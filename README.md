# Operating-System

P1
-----------------------------------------------------------------------------------------------------------------------------------

(1) The PurposeTo familiarize youwith the fork(), exec(), wait(), and exit() Linux system calls by writinga simple Linux shellin C++that can run system programs.(2) Shell SpecificationTo make your life easier and reduce your effort on scanning and parsing the shell commands, you may assumethatall commands entered at the promptare syntactically correct. In other words, you do not have to verify if a command entered by a user is valid or not.(2.1) The Shell Language(2.1.1) The Lexical StructureThe input to the shell is a sequence of lines.Each line consists of tokens. Tokens are separated by one or more spaces. A line may contain as many tokens asa command is allowed to have.There is only one kindof tokens: words.Awordcan be either a command or an argument associated with a command.(2.1.2) Parsing the Shell LanguageA line of input represents atoken group.Each token group will result in the shell forking a new process and then executing the process.e.g. cat –n myfile.txt// a token groupEvery token group must begin with a word that is called the command(see example above). The words immediately following a command are calledarguments(e.g. there are two arguments for the catcommand above).A command may be followed bynone, one, or more argumentsas the command allows to have. Page 2of 3(2.1.3) Some Examples of Shell Commandsls: a token groupcontaining onetoken(i.e.a command)ls -l: a token group containing two tokens (i.e.a command and an argument)sort infile: a tokengroup containingtwo tokens (i.e.acommand and an argument) dir: a token group containingonly one token (i.e.a command)sort –dinfile: atoken group containingthree tokens (i.e.a command and two arguments)cat infile: a token group containing two tokens (i.e.a command and an argument) (3) Interpreting the Shell LanguageLines of input areinterpretedonce their tokens are correctly extracted. Your shell should first print a # sign to the screen representing a prompt and waitthere until the user types in a command. Your shell then spawns a child process to carry out the command.When yourshell finishes processingthe current line, it prints a # sign again to the screen waiting for the user to type in another command.This process is repeated until the user pressesCtrl-Cto terminate your shell.Every commandis to be interpreted as a valid Linux executable to be executed. All commands areassumed to be in the current directory.After interpreting a command, the shell should wait for the forked processto terminate before processingthe next line of input




P2
-----------------------------------------------------------------------------------------------------------------------------------


The PurposeTo familiarize youwith the pthread_create(), pthread_join(), and pthread_exit() functionsby writinga program inC orC++ running in the Debian VM environment to sort a list of evennumber of integers in nondecreasingorder using the sorting algorithm of your own choice.(2) The ProblemSort a list of even number of integers in nondecreasingorder using threethreads, among which two of them are sortingthreads responsible for sorting each of the two sublists, while the third thread (i.e.the mergingthread) is responsible for merging the twosortedsublists into a single sorted list. You mayassume that the total number of integers in the list is less than or equal to 20.(3) The ApproachCreate a global array shared betweenthe two sorting threads, each of which will work on half of thearray. A second global array of the same sizecan be used by the two sorting threads to store their sorted subarrays there. The merging thread then merges the two sorted subarrays into a sorted sequenceby using eitherthe first global arrayto store the result or a third global array to do it.This programming project will require passing parameters to each of thetwosorting threads. In particular, it will be necessary to identify the starting index from which each threadis to begin sorting. The mainthread will output the sorted array once allthreads have exited.The input data should be stored in a file named p2data.txt. The input filenameshould be hard coded in your program. Each line in the input file should contain exactly one integer. The sorted list should be displayed on the screen with each line containing exactly one inte




P3
-----------------------------------------------------------------------------------------------------------------------------------

(1) The PurposeTo familiarize youwith thesem_init(),sem_wait(), sem_post(), sem_destroy(), pthread_mutex_init(), 
pthread_mutex_lock(), pthread_mutex_unlock(), and pthread_mutex_destroy() functionsby writinga program in C++ running
in the Debian VM environment for the producer-consumer (i.e.bounded-buffer) problem shown in class.(2) The ProblemDesign and 
implement a programming solution to the producer-consumer problem shown in class solved using two general semaphores 
(i.e.empty and full) and twobinary semaphore (i.e.prod_mutexand cons_mutex). The two general semaphores are used to countthe number 
of empty and full buffersin the buffer pool, respectively, while the binary semaphores areused to protect the actual insertion or
removal of items in the buffer poolby the producer thread(s) and consumer thread(s), respectively.(3) The ApproachInternally, the 
buffer pool is implemented as a fixed-size array of type int. In this project, the maximum number of buffers in the buffer pool is 10.
The buffer pool will be manipulated as a circular queue. Also, the buffer pool will be manipulated with two functions, insert_item() and
remove_item(), which are called by the producer and consumer threads, respectively. A skeleton outlining these functions is shownas 
follows.int insert_item(int in_item) {P(empty); // make sure buffer pool is not fullbP(prod_mutex); // synchronize multiple producer 
threadsbuffer[in]= in_item;in = (in + 1) % 10;// updatethe inpointerbV(prod_mutex); // synchronize multiple producer threadsV(full);
//notify the consumerthreads/* return 0 if successful*/

Page 2of 5/* otherwise, return -1 indicating an error condition */}int remove_item(int *out_item) {P(full);
// make sure buffer pool is not emptybP(cons_mutex); // synchronize multiple consumer threadsout_item = buffer[out];out = (out + 1) % 10;//
update the our pointerbV(cons_mutex); // synchronize multiple consumer threadsV(empty);
// notify the producer threads/* return 0 if successful *//* otherwise, return -1 indicating an error condition
*/}Note that you should use the POSIX semaphore and mutex functions shown in class to implement the synchronization shown in
the insert_item() and remove_item() functions above.The main() function will initialize the buffer pool and those semaphores 
and mutexes needed for the project. The following shows the pseudo code to do it.int buffer_pool[10];semaphore empty, full;
/* two general semaphores */binary_semaphore prod_mutex, cons_mutex;/* two binary semaphores */item_type in_item, out_item;empty.
count = n; full.count = 0;int in = 0, out = 0;The main() functionwill also create the separate producer and consumer threads. 
Once it has created the producer and consumer threads, the main() function will sleep for a period of time (provided by the user) 
and, upon awakening, will terminate your program. In summary, the main() function will be provided (by the user) with the following 
three pieces of information.(a) How long to sleep (in seconds) before terminating(b) The number of producer threads(c) The number of 
consumer threads
Page 3of 5A skeleton for the main() functionis shown as follows.int main() {/* initialize the buffer pool, see page 2 above*//* 
initialize the semaphores and mutexes neededby the two functions, see page2 above*//* get the three pieces of information from the 
user *//* create producer thread(s) *//* create consumer thread(s) *//* sleep *//* exit */}A producer thread will alternate
betweensleeping for a random period of time (in seconds)and inserting a random integer into one of the buffers in the buffer 
pool(usinginto locate the buffer, as shown in class). Random numbers canbe produced using the rand() function, which produces 
random integersbetween 0 and RAND_MAX (animplementation dependent parameterbut guaranteed to be at least 32767). Your program
should convert the random number generated using the rand() function into a range of 0..3 representing how longthe producer 
threadwillsleepand 0..20 representingan itemto bedepositedinto a bufferby the producer thread. A consumer thread will also 
sleep for a random period of time (0..3, insecond(s)) and, upon awakening, will attempt to remove an item from one of the buffers
in the buffer pool(usingoutto locate the buffer, as shown in class).The following shows an outline of the producer and consumer 
threads.#include <stdlib.h> /* required for rand() */void *producer(void *param) {int item;while (true) {/* generate a random number
for the producerthreadto sleep */sleep(....);/* generate a random number representingan item to be deposited */if (insert_item(item))
// semaphores and mutexesare implemented in the
functioncout << "report error condition" << endl;elsecout << "producer " << tid << "produced " << item << "in buffer "
<<buffer_number<< endl;}
Page 4of 5void *consumer(void *param) {int item;while (true) {/* generate a random numberfor the 
consumerthreadto sleep */sleep(....);if (remove_item(&item))// semaphores and mutexesare implemented in the
functioncout << "report error condition" << endl;elsecout << "consumer " << tid << "consumed " << item << "from buffer " 
<<buffer_number << endl;}The following shows a scenario of running a sample program, where user's inputs are represented in 
boldface.Enter the number of seconds for the main() function to sleep: 15Enter the number of producer threads:2Enter the number
of consumer threads: 3/* program starts running here *//* program terminates after sleeping for 15 secon
