qmake  -t vcapp -o ioitem.dsp   ioitem.pro
msdev ioitem.dsp /MAKE "ioitem - Debug"  /OUT  log.txt
notepad log.txt

