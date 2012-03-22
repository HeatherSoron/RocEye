RocEye is a 3D visualization tool, meant to aid in the playing of tabletop RPGs such as Dungeons and Dragons. In particular, RocEye is meant to allow easier visualization of aerial combat, since that seems to come up fairly often with our group, and virtual tabletops are far too flat to display that well.

At present, RocEye is pretty bare-bones. But, we'll be fleshing it out over time.

Configuration:
==============
You'll have to set up plugins.cfg and resources.cfg for your own system. Sample files have been included, with a .cfg.sample extention. Additionally, the file scene.cfg is currently the primary means of setting up scenes in RocEye. Comments and examples are included in that file; fuller documentation will come when the format and codebase are solidified.

Controls:
=========
WASD: standard camera movement
Q: rotate counterclockwise
E: rotate clockwise
R: move up
F: move down
shift: speed up movement
ctrl: slow down movement
space: point camera straight down
Up/down/left/right: change camera direction (note: numpad doesn't work)
Mouse movement: change camera direction
O: toggle object picking mode (either normal entities, or particle systems/etc.)
Left click: select an object for movement
C: Center camera on currently selected object
Shift-C: force camera to rotate about currently selected object
H: level the horizon (jittery when camera is aligned with x-axis)
Shift-H: lock the horizon to a level position
G: turn on/off gridlines centered on the camera
Shift-G: turn on/off gridlines centered on the target
T: toggle whether you're moving the camera or the selected object, when one is selected
Escape: exit


License:
========
I'll get a proper license.txt up when I'm less tired. Copyright 2012 Ethan Kaminski, and all that. You can definitely use this under a CC-BY-SA license; I'm likely to loosen the restrictions a bit when I've written that license.txt.
