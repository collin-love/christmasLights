// Macros for assignment 3 - make christmas lights
#define DELAY_CONVERSION_FACTOR 5000 // convert msec to counter number
#define SCAN_OFFSET 695  // Offset for scan range
#define SCAN_DATA TSI0->DATA & 0xFFFF // Accessing the bits held in TSI0_DATA_TSICNT
#define TSI_CENTER 450 // reading from approximate center of TSI
#define TSI_THRESHOLD 70 // threshold value to ignore non-inputs

#define RED_LED_SHIFT (18) // port b
#define GREEN_LED_SHIFT (19) // port b
#define BLUE_LED_SHIFT (1) // port d

#define RED 1 // red
#define GREEN 2 // green
#define BLUE 3 // blue
#define WHITE 4 // white

#define TWICE 2 // two loops for startup

#ifndef LOG_H_
#define LOG_H_

#ifdef DEBUG
#define LOG printf
#define TENTH_SECOND 100 // 0.1 seconds
#define HALF_SECOND 500 // 0.5 seconds
#define ONE_SECOND 1000 // 1 second
#define TWO_SECOND 2000 // 2 seconds
#define THREE_SECOND 3000 // 3 seconds

#define HALF_SECOND_CONVERTED 6 // 0.5s in counters
#define ONE_SECOND_CONVERTED 12 // 1s in counters
#define TWO_SECOND_CONVERTED 24 // 2s in counters
#define TWO_HALF_SECOND_CONVERTED 30 // 2.5s in counters
#define FOUR_HALF_SECOND_CONVERTED 54// 4.5s in counters
#define FIVE_SECOND_CONVERTED 60 // 5s in counters
#define EIGHT_SECOND_CONVERTED 96 // 8s in counters
#define EIGHT_HALF_SECOND_CONVERTED 102 // 8.5s in counters
#else
#define LOG(...)
#define DELAY_CONVERSION_FACTOR 5000 // convert msec to counter number
#define TENTH_SECOND 100 // 0.1 seconds
#define HALF_SECOND 500 // 0.5 seconds
#define ONE_SECOND 1000 // 1 second
#define TWO_SECOND 2000 // 2 seconds
#define THREE_SECOND 3000 // 3 seconds

#define HALF_SECOND_CONVERTED 6 // 0.5s in counters
#define ONE_SECOND_CONVERTED 12 // 1s in counters
#define TWO_SECOND_CONVERTED 24 // 2s in counters
#define TWO_HALF_SECOND_CONVERTED 30 // 2.5s in counters
#define FOUR_HALF_SECOND_CONVERTED 54// 4.5s in counters
#define FIVE_SECOND_CONVERTED 60 // 5s in counters
#define EIGHT_SECOND_CONVERTED 96 // 8s in counters
#define EIGHT_HALF_SECOND_CONVERTED 102 // 8.5s in counters
#endif

#endif /* LOG_H_ */
