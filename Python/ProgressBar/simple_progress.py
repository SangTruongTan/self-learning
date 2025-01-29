from progress.bar import Bar
from progress.bar import ChargingBar
import time

# Create a progress bar
with Bar('Processing', max=10) as bar:
    for i in range(10):
        time.sleep(0.2)  # Simulate work
        bar.next()       # Move the bar forward

# Create a charging bar
with ChargingBar('Processing', max=10) as charging:
    for i in range(10):
        time.sleep(0.2)  # Simulate work
        charging.next()       # Move the bar forward
