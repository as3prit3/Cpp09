#!/bin/bash

# Function to generate random mouse events
generate_mouse_event() {
    local screen_width=$(xdpyinfo | grep 'dimensions:' | awk '{print $2}' | cut -d'x' -f1)
    local screen_height=$(xdpyinfo | grep 'dimensions:' | awk '{print $2}' | cut -d'x' -f2)
    local x=$((RANDOM % screen_width))
    local y=$((RANDOM % screen_height))
    
    # Move the mouse to a random position and click
    xdotool mousemove $x $y
}

# Infinite loop to run the function every 4 minutes
while true; do
    generate_mouse_event
    sleep 240 # Sleep for 4 minutes
done
