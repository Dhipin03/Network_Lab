#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define BUCKET_CAPACITY 10

// Function to simulate data transmission
void sendData(int data) {
    printf("Sending data: %d\n", data);
}

int main() {
    int inputRate, bucketSize, dataSize, i;
    int bucketContent = 0;

    printf("Enter the input rate (data units per second): ");
    scanf("%d", &inputRate);

    printf("Enter the bucket size (data units): ");
    scanf("%d", &bucketSize);

    printf("Enter the data size to be sent (data units): ");
    scanf("%d", &dataSize);

    printf("\n");

    for (i = 0; i < dataSize; i++) {
        // Sleep for one second to simulate the passage of time
        sleep(1);

        // Generate a random data unit
        int data = rand() % 5 + 1;

        printf("Packet %d, size = %d\n", i + 1, data);

        // Check if the bucket can accept the new data unit
        if ((data + bucketContent) <= bucketSize) {
            bucketContent += data;
            printf("Data accepted into the bucket. Bucket content: %d/%d\n", bucketContent, bucketSize);
            sendData(data); // Simulate data transmission
        } else {
            printf("Bucket overflow! Data discarded.\n");
        }

        // Update the bucket content after one second of data transmission
        bucketContent -= inputRate;
        if (bucketContent < 0) {
            bucketContent = 0;
        }
        printf("Data sent. Bucket content after transmission: %d/%d\n", bucketContent, bucketSize);
    }

    return 0;
}
