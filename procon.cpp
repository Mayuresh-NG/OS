#include <iostream>
#include <cstdlib>

using namespace std;

// Initialize a mutex to 1
int mutex = 1;

// Number of full slots as 0
int full = 0;

// Number of empty slots as size of buffer
int empty_slots, bufferSize, x = 0;

// Function to produce an item and add it to the buffer
void producer()
{
    // Decrease mutex value by 1
    --mutex;

    // Increase the number of full slots by 1
    ++full;

    // Decrease the number of empty slots by 1
    --empty_slots;

    // Item produced
    x++;
    cout << "\nProducer produces item " << x << endl;

    // Increase mutex value by 1
    ++mutex;
}

// Function to consume an item and remove it from buffer
void consumer()
{
    // Decrease mutex value by 1
    --mutex;

    // Decrease the number of full slots by 1
    --full;

    // Increase the number of empty slots by 1
    ++empty_slots;
    cout << "\nConsumer consumes item " << x << endl;
    x--;

    // Increase mutex value by 1
    ++mutex;
}

// Driver Code
int main()
{
    int n, i;
    cout << "\nEnter the buffer size: ";
    cin >> bufferSize;

    empty_slots = bufferSize;

    cout << "\n1. Press 1 for Producer"
        "\n2. Press 2 for Consumer"
        "\n3. Press 3 for Exit\n";

    for (i = 1; i > 0; i++) {

        cout << "\nEnter your choice: ";
        cin >> n;

        // Switch Cases
        switch (n) {
        case 1:

            // If mutex is 1 and empty is non-zero, then it is possible to produce
            if ((mutex == 1)
                && (empty_slots != 0)) {
                producer();
            }

            // Otherwise, print buffer is full
            else {
                cout << "Buffer is full!" << endl;
            }
            break;

        case 2:

            // If mutex is 1 and full is non-zero, then it is possible to consume
            if ((mutex == 1)
                && (full != 0)) {
                consumer();
            }

            // Otherwise, print Buffer is empty
            else {
                cout << "Buffer is empty!" << endl;
            }
            break;

        // Exit Condition
        case 3:
            exit(0);
            break;

        default:
            cout << "Invalid choice!" << endl;
            break;
        }
    }

    return 0;
}



// #include <iostream>
// #include <thread>
// #include <semaphore.h>
// #include <vector>

// using namespace std;

// // Initialize the semaphores
// sem_t mutex;
// sem_t empty_slots;
// sem_t full;

// // Declare the buffer and other variables
// vector<int> buffer;
// int buffer_size;
// int num_items_to_produce;
// int num_items_to_consume;
// int item_counter = 0;
// int producer_counter = 0;
// int consumer_counter = 0;

// // Function to produce an item and add it to the buffer
// void producer()
// {
//     while (producer_counter < num_items_to_produce) {
//         // Wait for an empty slot in the buffer
//         sem_wait(&empty_slots);
        
//         // Acquire the mutex lock
//         sem_wait(&mutex);
        
//         // Produce an item and add it to the buffer
//         item_counter++;
//         buffer.push_back(item_counter);
//         cout << "Producer produces item " << item_counter << endl;
//         producer_counter++;

//         // Release the mutex lock
//         sem_post(&mutex);
        
//         // Signal that the buffer is no longer empty
//         sem_post(&full);
//     }
// }

// // Function to consume an item and remove it from the buffer
// void consumer()
// {
//     while (consumer_counter < num_items_to_consume) {
//         // Wait for a full slot in the buffer
//         sem_wait(&full);
        
//         // Acquire the mutex lock
//         sem_wait(&mutex);
        
//         // Consume an item from the buffer
//         int item = buffer.back();
//         buffer.pop_back();
//         cout << "Consumer consumes item " << item << endl;
//         consumer_counter++;
        
//         // Release the mutex lock
//         sem_post(&mutex);
        
//         // Signal that the buffer is no longer full
//         sem_post(&empty_slots);
//     }
// }

// int main()
// {
//     // Prompt the user to enter the buffer size, number of items to produce, and number of items to consume
//     cout << "Enter the buffer size: ";
//     cin >> buffer_size;
//     cout << "Enter the number of items to produce: ";
//     cin >> num_items_to_produce;
//     cout << "Enter the number of items to consume: ";
//     cin >> num_items_to_consume;

//     // Initialize the semaphores
//     sem_init(&mutex, 0, 1);
//     sem_init(&empty_slots, 0, buffer_size);
//     sem_init(&full, 0, 0);

//     // Create the producer and consumer threads
//     thread producer_thread(producer);
//     thread consumer_thread(consumer);

//     // Join the threads
//     producer_thread.join();
//     consumer_thread.join();

//     // Destroy the semaphores
//     sem_destroy(&mutex);
//     sem_destroy(&empty_slots);
//     sem_destroy(&full);

//     return 0;
// }

