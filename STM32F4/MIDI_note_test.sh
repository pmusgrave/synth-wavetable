#!/bin/bash
while true; do
      /home/paul/Downloads/sendmidi-linux-1.0.14/sendmidi dev "USB MIDI MIDI 1" on 50 127
      sleep 1
      /home/paul/Downloads/sendmidi-linux-1.0.14/sendmidi dev "USB MIDI MIDI 1" off 50 0
      sleep 2
done
