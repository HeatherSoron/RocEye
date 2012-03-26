#ifdef NO_BLACK_MAGIC
#error Warning: This file cannot compile without black magic.
#endif

// Note: NO header guard. This file is made to be imported multiple times!
// Nothing other than macros like those below should be in this file!

INTERACTION_FUNCTION(IncreaseSpeed,changeSpeed,1)
INTERACTION_FUNCTION(DecreaseSpeed,changeSpeed,-1)

INTERACTION_FUNCTION(TranslateForward,translate,InputHandler::DIR_FORWARD)
INTERACTION_FUNCTION(TranslateBackward,translate,InputHandler::DIR_BACKWARD)
INTERACTION_FUNCTION(TranslateLeft,translate,InputHandler::DIR_LEFT)
INTERACTION_FUNCTION(TranslateRight,translate,InputHandler::DIR_RIGHT)
INTERACTION_FUNCTION(TranslateUp,translate,InputHandler::DIR_UP)
INTERACTION_FUNCTION(TranslateDown,translate,InputHandler::DIR_DOWN)

INTERACTION_FUNCTION_ROTATE(RotateClockwise,InputHandler::ROT_CW)
INTERACTION_FUNCTION_ROTATE(RotateCounterClockwise,InputHandler::ROT_CCW)
INTERACTION_FUNCTION_ROTATE(RotateUp,InputHandler::ROT_UP)
INTERACTION_FUNCTION_ROTATE(RotateDown,InputHandler::ROT_DOWN)
INTERACTION_FUNCTION_ROTATE(RotateLeft,InputHandler::ROT_LEFT)
INTERACTION_FUNCTION_ROTATE(RotateRight,InputHandler::ROT_RIGHT)

INTERACTION_FUNCTION(ResetCamera,resetCamera,) // Note: that comma is necessary

INTERACTION_FUNCTION(ToggleObjectLock,toggleObjectLock,)
INTERACTION_FUNCTION(CenterOnObject,centerObject,)

INTERACTION_FUNCTION(ToggleHorizonLock,toggleHorizonLock,)
INTERACTION_FUNCTION(LevelHorizon,levelHorizon,)

INTERACTION_FUNCTION(ToggleLocalGridLines,toggleGridLines,false)
INTERACTION_FUNCTION(ToggleObjectGridLines,toggleGridLines,true)

INTERACTION_FUNCTION(ToggleSnapToGrid,toggleSnapToGrid,)
INTERACTION_FUNCTION(ToggleObjectMode,toggleObjectMode,)

INTERACTION_FUNCTION(ToggleMovementTarget,toggleMovementTarget,)

INTERACTION_FUNCTION(PrimaryPointerUp,onPrimaryPointerUp,)
INTERACTION_FUNCTION(PrimaryPointerDown,onPrimaryPointerDown,)

INTERACTION_FUNCTION(ActivateConsole,activateConsole,)

INTERACTION_FUNCTION(ToggleConsole,toggleConsole,)