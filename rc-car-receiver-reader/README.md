# rc-car-receiver-reader

> Read remote control receiver values with Arduino

## Usage

1. Download and run the [Arduino IDE](https://www.arduino.cc/en/Main/Software)
1. Plug your Arduino board and configure it in **Tools > Board** and **Tools > Port**
1. Open `rc-car-receiver-reader.ino`
1. Install the `EnableInterrupts` and `arduino-timer` libraries by unzipping `libraries.zip` to your local Arduino libraries folder (`/Users/<user>/Documents/Arduino/libraries` on Mac) or the `libraries` folder in your sketchbook. Refer to https://www.arduino.cc/en/Guide/Libraries for more details on how to install Arduino libraries.
1. Connect your Arduino board to the RF receiver:

    Arduino  | RF Receiver
    -------- | --------------
    5V       | Shared V+
    GND      | Shared V-
    A0       | CH1 Signal
    A1       | CH2 Signal
    A(n)     | CH(n+1) Signal

1. Verify the sketch with **Sketch > Verify/Compile**
1. Upload and run the sketch with **Sketch > Upload**
1. Open **Tools > Serial Monitor** and set port speed (at the bottom right) to **57600 baud** to display the readings every 0.2 seconds:

    ```
    CH1:1572    CH2:1248    CH3:1076    CH4:1436
    CH1:1708    CH2:1096    CH3:1076    CH4:1436
    CH1:1704    CH2:1108    CH3:1084    CH4:1424
    CH1:1668    CH2:1160    CH3:1372    CH4:1472
    CH1:1572    CH2:1352    CH3:1440    CH4:1448
    CH1:1528    CH2:1480    CH3:1248    CH4:1364
    CH1:1504    CH2:1548    CH3:1072    CH4:1296
    CH1:1444    CH2:1420    CH3:1156    CH4:1268
    ```

1. Use the throttle and steering inputs on the RF transmitter. Confirm that the readings change, then write down the minimum and maximum values for each channel of interest.

## Readings

### 2018-10-31

Desert Fox v2 with HK-GT2E transmitter/receiver

Channel  | Role     | Pulse Width at Rest (us) | Minimum Pulse Width (us) | Maximum Pulse Width (us)
-------- | -------- | ------------------------ | ------------------------ | ------------------------
CH1      | Steering | 1492 - 1496              | 996 - 1000 (Right)       | 1980 - 1984 (Left)
CH2      | Throttle | 1528 - 1532              | 1036 - 1040 (Reverse)    | 1992 - 1996 (Forward)

## References

- [Reading Remote Control Receiver Values with Arduino](https://ryanboland.com/blog/reading-rc-receive)
