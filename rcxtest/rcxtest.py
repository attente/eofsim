#!/usr/bin/python
#
#  Copyright © 2007 Ryan Lortie
#
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of version 3 of the GNU General Public License as
#  published by the Free Software Foundation.
#
#  See the included COPYING file for more information.
#

import gtk, gtk.glade, gobject
import serial

def on_window_destroyed (win):
  exit (0)

def get_value (obj):
  return chr (int (obj.get_value ()))

def on_scale_value_changed (obj):
  port.write ('*' + (''.join (map (get_value, scales))))

def on_serial_data (fd, condition):
  global buffer

  byte = port.read ()

  if byte == '\n':
    buffer = ''
  else:
    buffer = buffer + byte

  if len (buffer) == 3:
    for (byte, label) in zip (buffer, labels):
      label.set_markup ("<span size='xx-large'>" +
                          str(ord(byte) - 109) +
                        "</span>")

  return True

def on_serial_err (fd, condition):
  exit (1)

xml = gtk.glade.XML ('rcxtest.glade')
xml.signal_autoconnect (globals())
scales = map (xml.get_widget, ['scale1', 'scale2', 'scale3'])
labels = map (xml.get_widget, ['labela', 'labelb', 'labelc'])
port = serial.Serial (port='/dev/ttyUSB0', timeout=0)
gobject.io_add_watch (port, gobject.IO_IN, on_serial_data)
gobject.io_add_watch (port, gobject.IO_ERR, on_serial_err)
on_scale_value_changed (None)
buffer = ''

gtk.main ()
