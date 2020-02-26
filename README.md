# Operating-System

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
