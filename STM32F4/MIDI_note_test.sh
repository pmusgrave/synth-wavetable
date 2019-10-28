#!/bin/bash
while true; do
      /home/paul/Downloads/sendmidi-linux-1.0.14/sendmidi dev "USB MIDI MIDI 1" on 24 127
      sleep 1
      /home/paul/Downloads/sendmidi-linux-1.0.14/sendmidi dev "USB MIDI MIDI 1" off 24 1
      sleep 1
done
