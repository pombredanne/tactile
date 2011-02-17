#!/usr/bin/python
# (c) 2011-02-17 Thomas Perl <thp.io>; public domain

import gtk
import hildon
import time
import subprocess

def tactile(pattern):
    subprocess.Popen(('sudo', 'tactile', pattern))

def cb(*args):
    tactile(args[-1])

def on_visible(widget, visible, kind):
    if widget.props.visible:
        tactile(kind)
    else:
        tactile(kind+'-out')

w = hildon.StackableWindow()
a = hildon.AppMenu()
b = gtk.Button('blubb')
b.connect('button-press-event', cb, 'button')
def on_show_dialog(*args):
    global dlg
    dlg.show_all()
a.append(b)
a.connect('notify::visible', on_visible, 'appmenu')
w.set_app_menu(a)
a.show_all()

dlg = gtk.Dialog()
dlg.connect('notify::visible', on_visible, 'dialog')
dlg.set_title('heya')
for i in range(7):
    dlg.vbox.add(gtk.Label('xxx'+str(i)))

def on_delete(dlg, *args):
    dlg.hide()
    return True
dlg.connect('delete-event', on_delete)

sw = hildon.PannableArea()
adj = sw.get_vadjustment()

def xxx(*args):
    if adj.props.value == adj.props.lower:
        cb('scroll-stop')

adj.connect('changed', xxx, 'changed')

v = gtk.VBox()
v.set_border_width(20)
sw.add_with_viewport(v)
b = gtk.Button('show the dialog')
b.connect('clicked', on_show_dialog)
b.set_name('HildonButton-finger')
b.set_size_request(-1, 70)
b.connect('button-press-event', cb, 'button')
v.add(b)

v.add(gtk.Label(' '))

def on_value_changed(*args):
    tactile('slider-change')

hsc = gtk.HScale()
hsc.set_range(0, 1000)
hsc.connect('value-changed', on_value_changed)
v.add(hsc)

v.add(gtk.Label(' '))


for i in range(200):
    v.add(gtk.Label('xxx'+str(i)))
w.add(sw)
w.connect('destroy', gtk.main_quit)
w.show_all()
gtk.main()

