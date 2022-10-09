#include <stdio.h>

int front = -1, back = -1;
int frameCount, pageCount, pages[100], frames[100], faultCount = 0;

void insertIntoFrame(int page) {
    if(front == -1) {
        front = 0;
        back = 0;
        if(frameCount > 0) {
            frames[0] = page;
            return;
        }
    }

    if(back == frameCount-1) {
        // Frames are at maximum capacity, execute replacement algo
        // pop front, insert back
        for(int i=0; i<back; i++) {
            frames[i] = frames[i+1];
        }
        frames[back] = page;
    } else {
        back ++;
        frames[back] = page;
    }
}

void calculatePageFaults(int page) {
    int hit = 0;
    for(int i = front; i <= back; i++) {
        if(page == frames[i]) {          
            // got hit, no insert
            hit = 1;
            printf("HIT\n");
            break;
        } 
    }

    if( hit == 0 ) {
        printf("FAULT\n");
        faultCount++;
        insertIntoFrame(page);
    }
}

int main() {

    printf("Enter Number of frames: ");
    scanf("%d", &frameCount);

    printf("Enter Number of pages: ");
    scanf("%d", &pageCount);

    printf("Enter pages\n");

    for(int i=0; i<pageCount; i++) {
        scanf("%d", &pages[i]);
    }

    for(int i=0; i<pageCount; i++) {
        printf("Current frames:");
        for(int j=front; j<=back; j++) {
            if(j == -1) {
                printf("Frame Empty");
            } else {
                printf(" %d", frames[j]);
            }
        }
        printf("\ncurrent page: %d\n", pages[i]);
        calculatePageFaults(pages[i]);

        printf("\n");
        
    }

    printf("Total Page Fault: %d", faultCount);
    return 0;
}
