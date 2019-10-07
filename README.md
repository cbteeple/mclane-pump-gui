# mclane-pump-gui

This is a GUI for operting a McLane deep-sea rated low-pressure hydraulic pump through standard RS232 communication.

## Dependencies
### Hardware
- [McLane Pump - Just the pump](https://mclanelabs.com/remote-access-sampler-2)
- Control bottle for McLane pump w/ associated SubCon connectors
- USB to Serial converter (any cheap one will do)


### Software
- [Qt Development Platform](https://www.qt.io/) - The GUI is written in C++ using the Qt IDE, and must be built and run from within the IDE.
    - Confirmed working version of Qt Creator: **4.10.0**
    - Confirmed Kit to use on Windows 10: **Desktop 5.12.2 MinGQ 64-bit**
- Appropriate device drivers for USB to Serial converter

## Setup
- Pump Hardware - Always run the pump with water. The pump should not be run dry (this could damage it).
- Qt - Make sure you set the buld directory to something intelligent. It should be set to store the build in a "build" folder within this main folder.


## Usage
1. Open Qt and open the `Pump_GUI.pro` project.
2. Press the large "*Run*" button on the left sidebar of the QT IDE. The project will build, then a GUI will open.
3. Set up the correct COM ports and serial settings
    - Press the "*settings*" button (gear-shaped icon)
    - Set up the settings:
        - Buad: 9600
        - Data Bits: 8
        - Stop bits: 1
        - Pairity: None
        - Flow Control: None
4. Connect to the pump.
5. Control the pump!
    - Close: Run the pump forward to pressurize
    - Open: Run the pump backward to vent/draw vacuum
    - Halt: Stop running the pump. This needs to be pressed between *Close* and *Open* moves
6. When you're done, press the close button (red x) to exit the GUI and shut down the pump.


## Debugging
- If Qt hangs in the "*reading project*" stage when you open the project, this could be becasue the build directory is not set correctly.
    1. Go to the settings and locate the "*shadow build*" box.
    2. Set it to somewhere intelligent. Usually it should be set to the "*build*" folder inside the main folder.
    3. Force-quit the Qt IDE and re-open it. Everything should work now
- If the GUI looks gross on a high-DPI screen in Windows
    1. You're out of luck. [Qt (still) only supports integer scaling factors](https://bugreports.qt.io/browse/QTBUG-55654?focusedCommentId=330300&page=com.atlassian.jira.plugin.system.issuetabpanels%3Acomment-tabpanel). [Qt's official documentation](https://doc.qt.io/qt-5/highdpi.html) says nothing about this.
