# gnuplot script to visualize sensor data from 9DoF Stick
# Creates 3 graphs; one for each sensor
# Pauses between each graph until user hits any key
# Written by Chris Taylor for SparkFun Electronics 12/7/10
# see http://www.sparkfun.com/news/499

# Clear unwanted parameters
unset log
unset label

# Set up terminal (different for Mac and Linux!)
set term aqua 

# Set graph parameters
set style data lines
set autoscale x
set xlabel "Milliseconds"
set ylabel "Raw Data"

# Plot HMC5343 Data
set title "Magnetometer Data" 

plot"out.txt" using 10:1 title 'mx', \
"out.txt" using 10:2 title 'my',  \
"out.txt" using 10:3 title 'mz'

#Wait
pause mouse any "Hit any key to see Accelerometer Data"

# Plot ADXL345 Data
set title "Accelerometer Data"

plot"out.txt" using 10:4 title 'ax', \
"out.txt" using 10:5 title 'ay',  \
"out.txt" using 10:6 title 'az'

# Wait
pause mouse any "Hit any key to see Gyro Data" 

# Plot ITG3200 Data
set title "Gyro Data"

plot"out.txt" using 10:7 title 'gx', \
"out.txt" using 10:8 title 'gy',  \
"out.txt" using 10:9 title 'gz'
