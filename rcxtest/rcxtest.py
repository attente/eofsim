#!/usr/bin/python

import gtk, gtk.glade
import serial

def on_window_destroyed (win):
  exit (0)

def get_value (obj):
  return chr (int (obj.get_value ()))

def on_scale_value_changed (obj):
  port.write ('*' + (''.join (map (get_value, scales))))

xml = gtk.glade.XML ('rcxtest.glade')
xml.signal_autoconnect (globals())
scales = map (xml.get_widget, ['scale1', 'scale2', 'scale3'])
labels = map (xml.get_widget, ['labela', 'labelb', 'labelc'])
port = serial.Serial ("/dev/ttyUSB0", 9600)

gtk.main ()
