# MetaCoreBS

The Beat Saber specific extension of [MetaCore](https://github.com/Metalit/MetaCore).

## Documentation

This is just the general idea for each header file with the general contents to expect for each. Documentation for specific functions and variables can be found in the files themselves (except `stats.hpp`, which should be fairly self explanatory, and `internals.hpp`, which would be too annoying to document). Also, many of the functions (in particular everything in `events.hpp`) are not designed for multithreading, so when in doubt use `Engine::ScheduleMainThread` in MetaCore (`unity.hpp`). (All callbacks will be run on the main thread for you.) There is also more in [MetaCore](https://github.com/Metalit/MetaCore).

### `events.hpp`

Provides the ability to register callbacks to and broadcast events, with some available by default and the option to add more from other mods.

### `game.hpp`

Provides utilities for various aspects of Beat Saber game state and singletons.

### `input.hpp`

Provides utilities for managing controllers and their input.

### `internals.hpp`

Allows access and modification to the internal statistics tracked by the mod, in case another mod changes them in an unusual way.

### `pp.hpp`

Provides BeatLeader and ScoreSaber PP-related information retrieval and calculations.

### `songs.hpp`

Provides utilities related to songs and beatmaps.

### `stats.hpp`

Provides getters for many statistics about the currently playing level.

### `ui.hpp`

Provides utilities that I personally use to make creating and updating BSML (Lite) UI a little easier.

### `uiimpl.hpp`

Defines the functions in `ui.hpp`, in order to make BSML not a required dependency.
