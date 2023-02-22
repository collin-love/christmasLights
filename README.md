[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-c66648af7eb3fe8bc4f294546bfd86ef473780cde1dea487d3c4ff354943c9ae.svg)](https://classroom.github.com/online_ide?assignment_repo_id=10079925&assignment_repo_type=AssignmentRepo)
# Description: 

This repository explores the manipulation of the LED's along with the use of the Touch Senstive Input (TSI) Capacitive Sensor on board the FRDM-KL25Z MCU. The main file (make_christmas_lights.c) implements various functions created in a utilities file that does the following:

Start up sequence:

White Flash -> Blue Flash -> White Flash -> Blue Flash -> 3s Delay

Main Loop (Varying lengths of time on flash):

Red Flash (0.5s) -> Green Flash (1s) -> Red Flash (2s) -> Green Flash (3s) -> Back to top

If TSI is touched on left side:

Red Flash (0.5s) -> Red Flash (1s) -> Red Flash (2s) -> Red Flash (3s) -> Back to top

If TSI is touched on right side:

Green Flash (0.5s) -> Green Flash (1s) -> Green Flash (2s) -> Green Flash (3s) -> Back to top

Files (source dir contains all unique files, the rest are automatically created by MCU Expresso IDE)

    -- make_christmas_lights.c (main script performing above functions)

    -- my_utilities.c (all functions created for purpose of manipulating LEDs and using TSI Capacitive Sensor)
    -- my_utilities.h (header file with brief description of functions)

    -- MACROS.h (file containing list of global vars/values)

To Calibrate TSI: Change the Following Values in MACROS.h

    -- #define SCAN_OFFSET 695  // Offset for scan range
    -- #define TSI_CENTER 450 // reading from approximate center of TSI
    -- #define TSI_THRESHOLD 70 // threshold value to ignore non-inputs

To download the repo

    -- git clone "https://github.com/collin-love/christmasLights"
